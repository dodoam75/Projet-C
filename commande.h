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

int creerCommande(Boutique *b, int idClient, Date date,
                  const char *refProduit, int quantite);

int ajouterLigneCommande(Boutique *b, int numero,
                         const char *refProduit, int quantite);

int supprimerLigneCommande(Boutique *b, int numero,
                           const char *refProduit);

void calculerCommande(Commande *c);

int changerStatutCommande(Boutique *b, int numero,
                          const char *nouveauStatut);

int annulerCommande(Boutique *b, int numero);

void afficherCommande(Boutique *b, int numero);

#endif


