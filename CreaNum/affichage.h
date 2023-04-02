//
//

#include "structures.h"

#ifndef MONOPOLY_AFFICHAGE_H
#define MONOPOLY_AFFICHAGE_H

void affichageMenuPrincipal();
void affichageRegles();
void affichageNomEquipeProjet();
void saisitInvalide();
void afficherMenuJoueurDebut();
void afficherMenuJoueurFinAchat();
void afficherMenuJoueurFinPaye();
void afficherMenuJoueurFinCarte();
void afficherMenuJoueurFinTaxe();
void afficherMenuJoueurFinRien();


void affichagePlateau(dataPartie partie);
void affichagePrixOuProprietaire(dataPartie partie, int numeroPropriete, int quelPropriete);
void affichageStatsJoueur(dataPartie partie, int numeroJoueur);
void affichageJoueur(dataPartie partie, unsigned int positionDeTous[8], int numeroCase);
void parcourTableau(unsigned int tableau[8], int tailleLogiqueTableau, int** position, int numeroCase);

#endif //MONOPOLY_AFFICHAGE_H
