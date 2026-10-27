/* ============================================================
 * produit.c - Implementation du catalogue produits
 * ------------------------------------------------------------
 * ROLE : gere le tableau dynamique b->produits (malloc/realloc).
 *        - ajouterProduit : unicite de la reference (inactifs inclus)
 *        - supprimerProduit : suppression LOGIQUE (actif = 0), refusee si
 *          le produit est dans une commande non annulee
 *        - afficherAlertesStock : stock <= seuilAlerte
 * ETAT : trouverProduit() est fait, le reste est en TODO.
 * ============================================================ */
