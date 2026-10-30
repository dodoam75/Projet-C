/* ============================================================
 * produit.c - Implementation du catalogue produits
 * ------------------------------------------------------------
 * ROLE : gere le tableau dynamique b->produits (malloc/realloc).
 *        - ajouterProduit : unicite de la reference (inactifs inclus)
 *        - supprimerProduit : suppression LOGIQUE (actif = 0), refusee si
 *          le produit est dans une commande non annulee
 *        - afficherAlertesStock : stock <= seuilAlerte
 * ETAT : trouverProduit() est fait, le reste est en TODO.
 * ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include "produit.h"

#define CAPACITE_INITIALE_PRODUITS 4
#define STOCK_MAX 1000000

/* ================================================================== */
/*  SAISIE SÉCURISÉE                                                  */
/* ================================================================== */

/* Lit une ligne ; renvoie 1 si OK, 0 si trop longue. Arrêt propre sur EOF. */
static int lireLigne(char *dest, size_t taille)
{
    char tampon[512];

    if (fgets(tampon, sizeof tampon, stdin) == NULL) {
        fprintf(stderr, "\nFin de saisie (EOF) : arret du programme.\n");
        exit(EXIT_FAILURE);
    }
    size_t n = strlen(tampon);
    if (n > 0 && tampon[n - 1] == '\n') {
        tampon[--n] = '\0';
    } else {                         /* ligne plus longue que le tampon : on vide */
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        return 0;
    }
    if (n >= taille) return 0;
    strcpy(dest, tampon);
    return 1;
}

void lireChaine(const char *invite, char *dest, size_t taille)
{
    for (;;) {
        printf("%s", invite);
        if (!lireLigne(dest, taille)) {
            printf("Erreur : saisie trop longue (%zu caracteres max).\n", taille - 1);
            continue;
        }
        if (dest[strspn(dest, " \t")] == '\0') {
            printf("Erreur : la saisie ne peut pas etre vide.\n");
            continue;
        }
        return;
    }
}

int lireEntier(const char *invite, int min, int max)
{
    char buf[64];
    for (;;) {
        printf("%s", invite);
        if (!lireLigne(buf, sizeof buf)) { printf("Saisie invalide.\n"); continue; }
        char *fin;
        errno = 0;
        long v = strtol(buf, &fin, 10);
        if (fin == buf || *fin != '\0' || errno == ERANGE || v < min || v > max) {
            printf("Erreur : entier compris entre %d et %d attendu.\n", min, max);
            continue;
        }
        return (int)v;
    }
}

double lireReel(const char *invite, double min, int minExclus)
{
    char buf[64];
    for (;;) {
        printf("%s", invite);
        if (!lireLigne(buf, sizeof buf)) { printf("Saisie invalide.\n"); continue; }
        for (char *p = buf; *p; p++) if (*p == ',') *p = '.';
        char *fin;
        errno = 0;
        double v = strtod(buf, &fin);
        if (fin == buf || *fin != '\0' || errno == ERANGE || !isfinite(v)
            || v < min || (minExclus && v <= min) || v > 1e9) {
            printf("Erreur : nombre %s %.2f attendu.\n",
                   minExclus ? "strictement superieur a" : "superieur ou egal a", min);
            continue;
        }
        return v;
    }
}

/* ================================================================== */
/*  FONCTIONS INTERNES (PRODUITS)                                     */
/* ================================================================== */

/* Double la capacité du catalogue si nécessaire. En cas d'échec de realloc,
   l'ancien tableau reste valide (on n'écrase pas b->produits). */
static int assurerCapaciteProduits(Boutique *b)
{
    if (b->nbProduits < b->capaciteProduits) return 0;

    int nouvelle = (b->capaciteProduits > 0) ? b->capaciteProduits * 2
                                             : CAPACITE_INITIALE_PRODUITS;
    Produit *tmp = (Produit *)realloc(b->produits, (size_t)nouvelle * sizeof(Produit));
    if (tmp == NULL) return -1;

    b->produits = tmp;
    b->capaciteProduits = nouvelle;
    return 0;
}

/* Un produit est « utilisé » s'il figure dans une commande non annulée
   (clients désactivés inclus). */
static int produitUtilise(const Boutique *b, const char *reference)
{
    for (int i = 0; i < b->nbClients; i++) {
        const Client *cl = &b->clients[i];
        for (int j = 0; j < cl->nbCommandes; j++) {
            const Commande *c = &cl->commandes[j];
            if (strcmp(c->statut, STATUT_ANNULEE) == 0) continue;
            for (int k = 0; k < c->nbLignes; k++)
                if (strcmp(c->lignes[k].refProduit, reference) == 0) return 1;
        }
    }
    return 0;
}

