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

int modifierClient(Boutique *b, int idClient, Client modification) {

    int index = trouverClient(b, idClient);

    if (index == -1 || b->clients[index].actif == 0) {

        printf("Client introuvable.\n");
        return 0;
    }

    if (emailExiste(b, modification.email) &&
        strcmp(b->clients[index].email, modification.email) != 0) {

        printf("Erreur : email deja utilise.\n");
        return 0;
    }

    if (strlen(modification.nom) == 0 ||
        strlen(modification.prenom) == 0 ||
        strlen(modification.email) == 0 ||
        strlen(modification.telephone) == 0) {

        printf("Erreur : informations manquantes.\n");
        return 0;
    }

    strcpy(b->clients[index].nom, modification.nom);
    strcpy(b->clients[index].prenom, modification.prenom);
    strcpy(b->clients[index].email, modification.email);
    strcpy(b->clients[index].telephone, modification.telephone);

    b->clients[index].adresse = modification.adresse;

    printf("Client modifie avec succes.\n");

    return 1;
}


/* Supprimer un client : suppression logique */



/* Afficher la liste des clients */



/* Ajouter des points de fidelite */

void ajouterPointsFidelite(Boutique *b, int idClient, int points) {
}


/* Retirer des points de fidelite */

void retirerPointsFidelite(Boutique *b, int idClient, int points) {


