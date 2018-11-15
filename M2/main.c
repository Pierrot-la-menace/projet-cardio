#include <stdio.h>
#include <stdlib.h>
#include "menu.h"// inclue les prototypes des fonctions
#include "GenerationCode.h"

int main()
{
    int result = 0;//Variable contenant la valeur du mode d'éclairage des LEDs que l'utilisateur a choisi
    int autre = 0;/*Variable contenant la valeur de la LED allumée que l'utilisateur a choisi si celui-ci
                    a choisi le mode d'éclairage n°5*/

    system("chcp 65001");//Commande qui permet d'encoder les accents
    system("CLS");//Commande qui permet d'effacer les lignes précédentes

    DessinCoeur();//Fonction qui permet d'afficher le dessin du coeur et le dessin du menu

    result = choisirmenu();

    if(result == 5)
    {
        printf("Quelle LED veux-tu allumer ? ");
        scanf("%d", &autre);
        parametres(result, autre);/*Fonction permettant d'écrire dans le param.h les instructions nécessaires si
                                    l'utilisateur a choisi le mode d'éclairage n°5*/
    }
    else
    {
        parametre(result);/*Fonction permettant d'écrire dans le param.h les instructions nécessaires si
                                    l'utilisateur a choisi le mode d'éclairage n°1 2 3 ou 4*/
    }


    return 0;
}
