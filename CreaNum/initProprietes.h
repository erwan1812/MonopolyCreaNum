//

//

#include "structures.h"

#ifndef MONOPOLY_INITPROPRIETES_H
#define MONOPOLY_INITPROPRIETES_H


void initCases(cases** listeCase); //initialise les cases du plateau (allocution dynamique)
void initPropriete(propriete** listePropriete); //initialise toutes les proprietes du plateau
void libererListePropriete(propriete* listePropriete); //libere toutes les donnes des cases
void libererListeCase(cases* listeCase); //libere toutes les donnees des proprietes

#endif //MONOPOLY_INITPROPRIETES_H
