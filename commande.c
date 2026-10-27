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
#include "commande.h"
#include "client.h"
#include "produit.h"
#include "utils.h"

float calculerTauxRemise(float montantBrutHT) {
    if (montantBrutHT >= 600.0f) return 15.0f;
    if (montantBrutHT >= 300.0f) return 10.0f;
    if (montantBrutHT >= 100.0f) return 5.0f;
    return 0.0f;
}

void calculCommande(Commande *c) {
    /* TODO : montantBrutHT = somme des sousTotalHT, tauxRemise, montantRemise,
       montantHT, montantTVA (20 % du HT), fraisPort (0 si brut >= 60),
       montantTTC = HT + TVA + port */
    (void)c;
}

int trouverCommande(const Client *c, int numero) {
    for (int i = 0; i < c->nbCommandes; i++) {
        if (c->commandes[i].numero == numero)
            return i;
    }
    return -1;
}

int ajouterLigne(Commande *c, const Produit *p, int quantite) {
    /* TODO : refuser doublon de reference, verifier le stock (quantite cumulee),
       realloc des lignes si plein (controle NULL), figer designation et prix */
    (void)c; (void)p; (void)quantite;
    return 0;
}

int creerCommande(Boutique *b) {
    /* TODO : choisir client, saisir N lignes, numero = b->numeroSuivant++,
       copier l'adresse, decrementer le stock, calculCommande, points fidelite,
       realloc du tableau de commandes du client si plein */
    (void)b;
    return 0;
}

int ajouterLigneCommande(Boutique *b) {
    /* TODO : uniquement si EN_COURS, mise a jour du stock et des montants */
    (void)b;
    return 0;
}

int supprimerLigneCommande(Boutique *b) {
    /* TODO : uniquement si EN_COURS, reintegrer le stock, recalculer */
    (void)b;
    return 0;
}

int changerStatutCommande(Boutique *b) {
    /* TODO : EN_COURS -> EXPEDIEE -> LIVREE, sans retour */
    (void)b;
    return 0;
}

int annulerCommande(Boutique *b) {
    /* TODO : uniquement si EN_COURS, reintegrer le stock, retirer les points */
    (void)b;
    return 0;
}

void afficherCommande(const Boutique *b) {
    /* TODO : lignes, remise, TVA, frais de port, total TTC */
    (void)b;
}
