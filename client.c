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

Client *trouverClient(Boutique *b, int id) {
    for (int i = 0; i < b->nbClients; i++) {
        if (b->clients[i].id == id) {
            return &b->clients[i];
        }
    }
    return NULL;
}

void ajouterClient(Boutique *b, const char *nom, const char *prenom, const char *email, const char *adresse) {
    for (i = 0; i < b->nbClients; i++) {
        if (strcmp(b->clients[i].email, email) == 0) {
            printf("Erreur : un client avec cet email existe déjà.\n");
            return;
        }
    }

    b->clients = realloc(b->clients, (b->nbClients + 1) * sizeof(Client));
    if (b->clients == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    Client *c = &b->clients[b->nbClients];

c->id = b->idClientSuivant;
b->idClientSuivant++;

strcpy(c->nom, nom);
strcpy(c->prenom, prenom);
strcpy(c->email, email);
strcpy(c->adresse, adresse);

c->pointsFidelite = 0;
c->actif = 1;

b->nbClients++;
}