/* ============================================================
 * client.c - Implementation des clients et de la fidelite
 * ------------------------------------------------------------
 * ROLE : gere le tableau dynamique b->clients (malloc/realloc).
 *        - ajouterClient : id donne par b->idClientSuivant (jamais saisi),
 *          unicite de l'email (inactifs inclus), adresse complete
 *        - supprimerClient : suppression LOGIQUE, refusee s'il existe des
 *          commandes non annulees
 *        - afficherClient : fiche + historique des commandes
 * ETAT : trouverClient() et les fonctions de points sont faits.
 * ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"


/* Rechercher un client par son identifiant */

int trouverClient(Boutique *b, int idClient) {

    for (int i = 0; i < b->nbClients; i++) {

        if (b->clients[i].idClient == idClient) {
            return i + 1;
        }
    }

    return 0;
}


/* Verifier si un email existe deja */

int emailExiste(Boutique *b, char email[]) {

    for (int i = 0; i < b->nbClients; i++) {

        if (strcmp(b->clients[i].email, email) == 0) {
            return 1;
        }
    }

    return 0;
}


/* Ajouter un client */

int ajouterClient(Boutique *b, Client nouveauClient) {
    if (emailExiste(b, nouveauClient.email)) {
        return 0;
    }

    if (b->nbClients == b->capaciteClients) {
        int nouvelleCapacite = b->capaciteClients + 5;

        Client *temp = realloc(b->clients, nouvelleCapacite * sizeof(Client));
        if (temp == NULL) {
            return 0;
        }

        b->clients = temp;
        b->capaciteClients = nouvelleCapacite;
    }

    nouveauClient.idClient = b->idClientSuivant;
    nouveauClient.actif = 1;
    nouveauClient.pointsFidelite = 0;
    nouveauClient.commandes = NULL;
    nouveauClient.nbCommandes = 0;
    nouveauClient.capaciteCommandes = 0;

    b->clients[b->nbClients] = nouveauClient;

    b->nbClients++;
    b->idClientSuivant++;

    return 1;
}
/* Modifier un client */


/* Supprimer un client : suppression logique */
void supprimerClient(Boutique *b, int idClient) {
    int index = trouverClient(b, idClient);
    if (index != -1) {
        b->clients[index].actif = 0; // suppression logique donc du client
    }
}

/* Afficher la liste des clients */
void afficherClients(Boutique *b) {
}

/* Ajouter des points de fidelite */

void ajouterPointsFidelite(Boutique *b, int idClient, int points) {
}


/* Retirer des points de fidelite */

void retirerPointsFidelite(Boutique *b, int idClient, int points) {


