/* ============================================================
 * utils.c - Implementation de la saisie et de la validation
 * ------------------------------------------------------------
 * ROLE : evite scanf direct (dangereux) en utilisant fgets + conversion.
 *        Verifie les intervalles, refuse les chaines vides et valide les
 *        formats (email contient '@', telephone 10 chiffres, etc.).
 * A FAIRE EN PREMIER : tout le reste depend de ce module.
 * ETAT : saisirEntier/Float/Chaine et les valider* sont des TODO.
 * ============================================================ */
#include "utils.h"

void viderBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int saisirEntier(const char *invite, int min, int max, int *resultat) {
    /* TODO : fgets + strtol, verifier l'intervalle [min, max] */
    (void)invite; (void)min; (void)max; (void)resultat;
    return 0;
}

int saisirFloat(const char *invite, float min, float max, float *resultat) {
    /* TODO : fgets + strtof, verifier l'intervalle [min, max] */
    (void)invite; (void)min; (void)max; (void)resultat;
    return 0;
}

int saisirChaine(const char *invite, char *dest, size_t taille) {
    /* TODO : fgets, supprimer le '\n', refuser la chaine vide */
    (void)invite; (void)dest; (void)taille;
    return 0;
}

int estBissextile(int annee) {
    return (annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0);
}

int validerDate(Date d) {
    /* TODO : jour valide selon le mois, annee entre 2000 et 2100 */
    (void)d;
    return 0;
}

int validerEmail(const char *email) {
    /* TODO : contient '@' */
    (void)email;
    return 0;
}

int validerTelephone(const char *tel) {
    /* TODO : 10 chiffres */
    (void)tel;
    return 0;
}

int validerCodePostal(const char *cp) {
    /* TODO : 5 chiffres */
    (void)cp;
    return 0;
}

void afficherTitre(const char *titre) {
    printf("\n===== %s =====\n", titre);
}

void afficherSeparateur(void) {
    printf("----------------------------------------\n");
}

void pause(void) {
    printf("\nAppuyez sur Entree pour continuer...");
    viderBuffer();
}
