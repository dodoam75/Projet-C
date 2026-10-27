/* ============================================================
 * initialisation.h - Interface du jeu de donnees de demonstration
 * ------------------------------------------------------------
 * ROLE : declare l'initialisation de la boutique, le chargement des
 *        donnees de test et la liberation complete de la memoire.
 * ============================================================ */
#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "types.h"

void initialiserBoutique(Boutique *b);        /* valeurs par defaut, pointeurs a NULL */
void initialiserDonneesTest(Boutique *b);     /* 8 produits, 5 clients, 6 commandes */
void detruireBoutique(Boutique *b);           /* liberation complete de la memoire */

#endif /* INITIALISATION_H */
