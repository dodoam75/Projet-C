/* ============================================================
 * produit.h - Interface du module Catalogue produits
 * ------------------------------------------------------------
 * ROLE : declare le CRUD des produits (ajouter, modifier, supprimer,
 *        lister, rechercher), la recherche par reference et les alertes
 *        de stock.
 * UTILISE PAR : main.c (menu), commande.c (lecture/mise a jour du stock),
 *        statistique.c (palmares produits).
 * ============================================================ */
#ifndef PRODUIT_H
#define PRODUIT_H

#include <stddef.h>

/* ================================================================== */
/*  Constantes                                                        */
/* ================================================================== */

#define LG_REFERENCE    12
#define LG_DESIGNATION  60
#define LG_CATEGORIE    30
#define LG_STATUT       20

#define STATUT_EN_COURS "EN_COURS"
#define STATUT_EXPEDIEE "EXPEDIEE"
#define STATUT_LIVREE   "LIVREE"
#define STATUT_ANNULEE  "ANNULEE"

/* ================================================================== */
/*  Structures de données                                             */
/* ================================================================== */

typedef struct { int jour, mois, annee; } Date;

typedef struct {
    char rue[80];
    char ville[50];
    char codePostal[6];
    char pays[50];
} Adresse;

typedef struct {
    char  reference[LG_REFERENCE];
    char  designation[LG_DESIGNATION];
    char  categorie[LG_CATEGORIE];
    float prixUnitaireHT;
    int   quantiteStock;
    int   seuilAlerte;
    int   actif;                 /* 1 = actif, 0 = supprimé logiquement */
} Produit;

typedef struct {
    char  refProduit[LG_REFERENCE];
    char  designation[LG_DESIGNATION];
    int   quantite;
    float prixUnitaireHT;
    float sousTotalHT;
} LigneCommande;

typedef struct {
    int    numero;
    int    idClient;
    Date   dateCommande;
    char   statut[LG_STATUT];
    int    nbLignes;
    int    capaciteLignes;
    LigneCommande *lignes;
    float  montantBrutHT;
    float  tauxRemise;
    float  montantRemise;
    float  montantHT;
    float  montantTVA;
    float  montantTTC;
    float  fraisPort;
    Adresse adresseLivraison;
} Commande;

typedef struct {
    int     idClient;
    char    nom[50];
    char    prenom[50];
    char    email[80];
    char    telephone[15];
    Adresse adresse;
    int     pointsFidelite;
    int     nbCommandes;
    int     capaciteCommandes;
    Commande *commandes;
    int     actif;
} Client;

typedef struct {
    char     nom[50];
    Produit *produits;
    int      nbProduits;
    int      capaciteProduits;
    Client  *clients;
    int      nbClients;
    int      capaciteClients;
    int      numeroSuivant;
    int      idClientSuivant;
} Boutique;

/* ================================================================== */
/*  Saisie sécurisée                                                  */
/* ================================================================== */

/* Lit une chaîne non vide de moins de `taille` caractères (redemande sinon). */
void   lireChaine(const char *invite, char *dest, size_t taille);
/* Lit un entier dans [min, max]. */
int    lireEntier(const char *invite, int min, int max);
/* Lit un réel >= min (ou > min si minExclus). Accepte la virgule. */
double lireReel(const char *invite, double min, int minExclus);

/* ================================================================== */
/*  Gestion des produits                                              */
/* ================================================================== */

/* Codes de retour */
enum {
    PRODUIT_OK = 0,
    PRODUIT_DOUBLON = -1,
    PRODUIT_MEMOIRE = -2,
    PRODUIT_STOCK_INSUFFISANT = -3
};

/* --- Recherche interne --- */
int      indexProduit(const Boutique *b, const char *reference);        /* -1 si absent (inclut les inactifs) */
Produit *trouverProduitActif(Boutique *b, const char *reference);       /* NULL si absent ou inactif */

/* --- Gestion du catalogue --- */
int  ajouterProduitDonnees(Boutique *b, const Produit *p);  /* sans saisie : initialisation */
void ajouterProduit(Boutique *b);                           /* avec saisie */
void mettreAJourProduit(Boutique *b);
void supprimerProduit(Boutique *b);                         /* suppression logique */
void afficherProduits(const Boutique *b);
void rechercherProduit(const Boutique *b);
void afficherAlertesStock(const Boutique *b);

/* --- Gestion du stock --- */
int  retirerStock(Produit *p, int quantite);     /* PRODUIT_OK ou PRODUIT_STOCK_INSUFFISANT */
void reintegrerStock(Produit *p, int quantite);

#endif
