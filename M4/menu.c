/* action.c

Contient la fonction principale qui est la base de tout le programme

*/
#include "menu.h"

void afficherMenu(Donnees* donnees, char **file) {

    int continuer = 1, action = 0, moy = 0;
    Donnees *d = NULL;

    while(continuer == 1) //tant que l'utilisateur n'a pas voulu quitter
    {
        //on affiche le menu
        printf("\n          |  \\ \\ | |/ /                      \n");
        printf("          |  |\\ `' ' /                        \n");
        printf("          |  ;'aorta \\      / , pulmonary     \n");
        printf("          | ;    _,   |    / / ,  arteries     \n");
        printf(" superior | |   (  `-.;_,-' '-' ,              \n");
        printf("vena cava | `,   `-._       _,-'_              \n");
        printf("          |,-`.    `.)    ,<_,-'_, pulmonary   Veuillez choisir votre action :\n");
        printf("         ,'    `.   /   ,'  `;-' _,  veins        1 : Afficher les données en brut\n");
        printf("        ;        `./   /`,    \\-'                 2 : Trier les données\n");
        printf("        | right   /   |  ;\\   |\\                  3 : Rechercher des données pour un laps de temps donné\n");
        printf("        | atrium ;_,._|_,  `, ' \\                 4 : Afficher la moyenne des pouls\n");
        printf("        |        \\    \\ `       `,                5 : Afficher le nombre de données chargées\n");
        printf("        `      __ `    \\   left  ;,               6 : Rechercher les extremums des pouls\n");
        printf("         \\   ,'  `      \\,  ventricle             7 : Faire un bilan de santé cardiaque\n");
        printf("          \\_(            ;,      ;;               8 : Recharger les données\n");
        printf("          |  \\           `;,     ;;               0 : Quitter l'application\n");
        printf(" inferior |  |`.          `;;,   ;'            \n");
        printf("vena cava |  |  `-.        ;;;;,;'             \n");
        printf("          |  |    |`-.._  ,;;;;;'              \n");
        printf("          |  |    |   | ``';;;'  FL            \n");
        printf("                  aorta                        \n\n");

        //on demande l'action voulue (si on appuie sur enter on quitte)
        printf("Action ? (défaut : quitter)\n");
        action = scanfAI(0);
        system("CLS");

        //on fait un switch avec une case par action
        switch (action) {
            case 0 :
                 //fermeture programme
                 printf("On quitte l'application...\n");
                 continuer = 0;
                 break;
            case 1 :
                 //affichage des données actuellement chargées
                 afficherDonnees(donnees);
                 break;
            case 2 :
                 //on tri les données
                 tri(donnees);
                 break;
            case 3 :
                 //on lance la fonction de tri
                 rechercheDate(donnees);
                 break;
            case 4 :
                 //on cacule la moyenne
                 moy = moyennePouls(donnees);
                 if(moy == -1)
                 {
                     //si la fonction retourne -1, c'est qu'aucune donnée correspondait aux critères de l'utilisateur
                     printf("Moyenne incalculable selon vos critères\n\n");
                 }
                 else
                    //on affiche la moyenne
                    printf("La moyenne de vos pouls est égale à %d\n\n", moy);
                 break;
            case 5 :
                 //affichage du nombre de ligne
                 printf("Le nombre de lignes chargées est de %d lignes\n\n", donnees[0].lignes);
                 break;
            case 6 :
                 //affichage des extremums
                 d = extremumsPouls(donnees);
                 if(d != NULL)
                 {
                    printf("Voici les extremums trouvés dans les données : \n\n");
                    afficherDonnees(d);
                    free(d);
                 }
                 else
                 {
                     //si la fonction renvoie NULL c'est qu'il y eu une erreur pendant la recherche
                     printf("Aucune donnée trouvée dans le laps de temps donné");
                 }
                 d = NULL;
                 break;
            case 7 :
                 //exécution du bilan
                 bilan(donnees);
                 break;
            case 8 :
                //on recharge les données
                free(donnees);
                donnees = chargerDonnees(file);//on donne le pointeur du pointeur
                break;
            default :
                //si l'utilisateur s'est trompé
                printf("Action invalide veuillez recommencer\n");
                break;
        }
    }
}
