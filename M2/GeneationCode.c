#include <stdio.h>
#include <stdlib.h>

int parametre(int resultat)/*Fonction permettant d'écrire dans le param.h les instructions nécessaires si
                                    l'utilisateur a choisi le mode d'éclairage n°1 2 3 ou 4*/

{
    FILE *fichier = NULL;//Créer un pointeur de type FILE
    fichier = fopen("C:\\Users\\Le Fortier\\Desktop\\Quentin\\Etudes\\Cesi\\Prosit\\PROJET\\Code final\\code\\param.h", "w");//Permet d'écrir dans le fichier param.h

    if(fichier != NULL)
    {
     if(resultat == 1)
     {
        fputs("#define OPTION 1\nint autre;", fichier);//fputs permet d'écrire les éléments contenus entre parenthèses
        fclose(fichier);
     }

     else if(resultat == 2)
     {
         fputs("#define OPTION 2\nint autre;", fichier);
         fclose(fichier);
     }

     else if(resultat == 3)
     {
         fputs("#define OPTION 3\nint autre;", fichier);
         fclose(fichier);
     }

     else if(resultat == 4)
     {
         fputs("#define OPTION 4\nint autre;", fichier);
         fclose(fichier);
     }
    }

    else
    {
        printf("Erreur");
    }


    return 0;
}

void parametres(int resultat, int n)/*Fonction permettant d'écrire dans le param.h les instructions nécessaires si
                                    l'utilisateur a choisi le mode d'éclairage n°5*/
  
{
    FILE *fichier = NULL;
    fichier = fopen("C:\\Users\\Le Fortier\\Desktop\\Quentin\\Etudes\\Cesi\\Prosit\\PROJET\\Code final\\code\\param.h", "w");
    
    fprintf(fichier,"#define OPTION 5\nint autre = %d-1;", n);/*fprintf permet d'écrire les éléments contenus entre parenthèses
                                                                et en utilisant une variable contenant un nombre*/
    fclose(fichier);
}
