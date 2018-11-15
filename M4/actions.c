/* action.c

Contient toutes les fonctions pour l'éxecution des fonctionnalités du programme

*/
#include "actions.h"

void convertirTStoDate(long timeStamp, char *buf)
{
    //on cacule le TimeStamp et on set la structure tm
    time_t t = timeStamp;
    struct tm tm = *localtime(&t);

    strftime(buf, 80, "Le %d/%m/%Y à %H:%M:%S", &tm); //fonction dans time.h qui permet de retourner une chaîne formatttée
}

int moyennePouls(Donnees *donnees)
{
    //calcul de la moyenne des pouls

    //déclaration des variables
    int i = 0, total = 0, moy = 0, choix2 = 0;
    char choix[255];
    Donnees *donnees2 = NULL; //contiendra la zone de calcul

    //on demande où est-ce qu'on effectue le calcul
    printf("Rechercher en global ou sur un laps de temps donné (global/laps) ? (défaut : global) ");
    scanfAS(choix, "global");

    //on le met en minuscule pour éviter les problèmes de casse
    while(i < strlen(choix))
    {
        choix[i] = tolower(choix[i]);
        i++;
    }

    //on compare
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
        //on retourne -1 en cas d'erreur
        printf("Opération invalide\n");
        return -1;
    }

    i = 0;

    switch(choix2) {
        case 0 :
            //on calcule sur la globalité
            while(i < donnees[0].lignes)
            {
                total = total + donnees[i].pouls;
                i++;
            }
            moy = total / donnees[0].lignes;
            break;
        case 1 :
            donnees2 = rechercheLaps(donnees); //on calcule sur ce que la fonction nous retournera
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
            free(donnees2);//libération de l'espace
            break;
        default :
            return -1;
    }

    return moy;
}

void tri(Donnees* donnees)
{
    //fonction qui demande le tri
    char type[255];
    int i = 0;

    printf("Quel type de tri (date/pouls) ? (défaut : pouls) ");
    scanfAS(type, "pouls");

    //même manipulation que la dernière fonction
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
    //fonction qui permet de vérifier si la recherche ne retourne pas NULL
    system("CLS");
    if(donnees != NULL)
    {
        printf("\nVoici les entrées qui correspondent à vos critères :\n\n");
        afficherDonnees(donnees);
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

    //on demande les critères
    printf("Quel type de recherche souhaitez vous faire ?\n1 : Recherche postérieur à [date]\n2 : Recherche antérieur à [date]\n3 : Recherche dans un laps de temps\n");
    choix = scanfAI(-1);

    switch(choix) {
        //on recherche et on affiche les données
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
    //Fonction qui permet de retourner les entrées qui contiennent les extremums des pouls

    //déclaration variables
    Donnees *donnees2 = NULL, *donnees3 = NULL;
    int i = 0, choix2 = 0;
    char choix[255];


    donnees2 = malloc(donnees[0].lignes * sizeof(Donnees));//permet de définir l'étendue de la recherche
    donnees3 = malloc(2 * sizeof(Donnees));//on a que 2 extremums

    if(donnees2 == NULL || donnees3 == NULL)
    {
        system("CLS");
        system("COLOR 4");
        printf("Copie des données...\n");
        printf("Erreur allocation variable !");
        exit(1);
    }


    //on demande où est-ce qu'on effectue la recherche
    printf("Rechercher en global ou sur un laps de temps donné (global/laps) ? (défaut : laps) ");
    scanfAS(choix, "laps");

    //même manipulation que les dernières fonctions
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
        return NULL;
    }

    i = 0;

    switch(choix2) {
        case 0 :
            //copie de l'intégralité des données
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
            free(donnees2); //on libère l'espace
            donnees2 = rechercheLaps(donnees); //on prend les données qui nous intérresse
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

    tri_Poul(donnees2); //on trie par ordre de date

    //on prends les deux extremitées du tableau
    donnees3[0].date = donnees2[0].date;
    donnees3[0].millis = donnees2[0].millis;
    donnees3[0].pouls = donnees2[0].pouls;
    donnees3[0].lignes = 2;

    donnees3[1].date = donnees2[i].date;
    donnees3[1].millis = donnees2[i].millis;
    donnees3[1].pouls = donnees2[i].pouls;
    donnees3[1].lignes = 2;

    free(donnees2); //on libère l'espace devenu inutile

    return donnees3;
}

void bilan(Donnees *donnees)
{
    //Fonction qui permet de réaliser un bilan de santé selon ce qui est marqué dans le guide du projet

    //déclaration des variables
    const int bpm[6][2] = {{140, 50}, {110, 40}, {105, 35}, {95, 30}, {70, 10}, {65, 5}}; //{moyenne, variation max}
    int index = 0, moyenne = 0;

    system("CLS");

    //on demande l'âge de l'utilisateur
    printf("Quel est vôtre âge (en années) ? [défaut : adulte] ");
    index = scanfAI(40);

    if(index >= 0)
    {
        //on met la bonne valeur dans l'index pour le tableau
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

        //on précise si le bilan peut ne pas être précis
        if(donnees[0].lignes <= 5)
        {
            printf("Votre bilan peut ne pas être précis : on ne calcule la moyenne qu'à partir de %d nombres\n", donnees[0].lignes);
        }

        //on calcule la moyenne
        moyenne = moyennePouls(donnees);

        //on comparation si la moyenne obtenue est dans la moyenne +/- la variation du tableau
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
       //si l'âge est négatif
       printf("Impossible de faire un bilan pour quelqu'un qui n'est pas né...\n");
    }
}
