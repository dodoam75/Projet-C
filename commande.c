/* ============================================================
 * commande.c - Implementation des commandes (module le plus complexe)
 * ------------------------------------------------------------
 * ROLE : - calculCommande : brut HT -> remise (paliers) -> HT -> TVA 20 %
 *          -> frais de port (offerts des 60 EUR HT brut) -> TTC
 *        - ajouterLigne : tableau dynamique de lignes (realloc), pas de
 *          doublon de reference, stock verifie sur la quantite cumulee
 *        - creerCommande : decremente le stock, credite les points
 *        - annulerCommande : seulement EN_COURS, reintegre stock + points
 *        - changerStatutCommande : EN_COURS -> EXPEDIEE -> LIVREE
 * ETAT : calculerTauxRemise() et trouverCommande() sont faits.
 * ============================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commande.h"

static Client *chercherClient(Boutique *b, int idClient)
{
    int i;

    for (i = 0; i < b->nbClients; i++)
    {
        if (b->clients[i].idClient == idClient)
            return &b->clients[i];
    }

    return NULL;
}

static Produit *chercherProduit(Boutique *b, const char *reference)
{
    int i;

    for (i = 0; i < b->nbProduits; i++)
    {
        if (strcmp(b->produits[i].reference, reference) == 0
            && b->produits[i].actif == 1)
        {
            return &b->produits[i];
        }
    }

    return NULL;
}

static Commande *chercherCommande(Boutique *b, int numero)
{
    int i, j;

    for (i = 0; i < b->nbClients; i++)
    {
        Client *cl = &b->clients[i];

        for (j = 0; j < cl->nbCommandes; j++)
        {
            if (cl->commandes[j].numero == numero)
                return &cl->commandes[j];
        }
    }

    return NULL;
}

void calculerCommande(Commande *c)
{
    int i;

    c->montantBrutHT = 0;

    for (i = 0; i < c->nbLignes; i++)
    {
        c->lignes[i].sousTotalHT =
            c->lignes[i].quantite *
            c->lignes[i].prixUnitaireHT;

        c->montantBrutHT += c->lignes[i].sousTotalHT;
    }
//Calcule de la remise 
    if (c->montantBrutHT >= 600)
        c->tauxRemise = 15;
    else if (c->montantBrutHT >= 300)
        c->tauxRemise = 10;
    else if (c->montantBrutHT >= 100)
        c->tauxRemise = 5;
    else
        c->tauxRemise = 0;

    c->montantRemise =
        c->montantBrutHT * c->tauxRemise / 100;

    c->montantHT =
        c->montantBrutHT - c->montantRemise;

    c->montantTVA = c->montantHT * 0.20f;

    //Calcule des frait de port
    if (c->montantBrutHT >= 60)
        c->fraisPort = 0;
    else
        c->fraisPort = 5.90f;

    c->montantTTC =
        c->montantHT + c->montantTVA + c->fraisPort;
}

int creerCommande(Boutique *b, int idClient, Date date,
                  const char *refProduit, int quantite)
{
    Client *cl;
    Produit *p;
    Commande nouvelle;
    Commande *temp;
    LigneCommande *ligne;

    if (b == NULL || refProduit == NULL || quantite <= 0)
        return 0;

    cl = chercherClient(b, idClient);

    if (cl == NULL || cl->actif != 1)
    {
        printf("Client introuvable.\n");
        return 0;
    }

    p = chercherProduit(b, refProduit);

    if (p == NULL)
    {
        printf("Produit introuvable.\n");
        return 0;
    }

    if (p->quantiteStock < quantite)
    {
        printf("Stock insuffisant.\n");
        return 0;
    }

    /* Verifier la capacite du tableau de commandes */
    if (cl->nbCommandes == cl->capaciteCommandes)
    {
        int nouvelleCapacite =
            (cl->capaciteCommandes == 0)
            ? 2 : cl->capaciteCommandes * 2;

        temp = realloc(cl->commandes,
                       nouvelleCapacite * sizeof(Commande));

        if (temp == NULL)
            return 0;

        cl->commandes = temp;
        cl->capaciteCommandes = nouvelleCapacite;
    }

    /* Initialisation de la nouvelle commande */
    memset(&nouvelle, 0, sizeof(Commande));

    nouvelle.numero = b->numeroSuivant;
    nouvelle.idClient = idClient;
    nouvelle.dateCommande = date;

    strcpy(nouvelle.statut, "EN_COURS");

    nouvelle.capaciteLignes = 2;
    nouvelle.nbLignes = 0;

    nouvelle.lignes = malloc(
        nouvelle.capaciteLignes * sizeof(LigneCommande));

    if (nouvelle.lignes == NULL)
        return 0;

    /* Creation de la premiere ligne */
    ligne = &nouvelle.lignes[0];

    strcpy(ligne->refProduit, p->reference);
    strcpy(ligne->designation, p->designation);

    ligne->quantite = quantite;
    ligne->prixUnitaireHT = p->prixUnitaireHT;
    ligne->sousTotalHT = quantite * p->prixUnitaireHT;

    nouvelle.nbLignes = 1;

    /* Copier l'adresse du client */
    nouvelle.adresseLivraison = cl->adresse;

    calculerCommande(&nouvelle);

    /* Enregistrer la commande */
    cl->commandes[cl->nbCommandes] = nouvelle;
    cl->nbCommandes++;

    /* Mettre a jour le stock */
    p->quantiteStock -= quantite;

    /* Attribution des points de fidelite */
    cl->pointsFidelite += (int)(nouvelle.montantTTC / 10);

    b->numeroSuivant++;

    printf("Commande creee avec succes. Numero : %d\n",
           nouvelle.numero);

    return 1;
}

