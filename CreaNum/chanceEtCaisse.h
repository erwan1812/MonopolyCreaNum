//
//

#ifndef MONOPOLY_CHANCEETCAISSE_H
#define MONOPOLY_CHANCEETCAISSE_H

void melangeCartes(char** listeCarteChance, char** listeCarteCommunaute);
void libererListeCarte(char** listeCarteChance, char** listeCarteCommunaute);

listeChaineCarte* creationListeChaineChance(char** listeCarteChance);
listeChaineCarte* creationListeChaineCommunaute(char** listeCarteCommunaute);
void realisationCarteChance(dataPartie* partie, int numeroJoueur, int* estCeQuilAPaye, int* finDeTour);
void realisationCarteCommunaute(dataPartie* partie, int numeroJoueur, int* estCeQuilAPaye, int* finDeTour);
void libererListeChaineCarte(listeChaineCarte* listeChaineCarteChance, listeChaineCarte* listeChaineCarteCommunaute);

#endif //MONOPOLY_CHANCEETCAISSE_H
