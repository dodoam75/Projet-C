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
#include <stddef.h>

/* Tailles utilisées par le module Produits */
#define LG_REFERENCE   12
#define LG_DESIGNATION 60
#define LG_CATEGORIE   30
#define LG_STATUT      20

/* Statuts de commande utilisés pour protéger les produits commandés */
#define STATUT_EN_COURS "EN_COURS"
#define STATUT_EXPEDIEE "EXPEDIEE"
#define STATUT_LIVREE   "LIVREE"
#define STATUT_ANNULEE  "ANNULEE"

/* Codes de retour */
enum {
    PRODUIT_OK = 0,
    PRODUIT_DOUBLON = -1,
    PRODUIT_MEMOIRE = -2,
    PRODUIT_STOCK_INSUFFISANT = -3
};

/* Saisie sécurisée */
void lireChaine(const char *invite, char *dest, size_t taille);
int lireEntier(const char *invite, int min, int max);
double lireReel(const char *invite, double min, int minExclus);

/* Recherche */
int indexProduit(const Boutique *b, const char *reference);
Produit *trouverProduitActif(Boutique *b, const char *reference);

/* Gestion du catalogue */
int ajouterProduitDonnees(Boutique *b, const Produit *p);
void ajouterProduit(Boutique *b);
void modifierProduit(Boutique *b);
void supprimerProduit(Boutique *b);
void afficherCatalogue(const Boutique *b);
void rechercherProduit(const Boutique *b);
void afficherAlertesStock(const Boutique *b);

/* Noms conservés pour compatibilité avec l'ancienne version du module */
void mettreAJourProduit(Boutique *b);
void afficherProduits(const Boutique *b);

/* Gestion du stock */
int retirerStock(Produit *p, int quantite);
void reintegrerStock(Produit *p, int quantite);

#endif
