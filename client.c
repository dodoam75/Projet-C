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
            return i;
        }
    }
    return -1;
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




/* Modifier un client */



/* Supprimer un client : suppression logique */



/* Afficher la liste des clients */



/* Ajouter des points de fidelite */

void ajouterPointsFidelite(Boutique *b, int idClient, int points) {
}


/* Retirer des points de fidelite */

void retirerPointsFidelite(Boutique *b, int idClient, int points) {


