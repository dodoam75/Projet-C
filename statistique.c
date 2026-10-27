/* ============================================================
 * statistique.c - Implementation des statistiques
 * ------------------------------------------------------------
 * ROLE : parcourt clients -> commandes -> lignes pour agreger les donnees.
 *        Les palmares utilisent un tableau temporaire (malloc) trie par un
 *        algorithme de tri (qsort ou tri maison), puis libere (free).
 * ETAT : tout est en TODO.
 * ============================================================ */
#include "statistique.h"
#include "utils.h"

float chiffreAffairesHT(const Boutique *b) {
    /* TODO : somme des montantHT des commandes non ANNULEE */
    (void)b;
    return 0.0f;
}

float chiffreAffairesTTC(const Boutique *b) {
    /* TODO : somme des montantTTC des commandes non ANNULEE */
    (void)b;
    return 0.0f;
}

void afficherChiffreAffaires(const Boutique *b) {
    /* TODO : total HT et TTC */
    (void)b;
}

void chiffreAffairesParPeriode(const Boutique *b, int mois, int annee) {
    /* TODO : par mois (mois > 0) ou par annee (mois == 0) */
    (void)b; (void)mois; (void)annee;
}

void palmaresProduits(const Boutique *b) {
    /* TODO : tableau temporaire (malloc), cumul des quantites,
       tri (qsort ou tri maison), afficher le top 5, free */
    (void)b;
}

void palmaresClients(const Boutique *b) {
    /* TODO : tableau temporaire (malloc), CA par client, tri decroissant, free */
    (void)b;
}
