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
