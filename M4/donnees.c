/* donnees.c

Contient toutes les fonctions pour la manipulation des données

*/
#include "donnees.h"
#include "actions.h"

long convertirStringtoTS()
{
    //déclaration des variable
    time_t TS;
    struct tm tm;
    long annee = 0L, mois = 0L, jour = 0L, heure = 0L, minute = 0L, seconde = 0L, timeStamp = 0L;
    const int NB_JOUR_MOIS[2][12] = {
	{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
	{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}};

	time(&TS); //retour le TimeStamp du système
    tm = *localtime(&TS); //retourne la structure tm à partir du TimeStamp

    printf("Année [%d]: ", tm.tm_year + 1900); //tm.tm_year retourne le nombre d'années depuis 1900
    annee = scanfAL(tm.tm_year + 1900);
    printf("Mois [%d]: ", tm.tm_mon + 1);//tm.tm_mon retourne le nombre de mois écoulés depuis le début de l'année (0 - 11)
    mois = scanfAL(tm.tm_mon + 1);
    printf("Jour [%d]: ", tm.tm_mday);//tm.tm_mday retourne le jour du mois (1 - 31)
    jour = scanfAL(tm.tm_mday);
    printf("Heure [%d]: ", tm.tm_hour);//tm.tm_hour retourne les heures (0 - 23)
    heure = scanfAL(tm.tm_hour);
    printf("Minute [%d]: ", tm.tm_min);//tm.tm_min retourne les minutes (0 - 59)
    minute = scanfAL(tm.tm_min);
    printf("Seconde [%d]: ", tm.tm_sec);//tm.tm_hour retourne les secondes (0 - 59)
    seconde = scanfAL(tm.tm_sec);

    //On vérifie que l'utilisateur n'a pas rentré n'importe quoi
    if(annee >= 1970 && 1 <= mois && mois <= 12 && 1 <= jour && jour <= 31 && 0 <= heure && heure <= 23 && 0 <= minute && minute <= 59 && 0 <= seconde && seconde <= 59)
    {
        /* Calcul du TimeStamp
        Nombre de seconde dans :
         - 1 année : 31536000
         - 1 jour : 86400
                                */

        annee = annee - 1970;

        timeStamp = (jour - 1) * 86400;

        timeStamp = timeStamp + (heure * 3600);

        timeStamp = timeStamp + (minute * 60);

        timeStamp = timeStamp + seconde;

        timeStamp = (timeStamp + annee * 31536000 + round(((double)annee/4) - 0.1) * 86400) - 3600; //prise en compte des années bissextiles depuis 1970 plus retirer une heure de décalage (On a 1 heure d'avance par rapport à l'UTC)

        if((annee - 2)%4 == 0) //si année bissextiles
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
    //fonction home-made qui permet de retourner une chaîne par défaut si la chaîne d'entrée est vide
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
    //fonction home-made qui permet de retourner un integer par défaut si la chaîne d'entrée est vide

    char buf[255];

    fflush(stdin);
    gets(buf);

    if(strlen(buf) == 0)
    {
        if(defaut != -1)
            return defaut;
        else
            return 0;
    }
    else
    {
       return atoi(buf);
    }
}

long scanfAL(int defaut)
{
    //fonction home-made qui permet de retourner un long par défaut si la chaîne d'entrée est vide

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
    /*Fonction qui charge les données
      Le double pointeur permet la modification du choix par défaut*/


    //déclaration variables
    char file[255], caractere;
    FILE* fichier = NULL;
    Donnees* donnees = NULL;
    long timestamp = 0L, millis = 0L, timestampDebut = 0L;
    int i = 0, taille = 0, poul = 0;


    if(*filedef != NULL) //si le choix par défaut n'est pas nul
    {
       printf("Entrez le nom du fichier [defaut : %s] : ", *filedef);

       scanfAS(file, *filedef); //on demande le nom du fichier

       if(file == NULL)
       {
          system("CLS");
          system("COLOR 4");
          printf("Le nom du fichier ne peut être vide !");
          exit(1);
       }

       if(realloc(*filedef, sizeof(char)*strlen(file)) == NULL) //on réalloue au cas où le nom change
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

        scanfAS(file, NULL); //on demande le nom du fichier

        if(file[0] == '0')
        {
          system("CLS");
          system("COLOR 4");
          printf("Le nom du fichier ne peut être vide !");
          exit(1);
        }

        *filedef = malloc(sizeof(char)*strlen(file)); //on alloue la mémoire pour stocker le nom
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

    fichier = fopen(*filedef, "r"); //tentative d'ouverture du fichier

    if(fichier == NULL)
    {
        system("CLS");
        system("COLOR 4");
        printf("Chargement des données...\n");
        printf("Erreur : impossible d'ouvrir le fichier %s\n", file);
        exit(1);
    }

    //on compte le nombre de ligne
    do
    {
        caractere = fgetc(fichier);

        if(caractere == '\n')
        {
            taille++;
        }

    }while(caractere != EOF);

    if(taille == 0) //si le fichier est vide
    {
        fclose(fichier);
        system("CLS");
        system("COLOR 4");
        printf("Chargement des données...\n");
        printf("Fichier vide !");
        exit(1);
        return NULL;
    }

    fseek(fichier, 0, SEEK_SET); //retour début du fichier

    donnees = malloc(taille * sizeof(Donnees)); //on  alloue la mémoire nécessaire pour stocker les données

    if(donnees == NULL)
    {
        system("CLS");
        system("COLOR 4");
        printf("Chargement des données...\n");
        printf("Erreur allocation variable !");
        exit(1);
    }

    fscanf(fichier, "%ld;;", &timestampDebut);
    while(i < taille)
    {
        //on parse le fichier
        fscanf(fichier, "%ld;%d;", &millis, &poul);
        timestamp = timestampDebut + (long)round((double)millis/1000);

       //on set les données
        donnees[i].date = timestamp;
        donnees[i].millis = millis;
        donnees[i].pouls = poul;
        donnees[i].lignes = taille;

        i++;
    }

    fclose(fichier); //fermeture du fichier

    return donnees; //on retourne le pointeur
}

void afficherDonnees(Donnees *donnees) {

    /* Fonction qui affiche tout ce qui a dans le pointeur passé en paramètre via une boucle*/
    int i = 0;

    while(i < donnees[0].lignes)
    {
        char buffer[80];
        convertirTStoDate(donnees[i].date, buffer);
        printf("Date et heure : %s\n", buffer);
        printf("Moment execution Arduino : %ld\n", donnees[i].millis);
        printf("Pouls enregistré : %d\n\n", donnees[i].pouls);
        i++;
    }

    printf("(%d entrée(s))\n\n", i);
}

void triDate(Donnees *donnees)
{
    //Algorithme de tri à bulle

    int taille = donnees[0].lignes, tab_trie = 0;

    while(tab_trie == 0)
    {
        tab_trie = 1;
        for(int i = 0; i < taille-1; i++)
        {
            if(donnees[i].date > donnees[i+1].date)
            {
                //Inversion des deux cases
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
    //Fonction qui inverse les données pour le tri rapide

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
    //Fonction qui fait partie de l'algorithme de tri rapide

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
    //Fonction récursive principale du tri rapide
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
    //Fonction de lancement du tri rapide
    tri_rapide(donnees, 0, donnees[0].lignes - 1);
}

Donnees* recherchePosterieur(Donnees* donnees)
{
    //Permet de réaliser la recherche pour toutes les données postérieur à une date

    //déclaration des variables
    int i = 0, j = 0;
    Donnees *donnees2 = NULL, *donnees3 = NULL;
    long TS;

    printf("Postérieur à ?\n");

    TS = convertirStringtoTS(); //on demande la date

    if(TS == 0L)
    {
        //si la fonction renvoie OL, cela signifie que la date n'est pas correcte. recherchePosterieur renvoie donc NULL
        printf("Date invalide\n");
    }
    else
    {
        //on copie les données pour ne pas affecter les données qui sont chargées.
        donnees2 = malloc(donnees[0].lignes * sizeof(Donnees)); //contient la copie
        donnees3 = malloc(donnees[0].lignes * sizeof(Donnees)); //contient le final

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

        triDate(donnees2); //on tri par date pour être sûr et rendre la fonction plus efficace

        while(i < donnees2[0].lignes) //on regarde le nombre de données qui correspondent aux critères et on les copies dans donnees3
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

        free(donnees2); //donnees2 devenue inutile

        if(j == 0) //si aucune entrée, on libère donnee3 et on renvoie NULL
        {
            free(donnees3);
            return NULL;
        }

        if(realloc(donnees3, j * sizeof(Donnees)) == NULL) //on realloue la bonne quantité de mémoire
        {
            system("CLS");
            system("COLOR 4");
            printf("Copie des données...\n");
            printf("Erreur allocation variable !");
            exit(1);
        }

        i = 0;

        while(i < j) //on set bien la bonne longueur sur donnee3
        {
            donnees3[i].lignes = j;
            i++;
        }
    }
    return donnees3;
}

Donnees* rechercheAnterieur(Donnees* donnees)
{
    //Même fonction ma pour les données qui sont antérieurs
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

    //Même fonction ma pour les données qui sont comprise dans laps de temps

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
