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
#include "commande.h"


/* Rechercher un client dans la boutique */
static Client *chercherClient(Boutique *boutique, int idClient)
{
    int i;

    if (boutique == NULL)
        return NULL;

    for (i = 0; i < boutique->nbClients; i++)
    {
        if (boutique->clients[i].idClient == idClient &&
            boutique->clients[i].actif == 1)
        {
            return &boutique->clients[i];
        }
    }

    return NULL;
}


/* Rechercher une commande */
Commande *chercherCommande(Boutique *boutique, int idClient, int idCommande)
{
    Client *client;
    int i;

    client = chercherClient(boutique, idClient);

    if (client == NULL)
        return NULL;

    for (i = 0; i < client->nbCommandes; i++)
    {
        if (client->commandes[i].idCommande == idCommande)
        {
            return &client->commandes[i];
        }
    }

    return NULL;
}


/* Créer une nouvelle commande */
int creerCommande(Boutique *boutique, int idClient, float montantTotal)
{
    Client *client;
    Commande *nouveauTableau;
    Commande nouvelle;
    int i;
    int nouvelId = 1;

    if (boutique == NULL || montantTotal < 0)
        return 0;

    client = chercherClient(boutique, idClient);

    if (client == NULL)
        return 0;

    /* Vérifier si le tableau de commandes doit être agrandi */
    if (client->nbCommandes >= client->capaciteCommandes)
    {
        int nouvelleCapacite;

        if (client->capaciteCommandes == 0)
            nouvelleCapacite = 2;
        else
            nouvelleCapacite = client->capaciteCommandes * 2;

        nouveauTableau = realloc(
            client->commandes,
            nouvelleCapacite * sizeof(Commande)
        );

        if (nouveauTableau == NULL)
            return 0;

        client->commandes = nouveauTableau;
        client->capaciteCommandes = nouvelleCapacite;
    }

    /* Trouver un nouvel identifiant de commande */
    for (i = 0; i < boutique->nbClients; i++)
    {
        Client *c = &boutique->clients[i];
        int j;

        for (j = 0; j < c->nbCommandes; j++)
        {
            if (c->commandes[j].idCommande >= nouvelId)
                nouvelId = c->commandes[j].idCommande + 1;
        }
    }

    /* Remplir la nouvelle commande */
    nouvelle.idCommande = nouvelId;
    nouvelle.idClient = idClient;
    nouvelle.montantTotal = montantTotal;
    nouvelle.statut = EN_ATTENTE;

    /* Ajouter la commande au tableau du client */
    client->commandes[client->nbCommandes] = nouvelle;
    client->nbCommandes++;

    return nouvelId;
}


/* Modifier le statut d'une commande */
int changerStatutCommande(Boutique *boutique, int idClient,
                          int idCommande, StatutCommande nouveauStatut)
{
    Commande *commande;

    commande = chercherCommande(boutique, idClient, idCommande);

    if (commande == NULL)
        return 0;

    /* Vérifier les transitions autorisées */
    if (commande->statut == EN_ATTENTE && nouveauStatut == EN_COURS)
    {
        commande->statut = nouveauStatut;
        return 1;
    }

    if (commande->statut == EN_COURS && nouveauStatut == LIVREE)
    {
        commande->statut = nouveauStatut;
        return 1;
    }

    return 0;
}


/* Annuler une commande */
int annulerCommande(Boutique *boutique, int idClient, int idCommande)
{
    Commande *commande;

    commande = chercherCommande(boutique, idClient, idCommande);

    if (commande == NULL)
        return 0;

    /* Une commande déjà livrée ou annulée ne peut pas être annulée */
    if (commande->statut == LIVREE || commande->statut == ANNULEE)
        return 0;

    commande->statut = ANNULEE;

    return 1;
}


/* Afficher une commande précise */
void afficherCommande(Commande *commande)
{
    if (commande == NULL)
        return;

    printf("\n--- COMMANDE ---\n");

    printf("Numero : %d\n", commande->idCommande);
    printf("Client : %d\n", commande->idClient);
    printf("Montant total : %.2f euros\n", commande->montantTotal);

    printf("Statut : ");

    switch (commande->statut)
    {
        case EN_ATTENTE:
            printf("En attente\n");
            break;

        case EN_COURS:
            printf("En cours\n");
            break;

        case LIVREE:
            printf("Livree\n");
            break;

        case ANNULEE:
            printf("Annulee\n");
            break;

        default:
            printf("Statut inconnu\n");
            break;
    }
}


/* Afficher toutes les commandes d'un client */
void afficherCommandes(Boutique *boutique, int idClient)
{
    Client *client;
    int i;

    client = chercherClient(boutique, idClient);

    if (client == NULL)
    {
        printf("Client introuvable.\n");
        return;
    }

    if (client->nbCommandes == 0)
    {
        printf("Ce client n'a aucune commande.\n");
        return;
    }

    for (i = 0; i < client->nbCommandes; i++)
    {
        afficherCommande(&client->commandes[i]);
    }
}
