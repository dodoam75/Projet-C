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
#define MAX_NOM 50
#define MAX_PRENOM 50
#define MAX_EMAIL 100
#define MAX_TELEPHONE 20

typedef struct {
    char rue[100];
    char codePostal[10];
    char ville[50];
    char pays[50];
} Adresse;

typedef enum {
    EN_ATTENTE,
    EN_COURS,
    LIVREE,
    ANNULEE
} StatutCommande;

typedef struct {
    int idCommande;
    int idClient;
    float montantTotal;
    StatutCommande statut;
} Commande;

typedef struct {
    int idClient;
    char nom[MAX_NOM];
    char prenom[MAX_PRENOM];
    char email[MAX_EMAIL];
    char telephone[MAX_TELEPHONE];

    Adresse adresse;

    int pointsFidelite;

    Commande *commandes;
    int nbCommandes;
    int capaciteCommandes;

    int actif;
} Client;

typedef struct {
    Client *clients;
    int nbClients;
    int capaciteClients;
    int idClientSuivant;
} Boutique;

#endif