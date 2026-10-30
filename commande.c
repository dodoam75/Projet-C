#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
Commande *chercherCommande(Boutique *boutique, int idClient,
                           int numeroCommande)
{
    Client *client;
    int i;

    client = chercherClient(boutique, idClient);

    if (client == NULL)
        return NULL;

    for (i = 0; i < client->nbCommandes; i++)
    {
        if (client->commandes[i].numero == numeroCommande)
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

    if (boutique == NULL || montantTotal < 0)
        return 0;

    client = chercherClient(boutique, idClient);

    if (client == NULL)
        return 0;

    /* Agrandir le tableau si nécessaire */
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

    /* Initialiser tous les champs à zéro */
    memset(&nouvelle, 0, sizeof(Commande));

    /* Attribuer le numéro depuis la boutique */
    if (boutique->numeroSuivant <= 0)
        boutique->numeroSuivant = 1;

    nouvelle.numero = boutique->numeroSuivant;
    nouvelle.idClient = idClient;

    /* Pour cette version simplifiée, on stocke le montant en TTC */
    nouvelle.montantTTC = montantTotal;

    /* Une nouvelle commande commence EN_COURS */
    strcpy(nouvelle.statut, "EN_COURS");

    /* Ajouter la commande au tableau du client */
    client->commandes[client->nbCommandes] = nouvelle;
    client->nbCommandes++;

    /* Préparer le prochain numéro */
    boutique->numeroSuivant++;

    return nouvelle.numero;
}


/* Modifier le statut d'une commande */
int changerStatutCommande(Boutique *boutique, int idClient,
                          int numeroCommande, const char *nouveauStatut)
{
    Commande *commande;

    if (nouveauStatut == NULL)
        return 0;

    commande = chercherCommande(boutique, idClient, numeroCommande);

    if (commande == NULL)
        return 0;

    /* EN_COURS -> EXPEDIEE */
    if (strcmp(commande->statut, "EN_COURS") == 0 &&
        strcmp(nouveauStatut, "EXPEDIEE") == 0)
    {
        strcpy(commande->statut, "EXPEDIEE");
        return 1;
    }

    /* EXPEDIEE -> LIVREE */
    if (strcmp(commande->statut, "EXPEDIEE") == 0 &&
        strcmp(nouveauStatut, "LIVREE") == 0)
    {
        strcpy(commande->statut, "LIVREE");
        return 1;
    }

    return 0;
}


/* Annuler une commande */
int annulerCommande(Boutique *boutique, int idClient, int numeroCommande)
{
    Commande *commande;

    commande = chercherCommande(boutique, idClient, numeroCommande);

    if (commande == NULL)
        return 0;

    /* Seule une commande EN_COURS peut être annulée */
    if (strcmp(commande->statut, "EN_COURS") != 0)
        return 0;

    strcpy(commande->statut, "ANNULEE");

    return 1;
}


/* Afficher une commande précise */
void afficherCommande(Commande *commande)
{
    if (commande == NULL)
        return;

    printf("\n--- COMMANDE ---\n");

    printf("Numero : %d\n", commande->numero);
    printf("Client : %d\n", commande->idClient);
    printf("Montant TTC : %.2f euros\n", commande->montantTTC);
    printf("Statut : %s\n", commande->statut);
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
void menuCreerCommande(Boutique *boutique)
{
    int idClient;
    float montantTotal;
    int numero;

    printf("\n===== CREATION D'UNE COMMANDE =====\n");

    printf("Identifiant du client : ");
    scanf("%d", &idClient);

    printf("Montant de la commande : ");
    scanf("%f", &montantTotal);

    numero = creerCommande(boutique, idClient, montantTotal);

    if (numero != 0)
    {
        printf("Commande creee avec succes !\n");
        printf("Numero de commande : %d\n", numero);
    }
    else
    {
        printf("Erreur : impossible de creer la commande.\n");
    }
}
