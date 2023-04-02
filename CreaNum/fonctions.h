//
//

#include "structures.h"

#ifndef MONOPOLY_FONCTIONS_H
#define MONOPOLY_FONCTIONS_H


void flush();//permet de vider le buffer
int saisirCarac (char *phrase, int taille);//permet de faire saisir des mots a une personne de maniere securise
int saisirEntier();//permet de faire saisir des entiers a une ersonne de maniere securise
int lancerDe(dataPartie* partie);//genere un nombre aleatoire entre 1 et 6 compris ou demande un entier (si le cheat mode est actif)
void abandon(dataPartie* partie, int numeroJoueur);//permet d'eleminer un joueur s'il abandonne
void prison(joueur* listeJoueur, int numeroJoueur);//permet d'envoyer un joueur en prison
void remiseCarteSortiePrison(dataPartie* partie, int chanceOuCommunaute);//remet une carte sortie de prison en dessous de la pile
void menuAvantPaye(dataPartie* partie, int numeroJoueur, int aQuiPaye, int* estCeQuilAPaye);//si un joueur doit payer mais n'a pas assez de liquide sans etre en faillite, il peut vendre des batiments


int tourDuJoueur(dataPartie* partie, int numeroJoueur, int compteurDoubleDaffile, int* finDeTour);//fait jouer le joueur(lancer de dé) en prenant en compte s'il est en prison
void deplacementJoueur (dataPartie* partie, int numeroJoueur, int valeurDe1, int valeurDe2, int* finDeTour);//fait se delpacer un joueur
void realisationCaseTaxe(dataPartie* partie, int numeroJoueur, int* EstCeQuIlAPaye);//debite le joueur du montant de la taxe de la case
void chargeToiBinaire(dataPartie * tab);//permet de charger une partie deja sauvegarde
void sauvegardeToiDansUnFichierBinaire(dataPartie * tab);//permet de sauvegarder une partie



void achatMaison(dataPartie* partie, int numeroJoueur);//permet a un joueur d'acheter une maison sur un de ses groupes de proprietes
int verifPasDeMaison(propriete* listePropriete, cases* listeCase, int quellePropriete);//verifie si un terrain contient des maison/hotel
int verifCarteSortieDePrison(joueur* listeJoueur, int numeroJoueur);//verifie si un joueur posse une carte sortie de prison
void marchandage(dataPartie* partie, int numeroJoueur);//permet de marchander une propriete ou une carte sortie de prison avec qql d'autre
void hypotheque(dataPartie*  partie, int numeroJoueur);//permet d'hypothequer ou de vendre des maisons


int verifArgent(joueur* listeJoueur, int combien, int numeroJoueur);//verifie si un joueur a assez d'argent pour payer
void achat(dataPartie* partie, int numeroJoueur, unsigned int quelTerrain);//permet a un joueur d'acheter une propriete
int boolFaillite(dataPartie* partie, int numeroJoueur, int combien);//verifie si un joueur a assez d'argent (propriete et maisons compris)
void faillite(dataPartie* partie, int numeroJoueur, int quiRecoit);//elimine un joueur car il est en faillite
int paye(dataPartie* partie, int quiPaye, int quiRecoit, int combien);//permet de faire payer un joueur a la banque ou a un autre joueur







#endif //MONOPOLY_FONCTIONS_H
