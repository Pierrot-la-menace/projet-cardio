#include "menu.h"

void afficherMenu(Donnees* donnees, char **file) {

    int continuer = 1, action = 0, moy = 0;
    Donnees *d = NULL;

    while(continuer == 1)
    {
        printf("Veuillez choisir votre action :\n");
        printf("   1 : Afficher les données en brut\n");
        printf("   2 : Trier les données\n");
        printf("   3 : Rechercher des données pour un laps de temps donné\n");
        printf("   4 : Afficher la moyenne des pouls\n");
        printf("   5 : Afficher le nombre de données chargées\n");
        printf("   6 : Rechercher les extremums des pouls\n");
        printf("   7 : Faire un bilan de santé cardiaque\n");
        printf("   8 : Recharger les données\n");
        printf("   0 : Quitter l'application\n");
        printf("Action ? (défaut : quitter)\n");
        action = scanfAI(0);
        system("CLS");

        switch (action) {
            case 0 :
                 printf("On quitte l'application...\n");
                 continuer = 0;
                 break;
            case 1 :
                 afficherDonnees(donnees);
                 break;
            case 2 :
                 tri(donnees);
                 break;
            case 3 :
                 rechercheDate(donnees);
                 break;
            case 4 :
                 moy = moyennePouls(donnees);
                 if(moy == -1)
                 {
                     printf("Moyenne incalculable selon vos critères\n\n");
                 }
                 else
                    printf("La moyenne de vos pouls est égale à %d\n\n", moy);
                 break;
            case 5 :
                 printf("Le nombre de lignes chargées est de %d lignes\n\n", donnees[0].lignes);
                 break;
            case 6 :
                 d = extremumsPouls(donnees);
                 if(d != NULL)
                 {
                    printf("Voici les extremums trouvés dans les données : \n\n");
                    afficherDonnees(d);
                    free(d);
                 }
                 else
                 {
                     printf("Aucune donnée trouvée dans le laps de temps donné");
                 }
                 d = NULL;
                 break;
            case 7 :
                 bilan(donnees);
                 break;
            case 8 :
                free(donnees);
                donnees = chargerDonnees(file);
            default :
                printf("Action invalide veuillez recommencer\n");
                break;
        }
    }
}
