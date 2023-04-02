//

//

#include "structures.h"

#ifndef MONOPOLY_PARTIE_H
#define MONOPOLY_PARTIE_H


void initDataPartie(dataPartie* partie);//initilise toutes les données de la partie a NULL
dataPartie creePartie();//permet d'initialiser toutes les données de la partie (les differentes cases, joueurs...)
dataPartie bouclePartie(dataPartie* partie);//boucle realisant le tour des joueurs
void libererTout(dataPartie* partie);//permet de liberer toutes les donnees qui doivent etre liberes



#endif //MONOPOLY_PARTIE_H