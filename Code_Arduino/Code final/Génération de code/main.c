#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "GenerationCode.h"

int main()
{
    int result = 0;
    int autre = 0;

    system("chcp 65001");
    system("CLS");

    DessinCoeur();

    result = choisirmenu();

    if(result == 5)
    {
        printf("Quelle LED veux-tu allumer ? ");
        scanf("%d", &autre);
        parametres(result, autre);
    }
    else
    {
        parametre(result);
    }


    return 0;
}
