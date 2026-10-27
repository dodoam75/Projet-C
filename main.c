/* ============================================================
 * main.c - Point d'entree du programme
 * ------------------------------------------------------------
 * ROLE : cree la Boutique (variable locale, 'racine' des donnees), charge
 *        les donnees de test, affiche le menu principal en boucle puis
 *        libere toute la memoire avant de quitter.
 * A FAIRE : remplir les 4 sous-menus (produits, clients, commandes,
 *          statistiques) et ajouter les 2 fonctionnalites de creativite.
 * ============================================================ */
#include "types.h"
#include "utils.h"
#include "produit.h"
#include "client.h"
#include "commande.h"
#include "statistique.h"
#include "initialisation.h"

static void menuProduits(Boutique *b) {
    /* TODO : ajouter / modifier / supprimer / lister / rechercher / alertes */
    (void)b;
}

static void menuClients(Boutique *b) {
    /* TODO : ajouter / modifier / supprimer / lister / afficher */
    (void)b;
}

static void menuCommandes(Boutique *b) {
    /* TODO : creer / ajouter ligne / supprimer ligne / statut / annuler / afficher */
    (void)b;
}

static void menuStatistiques(Boutique *b) {
    /* TODO : CA / palmares produits / palmares clients */
    (void)b;
}

int main(void) {
    Boutique boutique;
    int choix = -1;

    initialiserBoutique(&boutique);
    initialiserDonneesTest(&boutique);

    while (choix != 0) {
        afficherTitre("SHOPFLOW");
        printf("1. Produits\n2. Clients\n3. Commandes\n4. Statistiques\n0. Quitter\n");
        if (!saisirEntier("Votre choix : ", 0, 4, &choix))
            continue;

        switch (choix) {
            case 1: menuProduits(&boutique);     break;
            case 2: menuClients(&boutique);      break;
            case 3: menuCommandes(&boutique);    break;
            case 4: menuStatistiques(&boutique); break;
            default: break;
        }
    }

    detruireBoutique(&boutique);
    return 0;
}
