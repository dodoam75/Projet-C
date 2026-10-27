/* ============================================================
 * client.h - Interface du module Clients
 * ------------------------------------------------------------
 * ROLE : declare le CRUD des clients, la recherche par identifiant et la
 *        gestion des points de fidelite.
 * UTILISE PAR : main.c (menu), commande.c (points de fidelite, ajout
 *        d'une commande au client), statistique.c (palmares clients).
 * ============================================================ */
#ifndef CLIENT_H
#define CLIENT_H

#include "types.h"

/* Retourne l'indice du client (ou -1 si introuvable) */
int  trouverClient(const Boutique *b, int idClient);

/* CRUD (retournent 1 si succes, 0 sinon) */
int  ajouterClient(Boutique *b);
int  mettreAJourClient(Boutique *b);
int  supprimerClient(Boutique *b);
void afficherClients(const Boutique *b);
void afficherClient(const Boutique *b);

/* Fidelite */
void ajouterPointsFidelite(Client *c, int points);
void retirerPointsFidelite(Client *c, int points);

#endif /* CLIENT_H */
