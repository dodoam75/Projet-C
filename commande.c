/* ============================================================
 * commande.c - Implementation des commandes (module le plus complexe)
 * ------------------------------------------------------------
 * ROLE : - calculCommande : brut HT -> remise (paliers) -> HT -> TVA 20 %
 *          -> frais de port (offerts des 60 EUR HT brut) -> TTC
 *        - ajouterLigne : tableau dynamique de lignes (realloc), pas de
 *          doublon de reference, stock verifie sur la quantite cumulee
 *        - creerCommande : decremente le stock, credite les points
 *        - annulerCommande : seulement EN_COURS, reintegre stock + points
 *        - changerStatutCommande : EN_COURS -> EXPEDIEE -> LIVREE
 * ETAT : calculerTauxRemise() et trouverCommande() sont faits.
 * ============================================================ */

