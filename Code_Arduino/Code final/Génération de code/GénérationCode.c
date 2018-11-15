#include <stdio.h>
#include <stdlib.h>

int parametre(int resultat)
{
    FILE *fichier = NULL;
    fichier = fopen("C:\\Users\\Le Fortier\\Desktop\\Quentin\\Etudes\\Cesi\\Prosit\\PROJET\\Code final\\code\\param.h", "w");

    if(fichier != NULL)
    {
     if(resultat == 1)
     {
        fputs("#define OPTION 1\nint autre;", fichier);
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

    //system("start C:\\Users\\Le Fortier\\Desktop\\Quentin\\Etudes\\Cesi\\Prosit\\PROJET\\Code final\\code.ino");

    return 0;
}

void parametres(int resultat, int n)
{
    FILE *fichier = NULL;
    fichier = fopen("C:\\Users\\Le Fortier\\Desktop\\Quentin\\Etudes\\Cesi\\Prosit\\PROJET\\Code final\\code\\param.h", "w");
    fprintf(fichier,"#define OPTION 5\nint autre = %d-1;", n);
    fclose(fichier);
}
