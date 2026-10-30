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

// Recherche un client avec son identifiant
int trouverClient(Boutique *b, int idClient);
// Vérifie si un email existe déjà
int emailExiste(Boutique *b, char email[]);
// Ajouter un client
int ajouterClient(Boutique *b, Client nouveau);
// Modifier un client
int modifierClient(Boutique *b, int idClient, Client modification);
// Supprimer un client
int supprimerClient(Boutique *b, int idClient);
// Afficher tous les clients
void afficherClients(Boutique *b);
// Afficher un client et son historique d'achats
void afficherClient(Boutique *b, int idClient);
// Ajouter des points de fidélité
void ajouterPoints(Boutique *b, int idClient, int points);
// Retirer des points de fidélité
void retirerPoints(Boutique *b, int idClient, int points);
#endif