/* Ajouter une ligne a une commande */
int ajouterLigneCommande(Boutique *b, int numero,
                         const char *refProduit, int quantite)
{
    Commande *c;
    Produit *p;
    LigneCommande *temp;
    int i;
    int anciensPoints;
    int nouveauxPoints;

    if (b == NULL || refProduit == NULL || quantite <= 0)
        return 0;

    c = chercherCommande(b, numero);

    if (c == NULL || strcmp(c->statut, "EN_COURS") != 0)
        return 0;

    p = chercherProduit(b, refProduit);

    if (p == NULL || p->quantiteStock < quantite)
        return 0;

    /* Une seule ligne par produit dans une commande */
    for (i = 0; i < c->nbLignes; i++)
    {
        if (strcmp(c->lignes[i].refProduit,
                   refProduit) == 0)
        {
            printf("Ce produit existe deja dans la commande.\n");
            return 0;
        }
    }

    anciensPoints = (int)(c->montantTTC / 10);

    /* Agrandir le tableau si necessaire */
    if (c->nbLignes == c->capaciteLignes)
    {
        int nouvelleCapacite = c->capaciteLignes * 2;

        temp = realloc(c->lignes,
                       nouvelleCapacite * sizeof(LigneCommande));

        if (temp == NULL)
            return 0;

        c->lignes = temp;
        c->capaciteLignes = nouvelleCapacite;
    }

    /* Ajouter la ligne */
    strcpy(c->lignes[c->nbLignes].refProduit, p->reference);
    strcpy(c->lignes[c->nbLignes].designation, p->designation);

    c->lignes[c->nbLignes].quantite = quantite;
    c->lignes[c->nbLignes].prixUnitaireHT = p->prixUnitaireHT;

    c->nbLignes++;

    p->quantiteStock -= quantite;

    calculerCommande(c);

    nouveauxPoints = (int)(c->montantTTC / 10);

    /* Mettre a jour les points du client */
    for (i = 0; i < b->nbClients; i++)
    {
        int j;

        for (j = 0; j < b->clients[i].nbCommandes; j++)
        {
            if (b->clients[i].commandes[j].numero == numero)
            {
                b->clients[i].pointsFidelite +=
                    nouveauxPoints - anciensPoints;
                return 1;
            }
        }
    }

    return 1;
}

