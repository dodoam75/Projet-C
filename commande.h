/* ============================================================
 * commande.h - Interface du module Commandes
 * ------------------------------------------------------------
 * ROLE : declare la creation des commandes, la gestion des lignes, le
 *        changement de statut, l'annulation et le calcul des montants.
 * UTILISE PAR : main.c (menu), initialisation.c (jeu de test, via
 *        ajouterLigne et calculCommande), statistique.c.
 * ============================================================ */
/* ============================================================
 * commande.h - Interface du module Commandes
 * ------------------------------------------------------------
 * ROLE : declare la creation des commandes, la gestion des lignes, le
 *        changement de statut, l'annulation et le calcul des montants.
 * UTILISE PAR : main.c (menu), initialisation.c (jeu de test, via
 *        ajouterLigne et calculCommande), statistique.c.
 * ============================================================ */

#ifndef COMMANDE_H
#define COMMANDE_H

#include "types.h"

/* Créer une nouvelle commande pour un client */
int creerCommande(Boutique *boutique, int idClient, float montantTotal);

/* Rechercher une commande */
Commande *chercherCommande(Boutique *boutique, int idClient, int idCommande);

/* Modifier le statut d'une commande */
int changerStatutCommande(Boutique *boutique, int idClient,
                          int numeroCommande, const char *nouveauStatut);

/* Annuler une commande */
int annulerCommande(Boutique *boutique, int idClient, int idCommande);

/* Afficher les commandes d'un client */
void afficherCommandes(Boutique *boutique, int idClient);

/* Afficher une commande précise */
void afficherCommande(Commande *commande);

void menuCreerCommande(Boutique *boutique);

#endif
