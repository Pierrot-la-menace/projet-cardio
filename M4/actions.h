#include "donnees.h"
#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

//contient tout les prototypes de action.c
void convertirTStoDate(long, char*);
int moyennePouls(Donnees*);
void tri(Donnees* donnees);
void rechercheDate(Donnees* donnees);
Donnees* extremumsPouls(Donnees*);
void bilan(Donnees*);

#endif
