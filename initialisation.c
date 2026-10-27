/* ============================================================
 * initialisation.c - Donnees de demonstration + liberation memoire
 * ------------------------------------------------------------
 * ROLE : - initialiserBoutique : met la Boutique a zero (pointeurs NULL,
 *          compteurs numeroSuivant = 1001 et idClientSuivant = 1)
 *        - initialiserDonneesTest : 8 produits (3 categories, 2 en alerte),
 *          5 clients, 6 commandes (4 statuts, dont une > 600 EUR HT)
 *        - detruireBoutique : free() de TOUS les niveaux (lignes, commandes,
 *          clients, produits). Une seule fuite est sanctionnee.
 * ETAT : initialiserDonneesTest() est en TODO, le reste est fait.
 * ============================================================ */
#include "initialisation.h"
#include "commande.h"

void initialiserBoutique(Boutique *b) {
    strcpy(b->nom, "ShopFlow");
    b->produits = NULL;
    b->nbProduits = 0;
    b->capaciteProduits = 0;
    b->clients = NULL;
    b->nbClients = 0;
    b->capaciteClients = 0;
    b->numeroSuivant = 1001;
    b->idClientSuivant = 1;
}

void initialiserDonneesTest(Boutique *b) {
    /* TODO :
       1. Catalogue : 8 produits, >= 3 categories, 2 en alerte de stock
       2. Clients   : 5 clients avec adresses completes
       3. Commandes : 6 commandes couvrant les 4 statuts,
          dont >= 2 commandes de 3 lignes ou plus
          et >= 1 commande > 600 EUR HT
       Penser a : calculCommande(), stock coherent, compteurs numeroSuivant /
       idClientSuivant mis a jour, controle du retour de malloc. */
    (void)b;
}

/* Liberation complete : une seule fuite memoire est sanctionnee */
void detruireBoutique(Boutique *b) {
    for (int i = 0; i < b->nbClients; i++) {
        for (int j = 0; j < b->clients[i].nbCommandes; j++)
            free(b->clients[i].commandes[j].lignes);
        free(b->clients[i].commandes);
    }
    free(b->clients);
    free(b->produits);
    b->clients = NULL;
    b->produits = NULL;
    b->nbClients = b->capaciteClients = 0;
    b->nbProduits = b->capaciteProduits = 0;
}
