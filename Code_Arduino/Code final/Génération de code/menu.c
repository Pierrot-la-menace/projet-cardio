#include <stdio.h>
#include <stdlib.h>
void DessinCoeur()//Fonction permettant d'afficher le dessin de coeur et le dessin du menu
{
printf("\n          |  \\ \\ | |/ /                      \n");
printf("          |  |\\ `' ' /                        \n");
printf("          |  ;'aorta \\      / , pulmonary     \n");
printf("          | ;    _,   |    / / ,  arteries     \n");
printf(" superior | |   (  `-.;_,-' '-' ,              \n");
printf("vena cava | `,   `-._       _,-'_              \n");
printf("          |,-`.    `.)    ,<_,-'_, pulmonary   |----------------MENU----------------|\n");
printf("         ,'    `.   /   ,'  `;-' _,  veins     |    Toutes les LEDs allumées : 1    |\n");
printf("        ;        `./   /`,    \\-'              |  Une LED sur deux est allumée : 2  |\n");
printf("        | right   /   |  ;\\   |\\               |  Une LED sur trois est allumée : 3 |\n");
printf("        | atrium ;_,._|_,  `, ' \\              |         Mode chenille : 4          |\n");
printf("        |        \\    \\ `       `,             |       Une LED au choix : 5         |\n");
printf("        `      __ `    \\   left  ;,            |------------------------------------|\n");
printf("         \\   ,'  `      \\,  ventricle        \n");
printf("          \\_(            ;,      ;;           \n");
printf("          |  \\           `;,     ;;           \n");
printf(" inferior |  |`.          `;;,   ;'            \n");
printf("vena cava |  |  `-.        ;;;;,;'             \n");
printf("          |  |    |`-.._  ,;;;;;'              \n");
printf("          |  |    |   | ``';;;'  FL            \n");
printf("                  aorta                        \n\n");
    system("color 04");

}



int choisirmenu()//Fonction permettant de faire choisir pa l'utilisateur le mode d'éclairage des LEDs
{
    int resultat = 0;

    printf("Quel eclairage voulez vous avoir ? ");
    scanf("%d", &resultat);


    return resultat;
}