static void versMinuscules(char *dst, const char *src, size_t taille)
{
    size_t i;
    for (i = 0; i + 1 < taille && src[i] != '\0'; i++)
        dst[i] = (char)tolower((unsigned char)src[i]);
    dst[i] = '\0';
}

/* Recherche insensible à la casse d'un mot-clé dans un texte. */
static int contientMotCle(const char *texte, const char *mot)
{
    char t[LG_DESIGNATION], m[LG_DESIGNATION];
    versMinuscules(t, texte, sizeof t);
    versMinuscules(m, mot, sizeof m);
    return strstr(t, m) != NULL;
}

static void afficherEnTeteProduits(void)
{
    printf("\n%-12s %-24s %-14s %10s %6s %6s %12s %s\n",
           "Reference", "Designation", "Categorie", "Prix HT", "Stock", "Seuil",
           "Valeur stock", "Alerte");
    printf("-----------------------------------------------------------------------------------------------\n");
}

static void afficherLigneProduit(const Produit *p)
{
    double valeur = (double)p->prixUnitaireHT * p->quantiteStock;
    printf("%-12s %-24.24s %-14.14s %10.2f %6d %6d %12.2f %s\n",
           p->reference, p->designation, p->categorie, p->prixUnitaireHT,
           p->quantiteStock, p->seuilAlerte, valeur,
           (p->quantiteStock <= p->seuilAlerte) ? "<< STOCK BAS" : "");
}

/* ================================================================== */
/*  RECHERCHE                                                         */
/* ================================================================== */

int indexProduit(const Boutique *b, const char *reference)
{
    for (int i = 0; i < b->nbProduits; i++)
        if (strcmp(b->produits[i].reference, reference) == 0) return i;
    return -1;
}

/* Attention : le pointeur renvoyé devient invalide si le catalogue est
   ensuite agrandi (realloc). Ne pas le conserver après un ajout. */
Produit *trouverProduitActif(Boutique *b, const char *reference)
{
    int i = indexProduit(b, reference);
    if (i < 0 || !b->produits[i].actif) return NULL;
    return &b->produits[i];
}

/* ================================================================== */
/*  AJOUT                                                             */
/* ================================================================== */

/* Ajout sans saisie (initialisation, tests). Unicité contrôlée sur TOUS
   les produits, y compris désactivés. */
int ajouterProduitDonnees(Boutique *b, const Produit *p)
{
    if (indexProduit(b, p->reference) != -1) return PRODUIT_DOUBLON;
    if (assurerCapaciteProduits(b) != 0)     return PRODUIT_MEMOIRE;

    b->produits[b->nbProduits++] = *p;
    return PRODUIT_OK;
}

void ajouterProduit(Boutique *b)
{
    Produit p;
    memset(&p, 0, sizeof p);

    printf("\n--- Ajout d'un produit ---\n");

    for (;;) {
        lireChaine("Reference (ex. PRD-0009) : ", p.reference, sizeof p.reference);
        if (indexProduit(b, p.reference) == -1) break;
        printf("Erreur : cette reference existe deja (meme desactivee).\n");
    }
    lireChaine("Designation : ", p.designation, sizeof p.designation);
    lireChaine("Categorie   : ", p.categorie, sizeof p.categorie);
    p.prixUnitaireHT = (float)lireReel("Prix unitaire HT (> 0) : ", 0.0, 1);
    p.quantiteStock  = lireEntier("Stock initial (>= 0)        : ", 0, STOCK_MAX);
    p.seuilAlerte    = lireEntier("Seuil d'alerte (>= 0)       : ", 0, STOCK_MAX);
    p.actif = 1;

    switch (ajouterProduitDonnees(b, &p)) {
        case PRODUIT_OK:      printf("Produit %s ajoute.\n", p.reference); break;
        case PRODUIT_DOUBLON: printf("Erreur : reference deja utilisee.\n"); break;
        default:              printf("Erreur : memoire insuffisante, produit non ajoute.\n"); break;
    }
}

/* ================================================================== */
/*  MISE À JOUR                                                       */
/* ================================================================== */

/* Le prix modifié n'affecte pas les commandes existantes : leurs lignes
   conservent le prix figé au moment de la vente. */
