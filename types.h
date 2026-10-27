/* ============================================================
 * types.h - Structures de donnees et constantes (FICHIER CENTRAL)
 * ------------------------------------------------------------
 * ROLE : definit les 7 structures du sujet (Date, Adresse, Produit,
 *        LigneCommande, Commande, Client, Boutique) et les constantes
 *        metier (TVA, frais de port, statuts, capacite initiale).
 * UTILISE PAR : tous les modules (inclus dans chaque .h).
 * POURQUOI : evite les inclusions circulaires entre client.h et commande.h.
 * A FAIRE : en general rien, sauf si vous ajoutez un champ (ex. code promo
 *          pour la partie creativite).
 * ============================================================ */
#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- Constantes ---- */
#define TVA_TAUX          20.0f
#define FRAIS_PORT        5.90f
#define SEUIL_PORT_OFFERT 60.0f
#define POINTS_PAR_TRANCHE 10.0f   /* 1 point par tranche de 10 EUR TTC */

#define STATUT_EN_COURS "EN_COURS"
#define STATUT_EXPEDIEE "EXPEDIEE"
#define STATUT_LIVREE   "LIVREE"
#define STATUT_ANNULEE  "ANNULEE"

#define CAPACITE_INITIALE 4        /* capacite de depart des tableaux dynamiques */

/* ---- Structures ---- */
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct {
    char rue[80];
    char ville[50];
    char codePostal[6];
    char pays[50];
} Adresse;

typedef struct {
    char  reference[12];
    char  designation[60];
    char  categorie[30];
    float prixUnitaireHT;
    int   quantiteStock;
    int   seuilAlerte;
    int   actif;
} Produit;

typedef struct {
    char  refProduit[12];
    char  designation[60];
    int   quantite;
    float prixUnitaireHT;
    float sousTotalHT;
} LigneCommande;

typedef struct {
    int            numero;
    int            idClient;
    Date           dateCommande;
    char           statut[20];
    int            nbLignes;
    int            capaciteLignes;
    LigneCommande *lignes;
    float          montantBrutHT;
    float          tauxRemise;
    float          montantRemise;
    float          montantHT;
    float          montantTVA;
    float          montantTTC;
    float          fraisPort;
    Adresse        adresseLivraison;
} Commande;

typedef struct {
    int       idClient;
    char      nom[50];
    char      prenom[50];
    char      email[80];
    char      telephone[15];
    Adresse   adresse;
    int       pointsFidelite;
    int       nbCommandes;
    int       capaciteCommandes;
    Commande *commandes;
    int       actif;
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

#endif /* TYPES_H */
