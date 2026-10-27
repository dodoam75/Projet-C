/* ============================================================
 * utils.h - Interface du module Saisie & validation
 * ------------------------------------------------------------
 * ROLE : declare les fonctions utilitaires partagees : saisie securisee
 *        (entier, reel, chaine), validation (date, email, telephone,
 *        code postal) et affichage (titres, separateurs, pause).
 * UTILISE PAR : tous les modules qui interagissent avec l'utilisateur.
 * ============================================================ */
#ifndef UTILS_H
#define UTILS_H

#include "types.h"

/* Saisie securisee (retourne 1 si OK, 0 sinon) */
void viderBuffer(void);
int  saisirEntier(const char *invite, int min, int max, int *resultat);
int  saisirFloat(const char *invite, float min, float max, float *resultat);
int  saisirChaine(const char *invite, char *dest, size_t taille);

/* Validation */
int  validerDate(Date d);
int  validerEmail(const char *email);
int  validerTelephone(const char *tel);
int  validerCodePostal(const char *cp);
int  estBissextile(int annee);

/* Affichage */
void afficherTitre(const char *titre);
void afficherSeparateur(void);
void pause(void);

#endif /* UTILS_H */