/* Supprimer une ligne d'une commande */
int supprimerLigneCommande(Boutique *b, int numero,
                           const char *refProduit)
{
    Commande *c;
    Produit *p;
    int i, j;

    c = chercherCommande(b, numero);

    if (c == NULL || strcmp(c->statut, "EN_COURS") != 0)
        return 0;

    if (c->nbLignes <= 1)
    {
        printf("Une commande doit contenir au moins une ligne.\n");
        return 0;
    }

    for (i = 0; i < c->nbLignes; i++)
    {
        if (strcmp(c->lignes[i].refProduit, refProduit) == 0)
        {
            p = chercherProduit(b, refProduit);

            if (p != NULL)
                p->quantiteStock += c->lignes[i].quantite;

            for (j = i; j < c->nbLignes - 1; j++)
                c->lignes[j] = c->lignes[j + 1];

            c->nbLignes--;

            calculerCommande(c);

            return 1;
        }
    }

    return 0;
}

/* Changer le statut d'une commande */
int changerStatutCommande(Boutique *b, int numero,
                          const char *nouveauStatut)
{
    Commande *c;

    if (b == NULL || nouveauStatut == NULL)
        return 0;

    c = chercherCommande(b, numero);

    if (c == NULL)
        return 0;

    if (strcmp(c->statut, "EN_COURS") == 0 &&
        strcmp(nouveauStatut, "EXPEDIEE") == 0)
    {
        strcpy(c->statut, "EXPEDIEE");
        return 1;
    }

    if (strcmp(c->statut, "EXPEDIEE") == 0 &&
        strcmp(nouveauStatut, "LIVREE") == 0)
    {
        strcpy(c->statut, "LIVREE");
        return 1;
    }

    printf("Changement de statut non autorise.\n");
    return 0;
}

/* Annuler une commande et restituer le stock */
int annulerCommande(Boutique *b, int numero)
{
    Commande *c;
    Client *cl;
    Produit *p;
    int i;

    if (b == NULL)
        return 0;

    c = chercherCommande(b, numero);

    if (c == NULL)
        return 0;

    if (strcmp(c->statut, "EN_COURS") != 0)
    {
        printf("Seule une commande EN_COURS peut etre annulee.\n");
        return 0;
    }

    cl = chercherClient(b, c->idClient);

    if (cl == NULL)
        return 0;

    /* Restituer les produits au stock */
    for (i = 0; i < c->nbLignes; i++)
    {
        p = chercherProduit(b, c->lignes[i].refProduit);

        if (p != NULL)
            p->quantiteStock += c->lignes[i].quantite;
    }

    /* Retirer les points de fidelite */
    cl->pointsFidelite -= (int)(c->montantTTC / 10);

    if (cl->pointsFidelite < 0)
        cl->pointsFidelite = 0;

    strcpy(c->statut, "ANNULEE");

    printf("Commande annulee avec succes.\n");

    return 1;
}

/* Afficher le detail d'une commande */
void afficherCommande(Boutique *b, int numero)
{
    Commande *c;
    int i;

    c = chercherCommande(b, numero);

    if (c == NULL)
    {
        printf("Commande introuvable.\n");
        return;
    }

    printf("\n========== COMMANDE %d ==========\n", c->numero);

    printf("Client : %d\n", c->idClient);

    printf("Date : %02d/%02d/%04d\n",
           c->dateCommande.jour,
           c->dateCommande.mois,
           c->dateCommande.annee);

    printf("Statut : %s\n", c->statut);

    printf("\n--- Lignes de commande ---\n");

    for (i = 0; i < c->nbLignes; i++)
    {
        printf("%s | %s | Quantite : %d | Prix : %.2f EUR\n",
               c->lignes[i].refProduit,
               c->lignes[i].designation,
               c->lignes[i].quantite,
               c->lignes[i].prixUnitaireHT);

        printf("Sous-total : %.2f EUR\n",
               c->lignes[i].sousTotalHT);
    }

    printf("\n--- Facturation ---\n");

    printf("Montant brut HT : %.2f EUR\n", c->montantBrutHT);
    printf("Remise (%.0f%%) : %.2f EUR\n",
           c->tauxRemise, c->montantRemise);
    printf("Montant HT : %.2f EUR\n", c->montantHT);
    printf("TVA : %.2f EUR\n", c->montantTVA);
    printf("Frais de port : %.2f EUR\n", c->fraisPort);
    printf("TOTAL TTC : %.2f EUR\n", c->montantTTC);

    printf("=================================\n");
}

