#include "donnees.h"
#include "actions.h"

long convertirStringtoTS()
{
    time_t TS;
    struct tm tm;
    long annee = 0L, mois = 0L, jour = 0L, heure = 0L, minute = 0L, seconde = 0L, timeStamp = 0L;
    const int NB_JOUR_MOIS[2][12] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}};

	time(&TS);
    tm = *localtime(&TS);

    printf("Année [%d]: ", tm.tm_year + 1900);
    annee = scanfAL(tm.tm_year + 1900);
    printf("Mois [%d]: ", tm.tm_mon + 1);
    mois = scanfAL(tm.tm_mon + 1);
    printf("Jour [%d]: ", tm.tm_mday + 1);
    jour = scanfAL(tm.tm_mday + 1);
    printf("Heure [%d]: ", tm.tm_hour);
    heure = scanfAL(tm.tm_hour);
    printf("Minute [%d]: ", tm.tm_min);
    minute = scanfAL(tm.tm_min);
    printf("Seconde [%d]: ", tm.tm_sec);
    seconde = scanfAL(tm.tm_sec);

    if(annee >= 1970 && 1 <= mois && mois <= 12 && 1 <= jour && jour <= 31 && 0 <= heure && heure <= 23 && 0 <= minute && minute <= 59 && 0 <= seconde && seconde <= 59)
    {
        annee = annee - 1970;

        timeStamp = (jour - 1) * 86400;

        timeStamp = timeStamp + (heure * 3600);

        timeStamp = timeStamp + (minute * 60);

        timeStamp = timeStamp + seconde;

        timeStamp = (timeStamp + annee * 31536000 + round(((double)annee/4) - 0.1) * 86400) - 3600;

        if((annee - 2)%4 == 0)
        {
            timeStamp = timeStamp + (NB_JOUR_MOIS[1][mois - 1] * 86400);
        }
        else
        {
            timeStamp = timeStamp + (NB_JOUR_MOIS[0][mois - 1] * 86400);
        }

        return timeStamp;
    }
    else
    {
        return 0L;
    }
}

void scanfAS(char *buf, char *defaut)
{
    fflush(stdin);
    gets(buf);

    if(strlen(buf) == 0)
    {
        if(defaut != NULL)
        {
            strcpy(buf, defaut);
        }
        else
        {
             buf[0] = '0';
        }
    }
}

int scanfAI(int defaut)
{
    char buf[255];

    fflush(stdin);
    gets(buf);

    if(strlen(buf) == 0)
    {
        if(defaut != -1)
            return (long)defaut;
        else
            return 0L;
    }
    else
    {
       return (long)atoi(buf);
    }
}

long scanfAL(int defaut)
{
    char buf[255];

    fflush(stdin);
    gets(buf);

    if(strlen(buf) == 0)
    {
        if(defaut != -1)
            return (long)defaut;
        else
            return 0L;
    }
    else
    {
       return (long)atoi(buf);
    }
}

Donnees* chargerDonnees(char **filedef)
{
    char file[255], caractere;
    FILE* fichier = NULL;
    Donnees* donnees = NULL;
    long timestamp = 0L, millis = 0L;
    int i = 0, taille = 0, poul = 0;


    if(*filedef != NULL)
    {
       printf("Entrez le nom du fichier [defaut : %s] : ", *filedef);
       scanfAS(file, *filedef);

       if(file == NULL)
       {
          system("CLS");
          system("COLOR 4");
          printf("Le nom du fichier ne peut être vide !");
          exit(1);
       }

       if(realloc(*filedef, sizeof(char)*strlen(file)) == NULL)
       {
          system("CLS");
          system("COLOR 4");
          printf("Chargement des données...\n");
          printf("Erreur allocation variable !");
          exit(1);
       }
       strcpy(*filedef, file);
    }
    else
    {
        printf("Entrez le nom du fichier : ");

        scanfAS(file, NULL);

        if(file[0] == '0')
        {
          system("CLS");
          system("COLOR 4");
          printf("Le nom du fichier ne peut être vide !");
          exit(1);
        }

        *filedef = malloc(sizeof(char)*strlen(file));
        if(filedef == NULL)
        {
          system("CLS");
          system("COLOR 4");
          printf("Chargement des données...\n");
          printf("Erreur allocation variable !");
          exit(1);
       }

       strcpy(*filedef, file);
    }

    printf("Chargement des données...\n");

    fichier = fopen(*filedef, "r");

    if(fichier == NULL)
    {
        system("CLS");
        system("COLOR 4");
        printf("Chargement des données...\n");
        printf("Erreur : impossible d'ouvrier le fichier %s\n", file);
        exit(1);
    }

    do
    {
        caractere = fgetc(fichier);

        if(caractere == '\n')
        {
            taille++;
        }

    }while(caractere != EOF);
    taille++;

    if(taille == 0)
    {
        fclose(fichier);
        system("CLS");
        system("COLOR 4");
        printf("Chargement des données...\n");
        printf("Fichier vide !");
        exit(1);
        return NULL;
    }

    fseek(fichier, 0, SEEK_SET);

    donnees = malloc(taille * sizeof(Donnees));
    if(donnees == NULL)
    {
        system("CLS");
        system("COLOR 4");
        printf("Chargement des données...\n");
        printf("Erreur allocation variable !");
        exit(1);
    }

    while(i < taille)
    {
        fscanf(fichier, "%ld;%ld;%d", &timestamp, &millis, &poul);
        if(timestamp ==  donnees[i-1].date)
        {
            system("CLS");
            system("COLOR 4");
            printf("Chargement des données...\n");
            printf("Erreur parsing du fichier ligne %d !", i);
            exit(1);
        }
        donnees[i].date = timestamp;
        donnees[i].millis = millis;
        donnees[i].pouls = poul;
        donnees[i].lignes = taille;
        i++;
    }

    fclose(fichier);

    return donnees;
}

