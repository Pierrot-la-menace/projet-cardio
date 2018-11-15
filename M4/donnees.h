//on inclue toutes bibliothèques nécessaires
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#ifndef DONNEES_H_INCLUDED
#define DONNEES_H_INCLUDED

//contient la structure données
typedef struct {

    long date;
    long millis;
    int pouls;
    int lignes;

}Donnees;

//contient tout les prototypes nécessaire à la manipulation des données
long convertirStringtoTS();
void scanfAS(char*, char*);
int scanfAI(int);
long scanfAL(int);
Donnees* chargerDonnees(char **);
void afficherDonnees(Donnees*);
void triDate(Donnees*);
int partition(Donnees*, int, int);
void tri_rapide(Donnees*, int, int);
void tri_Poul(Donnees*);
Donnees* recherchePosterieur(Donnees*);
Donnees* rechercheAnterieur(Donnees*);
Donnees* rechercheLaps(Donnees*);

#endif
