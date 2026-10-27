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
#include "produit.h"
#include "utils.h"

int trouverProduit(const Boutique *b, const char *reference) {
    for (int i = 0; i < b->nbProduits; i++) {
        if (strcmp(b->produits[i].reference, reference) == 0)
            return i;
    }
    return -1;
}

int ajouterProduit(Boutique *b) {
    /* TODO : saisie, unicite de la reference (y compris inactifs),
       realloc si nbProduits == capaciteProduits (controle NULL) */
    (void)b;
    return 0;
}

int mettreAJourProduit(Boutique *b) {
    /* TODO : modifier prix, stock, seuil d'alerte */
    (void)b;
    return 0;
}

int supprimerProduit(Boutique *b) {
    /* TODO : suppression logique, refusee si utilise dans une commande non annulee */
    (void)b;
    return 0;
}

void afficherProduits(const Boutique *b) {
    /* TODO : liste du catalogue avec valorisation du stock */
    (void)b;
}

void rechercherProduit(const Boutique *b) {
    /* TODO : par reference exacte ou mot-cle de la designation */
    (void)b;
}

void afficherAlertesStock(const Boutique *b) {
    /* TODO : produits avec quantiteStock <= seuilAlerte */
    (void)b;
}