void afficherDonnees(Donnees *donnees) {

    int i = 0;

    while(i < donnees[0].lignes)
    {
        char buffer[80];
        convertirTStoDate(donnees[i].date, buffer);
        printf("Date et heure : %s\n", buffer);
        printf("Moment execution Arduino : %ld\n", donnees[i].millis);
        printf("Poul enregistré : %d\n\n", donnees[i].pouls);
        i++;
    }

    printf("(%d entrée(s))\n\n", i);
}

void triDate(Donnees *donnees)
{
    int taille = donnees[0].lignes, tab_trie = 0;
    while(tab_trie == 0)
    {
        tab_trie = 1;
        for(int i = 0; i < taille-1; i++)
        {
            if(donnees[i].date > donnees[i+1].date)
            {
                long tmp1 = donnees[i].date;
                int tmp2 = donnees[i].lignes;
                long tmp3 = donnees[i].millis;
                int tmp4 = donnees[i].pouls;

                donnees[i].date = donnees[i+1].date;
                donnees[i].lignes = donnees[i+1].lignes;
                donnees[i].millis = donnees[i+1].millis;
                donnees[i].pouls = donnees[i+1].pouls;

                donnees[i+1].date = tmp1;
                donnees[i+1].lignes = tmp2;
                donnees[i+1].millis = tmp3;
                donnees[i+1].pouls = tmp4;
                tab_trie = 0;
            }
        }
        taille--;
    }
}

void swap(Donnees *donnees, int index, int indexf)
{
    long tmp1 = donnees[index].date;
    int tmp2 = donnees[index].lignes;
    long tmp3 = donnees[index].millis;
    int tmp4 = donnees[index].pouls;

    donnees[index].date = donnees[indexf].date;
    donnees[index].lignes = donnees[indexf].lignes;
    donnees[index].millis = donnees[indexf].millis;
    donnees[index].pouls = donnees[indexf].pouls;

    donnees[indexf].date = tmp1;
    donnees[indexf].lignes = tmp2;
    donnees[indexf].millis = tmp3;
    donnees[indexf].pouls = tmp4;
}

int partition(Donnees *donnees, int deb, int fin)
{
    int compt = deb;
    Donnees pivot = donnees[deb];
    int i = 0;

    for(i = deb+1; i<= fin; i++)
    {
        if(donnees[i].pouls < pivot.pouls)
        {
            compt++;
            swap(donnees, compt, i);
        }
    }
    swap(donnees, compt, deb);
    return compt;
}

void tri_rapide(Donnees *donnees, int debut, int fin)
{
    int pivot = 0;
    if(debut < fin)
    {
        pivot = partition(donnees, debut, fin);
        tri_rapide(donnees, debut, pivot-1);
        tri_rapide(donnees, pivot+1, fin);
    }
}

void tri_Poul(Donnees *donnees)
{
    tri_rapide(donnees, 0, donnees[0].lignes - 1);
}

Donnees* recherchePosterieur(Donnees* donnees)
{
    int i = 0, j = 0;
    Donnees *donnees2 = NULL, *donnees3 = NULL;
    long TS;

    printf("Postérieur à ?\n");

    TS = convertirStringtoTS();

    if(TS == 0L)
    {
        printf("Date invalide\n");
    }
    else
    {
        donnees2 = malloc(donnees[0].lignes * sizeof(Donnees));
        donnees3 = malloc(donnees[0].lignes * sizeof(Donnees));

        if(donnees2 == NULL || donnees3 == NULL)
        {
            system("CLS");
            system("COLOR 4");
            printf("Copie des données...\n");
            printf("Erreur allocation variable !");
            exit(1);
        }

        while(i < donnees[0].lignes)
        {
            donnees2[i].date = donnees[i].date;
            donnees2[i].millis = donnees[i].millis;
            donnees2[i].pouls = donnees[i].pouls;
            donnees2[i].lignes = donnees[i].lignes;
            i++;
        }

        i = 0;

        triDate(donnees2);

        while(i < donnees2[0].lignes)
        {
            if(donnees2[i].date > TS)
            {
                donnees3[j].date = donnees2[i].date;
                donnees3[j].millis = donnees2[i].millis;
                donnees3[j].pouls = donnees2[i].pouls;
                donnees3[j].lignes = donnees2[i].lignes;
                j++;
            }
            i++;
        }

        free(donnees2);

        if(j == 0)
        {
            free(donnees3);
            return NULL;
        }

        if(realloc(donnees3, j * sizeof(Donnees)) == NULL)
        {
            system("CLS");
            system("COLOR 4");
            printf("Copie des données...\n");
            printf("Erreur allocation variable !");
            exit(1);
        }

        i = 0;

        while(i < j)
        {
            donnees3[i].lignes = j;
            i++;
        }
    }
    return donnees3;
}

