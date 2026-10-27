/* ============================================================
 * statistique.h - Interface du module Statistiques
 * ------------------------------------------------------------
 * ROLE : declare le chiffre d'affaires (total, par mois, par annee) et
 *        les deux palmares (top 5 produits, classement clients).
 * NB : les commandes ANNULEE sont toujours exclues des calculs.
 * ============================================================ */
#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include "types.h"

/* Chiffre d'affaires (hors commandes ANNULEE) */
float chiffreAffairesHT(const Boutique *b);
float chiffreAffairesTTC(const Boutique *b);
void  afficherChiffreAffaires(const Boutique *b);
void  chiffreAffairesParPeriode(const Boutique *b, int mois, int annee);

/* Palmares */
void  palmaresProduits(const Boutique *b);   /* top 5 par quantite vendue */
void  palmaresClients(const Boutique *b);    /* classement par CA genere */

#endif /* STATISTIQUE_H */