void mettreAJourProduit(Boutique *b)
{
    char ref[LG_REFERENCE];

    printf("\n--- Mise a jour d'un produit ---\n");
    lireChaine("Reference du produit : ", ref, sizeof ref);

    Produit *p = trouverProduitActif(b, ref);
    if (p == NULL) {
        printf("Erreur : aucun produit actif avec la reference %s.\n", ref);
        return;
    }

    printf("%s - %s | prix : %.2f | stock : %d | seuil : %d\n",
           p->reference, p->designation, p->prixUnitaireHT,
           p->quantiteStock, p->seuilAlerte);

    p->prixUnitaireHT = (float)lireReel("Nouveau prix HT (> 0)       : ", 0.0, 1);
    p->quantiteStock  = lireEntier("Nouveau stock (>= 0)        : ", 0, STOCK_MAX);
    p->seuilAlerte    = lireEntier("Nouveau seuil d'alerte (>=0): ", 0, STOCK_MAX);

    printf("Produit %s mis a jour.\n", p->reference);
}

/* ================================================================== */
/*  SUPPRESSION LOGIQUE                                               */
/* ================================================================== */

void supprimerProduit(Boutique *b)
{
    char ref[LG_REFERENCE];

    printf("\n--- Suppression d'un produit ---\n");
    lireChaine("Reference du produit : ", ref, sizeof ref);

    Produit *p = trouverProduitActif(b, ref);
    if (p == NULL) {
        printf("Erreur : aucun produit actif avec la reference %s.\n", ref);
        return;
    }
    if (produitUtilise(b, ref)) {
        printf("Suppression refusee : %s figure dans une commande non annulee.\n", ref);
        return;
    }
    p->actif = 0;   /* suppression logique : l'enregistrement reste en memoire */
    printf("Produit %s supprime (logiquement).\n", ref);
}

/* ================================================================== */
/*  AFFICHAGES                                                        */
/* ================================================================== */

void afficherProduits(const Boutique *b)
{
    double total = 0.0;
    int n = 0;

    printf("\n=== CATALOGUE DES PRODUITS ===");
    afficherEnTeteProduits();

    for (int i = 0; i < b->nbProduits; i++) {
        const Produit *p = &b->produits[i];
        if (!p->actif) continue;
        afficherLigneProduit(p);
        total += (double)p->prixUnitaireHT * p->quantiteStock;
        n++;
    }

    if (n == 0)
        printf("(catalogue vide)\n");
    else
        printf("\n%d produit(s) - valorisation totale du stock : %.2f EUR HT\n", n, total);
}

void rechercherProduit(const Boutique *b)
{
    printf("\n--- Recherche d'un produit ---\n");
    printf("1. Par reference exacte\n2. Par mot-cle dans la designation\n");
    int choix = lireEntier("Votre choix : ", 1, 2);
    int trouves = 0;

    if (choix == 1) {
        char ref[LG_REFERENCE];
        lireChaine("Reference : ", ref, sizeof ref);
        int i = indexProduit(b, ref);
        if (i >= 0 && b->produits[i].actif) {
            afficherEnTeteProduits();
            afficherLigneProduit(&b->produits[i]);
            trouves = 1;
        } else if (i >= 0) {
            printf("Ce produit existe mais a ete supprime (desactive).\n");
            return;
        }
    } else {
        char mot[LG_DESIGNATION];
        lireChaine("Mot-cle : ", mot, sizeof mot);
        for (int i = 0; i < b->nbProduits; i++) {
            const Produit *p = &b->produits[i];
            if (!p->actif || !contientMotCle(p->designation, mot)) continue;
            if (trouves == 0) afficherEnTeteProduits();
            afficherLigneProduit(p);
            trouves++;
        }
    }

    if (trouves == 0) printf("Aucun produit trouve.\n");
}

void afficherAlertesStock(const Boutique *b)
{
    int n = 0;

    printf("\n=== ALERTES DE STOCK ===");
    for (int i = 0; i < b->nbProduits; i++) {
        const Produit *p = &b->produits[i];
        if (!p->actif || p->quantiteStock > p->seuilAlerte) continue;
        if (n == 0) afficherEnTeteProduits();
        afficherLigneProduit(p);
        n++;
    }
    if (n == 0) printf("\nAucun produit en alerte de stock.\n");
    else        printf("\n%d produit(s) a reapprovisionner.\n", n);
}

/* ================================================================== */
/*  GESTION DU STOCK                                                  */
/* ================================================================== */

int retirerStock(Produit *p, int quantite)
{
    if (quantite <= 0 || quantite > p->quantiteStock) return PRODUIT_STOCK_INSUFFISANT;
    p->quantiteStock -= quantite;
    return PRODUIT_OK;
}

void reintegrerStock(Produit *p, int quantite)
{
    if (quantite > 0) p->quantiteStock += quantite;
}