Donnees* rechercheAnterieur(Donnees* donnees)
{
    int i = 0, j = 0;
    Donnees *donnees2 = NULL, *donnees3 = NULL;
    long TS;

    printf("Antérieur à ?\n");

    TS = convertirStringtoTS();

    if(TS == 0L)
    {
        printf("Date invalide\n");
    }
    else
    {
        donnees2 = malloc(donnees[0].lignes * sizeof(Donnees));
        donnees3 = malloc(donnees[0].lignes * sizeof(Donnees));

        if(donnees2 == NULL || donnees3 == NULL)
        {
            system("CLS");
            system("COLOR 4");
            printf("Copie des données...\n");
            printf("Erreur allocation variable !");
            exit(1);
        }

        while(i < donnees[0].lignes)
        {
            donnees2[i].date = donnees[i].date;
            donnees2[i].millis = donnees[i].millis;
            donnees2[i].pouls = donnees[i].pouls;
            donnees2[i].lignes = donnees[i].lignes;
            i++;
        }

        i = 0;

        triDate(donnees2);

        while(i < donnees2[0].lignes)
        {
            if(donnees2[i].date < TS)
            {
                donnees3[j].date = donnees2[i].date;
                donnees3[j].millis = donnees2[i].millis;
                donnees3[j].pouls = donnees2[i].pouls;
                donnees3[j].lignes = donnees2[i].lignes;
                j++;
            }
            i++;
        }

        free(donnees2);

        if(j == 0)
        {
            free(donnees3);
            return NULL;
        }

        if(realloc(donnees3, j * sizeof(Donnees)) == NULL)
        {
            system("CLS");
            system("COLOR 4");
            printf("Copie des données...\n");
            printf("Erreur allocation variable !");
            exit(1);
        }

        i = 0;

        while(i < j)
        {
            donnees3[i].lignes = j;
            i++;
        }
    }
    return donnees3;
}

Donnees* rechercheLaps(Donnees* donnees) {
    int i = 0, j = 0;
    Donnees *donnees2 = NULL, *donnees3 = NULL;
    long TS, TS2;

    printf("Postérieur à ?\n");

    TS = convertirStringtoTS();

    if(TS == 0L)
    {
        printf("Date invalide\n");
    }

    system("CLS");
    printf("Et antérieur à ?\n");

    TS2 = convertirStringtoTS();

    if(TS == 0L)
    {
        printf("Date invalide\n");
    }
    else
    {
        donnees2 = malloc(donnees[0].lignes * sizeof(Donnees));
        donnees3 = malloc(donnees[0].lignes * sizeof(Donnees));

        if(donnees2 == NULL || donnees3 == NULL)
        {
            system("CLS");
            system("COLOR 4");
            printf("Copie des données...\n");
            printf("Erreur allocation variable !");
            exit(1);
        }

        while(i < donnees[0].lignes)
        {
            donnees2[i].date = donnees[i].date;
            donnees2[i].millis = donnees[i].millis;
            donnees2[i].pouls = donnees[i].pouls;
            donnees2[i].lignes = donnees[i].lignes;
            i++;
        }

        i = 0;

        triDate(donnees2);

        while(i < donnees2[0].lignes)
        {
            if(donnees2[i].date > TS && donnees2[i].date < TS2)
            {
                donnees3[j].date = donnees2[i].date;
                donnees3[j].millis = donnees2[i].millis;
                donnees3[j].pouls = donnees2[i].pouls;
                donnees3[j].lignes = donnees2[i].lignes;
                j++;
            }
            i++;
        }

        free(donnees2);

        if(j == 0)
        {
            free(donnees3);
            return NULL;
        }

        if(realloc(donnees3, j * sizeof(Donnees)) == NULL)
        {
            system("CLS");
            system("COLOR 4");
            printf("Copie des données...\n");
            printf("Erreur allocation variable !");
            exit(1);
        }

        i = 0;

        while(i < j)
        {
            donnees3[i].lignes = j;
            i++;
        }

    }
    return donnees3;
}
