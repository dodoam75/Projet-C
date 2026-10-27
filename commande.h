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

/* Calculs : brut -> remise -> HT -> TVA -> port -> TTC */
float calculerTauxRemise(float montantBrutHT);
void  calculCommande(Commande *c);

/* Recherche (retourne l'indice dans le client, ou -1) */
int   trouverCommande(const Client *c, int numero);

/* Gestion des commandes (retournent 1 si succes, 0 sinon) */
int   creerCommande(Boutique *b);
int   ajouterLigneCommande(Boutique *b);
int   supprimerLigneCommande(Boutique *b);
int   changerStatutCommande(Boutique *b);
int   annulerCommande(Boutique *b);
void  afficherCommande(const Boutique *b);

/* Fonction interne reutilisable (ex. par initialisation.c) */
int   ajouterLigne(Commande *c, const Produit *p, int quantite);

#endif /* COMMANDE_H */
