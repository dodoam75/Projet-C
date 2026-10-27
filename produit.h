/* ============================================================
 * produit.h - Interface du module Catalogue produits
 * ------------------------------------------------------------
 * ROLE : declare le CRUD des produits (ajouter, modifier, supprimer,
 *        lister, rechercher), la recherche par reference et les alertes
 *        de stock.
 * UTILISE PAR : main.c (menu), commande.c (lecture/mise a jour du stock),
 *        statistique.c (palmares produits).
 * ============================================================ */
#ifndef PRODUIT_H
#define PRODUIT_H

#include "types.h"

/* Retourne l'indice du produit (ou -1 si introuvable) */
int  trouverProduit(const Boutique *b, const char *reference);

/* CRUD (retournent 1 si succes, 0 sinon) */
int  ajouterProduit(Boutique *b);
int  mettreAJourProduit(Boutique *b);
int  supprimerProduit(Boutique *b);
void afficherProduits(const Boutique *b);
void rechercherProduit(const Boutique *b);

/* Stock */
void afficherAlertesStock(const Boutique *b);

#endif /* PRODUIT_H */
