#include "actions.h"

void convertirTStoDate(long timeStamp, char *buf)
{
    time_t t = timeStamp;
    struct tm tm = *localtime(&t);

    strftime(buf, 80, "Le %d/%m/%Y à %H:%M:%S", &tm);
}

int moyennePouls(Donnees *donnees)
{
    int i = 0, total = 0, moy = 0, choix2 = 0;
    char choix[255];
    Donnees *donnees2 = NULL;

    printf("Rechercher en global ou sur un laps de temps donné (global/laps) ? (défaut : global) ");
    scanfAS(choix, "global");

    while(i < strlen(choix))
    {
        choix[i] = tolower(choix[i]);
        i++;
    }

    if(strcmp(choix, "laps") == 0)
    {
        choix2 = 1;
    }
    else if(strcmp(choix, "global") == 0)
    {
        choix2 = 0;
    }
    else
    {
        printf("Opération invalide\n");
        return -1;
    }

    i = 0;

    switch(choix2) {
        case 0 :
            while(i < donnees[0].lignes)
            {
                total = total + donnees[i].pouls;
                i++;
            }
            moy = total / donnees[0].lignes;
            break;
        case 1 :
            donnees2 = rechercheLaps(donnees);
            if(donnees2 != NULL)
            {
                while(i < donnees2[0].lignes)
                {
                    total = total + donnees2[i].pouls;
                    i++;
                }
                moy = total / donnees2[0].lignes;
            }
            else
            {
                moy = -1;
            }
            break;
        default :
            return -1;
    }

    return moy;
}

void tri(Donnees* donnees)
{
    char type[255];
    int i = 0;

    printf("Quel type de tri (date/pouls) ? (défaut : pouls) ");
    scanfAS(type, "pouls");

    i = 0;
    while(i < strlen(type))
    {
        type[i] = tolower(type[i]);
        i++;
    }

    if(strcmp(type, "date") == 0)
    {
        triDate(donnees);
        printf("Données triées !\n");
    }
    else if(strcmp(type, "pouls") == 0)
    {
        tri_Poul(donnees);
        printf("Données triées !\n");
    }
    else
    {
        printf("Opération invalide\n");
    }
}

void afficherDonneesRecherchee(Donnees* donnees)
{
    system("CLS");
    if(donnees != NULL)
    {
        printf("\nVoici les entrées qui correspondent à vos critères :\n\n");
        afficherDonnees(donnees);
        printf("(%d entrée(s))\n\n", donnees[0].lignes);
        free(donnees);
    }
    else
    {
        printf("Aucune donnée ne correspond à vos critères !\n\n");
    }
}

void rechercheDate(Donnees* donnees)
{
    Donnees* donnnees_recherchees = NULL;
    int choix = 0;
    printf("Quel type de recherche souhaitez vous faire ?\n1 : Recherche postérieur à [date]\n2 : Recherche antérieur à [date]\n3 : Recherche dans un laps de temps\n");
    choix = scanfAI(-1);

    switch(choix) {
        case 1:
            system("CLS");
            donnnees_recherchees = recherchePosterieur(donnees);
            afficherDonneesRecherchee(donnnees_recherchees);
            break;
        case 2:
            system("CLS");
            donnnees_recherchees = rechercheAnterieur(donnees);
            afficherDonneesRecherchee(donnnees_recherchees);
            break;
        case 3:
            system("CLS");
            donnnees_recherchees = rechercheLaps(donnees);
            afficherDonneesRecherchee(donnnees_recherchees);
            break;
        default:
            printf("Choix invalide\n");
    }
}

Donnees* extremumsPouls(Donnees *donnees)
{
    Donnees *donnees2 = NULL, *donnees3 = NULL;
    int i = 0, choix2 = 0;
    char choix[255];


    donnees2 = malloc(donnees[0].lignes * sizeof(Donnees));
    donnees3 = malloc(2 * sizeof(Donnees));

    if(donnees2 == NULL || donnees3 == NULL)
    {
        system("CLS");
        system("COLOR 4");
        printf("Copie des données...\n");
        printf("Erreur allocation variable !");
        exit(1);
    }


    printf("Rechercher en global ou sur un laps de temps donné (global/laps) ? (défaut : laps) ");
    scanfAS(choix, "laps");

    while(i < strlen(choix))
    {
        choix[i] = tolower(choix[i]);
        i++;
    }

    if(strcmp(choix, "laps") == 0)
    {
        choix2 = 1;
    }
    else if(strcmp(choix, "pouls") == 0)
    {
        choix2 = 0;
    }
    else
    {
        printf("Opération invalide\n");
        return NULL;
    }

    i = 0;

    switch(choix2) {
        case 0 :
            while(i < donnees[0].lignes)
            {
                donnees2[i].date = donnees[i].date;
                donnees2[i].millis = donnees[i].millis;
                donnees2[i].pouls = donnees[i].pouls;
                donnees2[i].lignes = donnees[i].lignes;
                i++;
            }
            i--;
            break;
        case 1 :
            free(donnees2);
            donnees2 = rechercheLaps(donnees);
            if(donnees2 == NULL)
            {
                return NULL;
            }
            i = donnees2[0].lignes;
            i--;
            break;
        default :
            return NULL;
    }

    tri_Poul(donnees2);

    donnees3[0].date = donnees2[0].date;
    donnees3[0].millis = donnees2[0].millis;
    donnees3[0].pouls = donnees2[0].pouls;
    donnees3[0].lignes = 2;

    donnees3[1].date = donnees2[i].date;
    donnees3[1].millis = donnees2[i].millis;
    donnees3[1].pouls = donnees2[i].pouls;
    donnees3[1].lignes = 2;

    free(donnees2);

    return donnees3;
}

void bilan(Donnees *donnees)
{
    const int bpm[6][2] = {{140, 50}, {110, 40}, {105, 35}, {95, 30}, {70, 10}, {65, 5}};
    int index = 0, moyenne = 0;

    system("CLS");
    printf("Quel est vôtre âge (en années) ? [défaut : adulte] ");
    index = scanfAI(40);

    if(index >= 0)
    {
        if(index == 0)
            index = 0;
        else if(index <= 2)
            index = 1;
        else if(index <= 5)
            index = 2;
        else if(index <= 12)
            index = 3;
        else if(index <= 65)
            index = 4;
        else
            index = 5;

        if(donnees[0].lignes <= 5)
        {
            printf("Votre bilan peut ne pas être précis : on ne calcule la moyenne qu'à partir de %d nombres\n", donnees[0].lignes);
        }

        moyenne = moyennePouls(donnees);

        if((bpm[index][0] - bpm[index][1]) > moyenne)
        {
            printf("Votre coeur bat trop lentement pour votre âge, vous devriez consulter un medecin (moyenne : %d)\n\n", moyenne);
        }
        else if((bpm[index][0] + bpm[index][1]) < moyenne)
        {
            printf("Votre coeur bat trop vite pour votre âge, vous devriez consulter un medecin (moyenne : %d)\n\n", moyenne);
        }
        else
        {
            printf("Votre coeur est en pleine forme ! (moyenne : %d)\n\n", moyenne);
        }
    }
    else
    {
       printf("Impossible de faire un bilan pour quelqu'un qui n'est pas né...\n");
    }
}
