/* ============================================================
 * main.c - Point d'entree du programme
 * ------------------------------------------------------------
 * ROLE : cree la Boutique (variable locale, 'racine' des donnees), charge
 *        les donnees de test, affiche le menu principal en boucle puis
 *        libere toute la memoire avant de quitter.
 * A FAIRE : remplir les 4 sous-menus (produits, clients, commandes,
 *          statistiques) et ajouter les 2 fonctionnalites de creativite.
 * ============================================================ */

#include <stdio.h>

int main()
{
int choix;
printf("Bievenue sur la Boutique que voulais vous faire :\n1-Produit\n2-Client\n3-Commandes\n4-Statistique");
do{
switch (choix) {
    case 1:
       Produit();
        break;

    case 2:
        Client();
        break;
    case 3:
        Commandes()
        break;
    case 4:
        Statistique();
        break;
default:
    printf("Choix invalide")
}}while(choix>5)
  
return 0
  }
