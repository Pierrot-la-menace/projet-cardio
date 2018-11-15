/* main.c

La main ne sert qu'à changer les données, lancer la fonction principale du programme et de permettre l'affichage des accents et la bonne couleur.

*/
#include "menu.h"

int main()
{
    Donnees* donnees = NULL;
    char *file = NULL;

    system("chcp 65001");//activation de l'UTF-8
    system("CLS");//suppression du message de retour de la commande
    system("COLOR 74");//set up de couleur
    printf("Bienvenue sur l'application HexCare, un coeur qui bat au rythme de vos rêves !\n");

    donnees = chargerDonnees(&file);//chargement des données
    afficherMenu(donnees, &file);//affichage de la fonction principale du programme

    free(donnees);//libération de la mémoire
    return 0;
}
