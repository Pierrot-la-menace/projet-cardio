#include "menu.h"

int main()
{
    Donnees* donnees = NULL;
    char *file = NULL;

    system("chcp 65001");
    system("CLS");
    system("COLOR 74");
    printf("Bienvenue sur l'application HexCare, un coeur qui bat au rythme de vos rêves !\n");

    donnees = chargerDonnees(&file);
    afficherMenu(donnees, &file);

    free(donnees);
    return 0;
}
