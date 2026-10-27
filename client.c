/* ============================================================
 * client.c - Implementation des clients et de la fidelite
 * ------------------------------------------------------------
 * ROLE : gere le tableau dynamique b->clients (malloc/realloc).
 *        - ajouterClient : id donne par b->idClientSuivant (jamais saisi),
 *          unicite de l'email (inactifs inclus), adresse complete
 *        - supprimerClient : suppression LOGIQUE, refusee s'il existe des
 *          commandes non annulees
 *        - afficherClient : fiche + historique des commandes
 * ETAT : trouverClient() et les fonctions de points sont faits.
 * ============================================================ */
#include "client.h"
#include "utils.h"

int trouverClient(const Boutique *b, int idClient) {
    for (int i = 0; i < b->nbClients; i++) {
        if (b->clients[i].idClient == idClient)
            return i;
    }
    return -1;
}

int ajouterClient(Boutique *b) {
    /* TODO : saisie + adresse, unicite email (y compris inactifs),
       id = b->idClientSuivant++, realloc si plein (controle NULL),
       commandes = NULL et capaciteCommandes = 0 */
    (void)b;
    return 0;
}

int mettreAJourClient(Boutique *b) {
    /* TODO : modifier coordonnees et adresse de livraison */
    (void)b;
    return 0;
}

int supprimerClient(Boutique *b) {
    /* TODO : suppression logique, refusee si commandes non annulees */
    (void)b;
    return 0;
}

void afficherClients(const Boutique *b) {
    /* TODO : liste avec nombre de commandes et chiffre d'affaires */
    (void)b;
}

void afficherClient(const Boutique *b) {
    /* TODO : fiche detaillee + historique des commandes */
    (void)b;
}

void ajouterPointsFidelite(Client *c, int points) {
    c->pointsFidelite += points;
}

void retirerPointsFidelite(Client *c, int points) {
    c->pointsFidelite -= points;
    if (c->pointsFidelite < 0)
        c->pointsFidelite = 0;
}
