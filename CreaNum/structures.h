//
//

#ifndef MONOPOLY_STRUCTURES_H
#define MONOPOLY_STRUCTURES_H

typedef struct listeChaineCarte {
    char** carte;
    struct listeChaineCarte* next;
}listeChaineCarte;



typedef struct {
    char* nom;
    unsigned int argent;
    unsigned int position;
    int etat;        //4 c'est normal ; 1 c'est en prison depuis 1 tour, 2 c'est en prison depuis 2 tours et 3 en prison depuis 3 tours; 0 c'est sur le parc gratuit et -1 alors il est mort
    int carteSortiePrisonChance, carteSortiePrisonCommunaute; //nombre de carte sortie de prison qu'a le joueur (differencie les cartes sortie de prison chance et communaute pour pouvoir remettre la carte dans la bonne pile)
}joueur;         // amelioration : liste chainé pour prendre moins de memoire lorsque un joueur meurt plutot que de stocker des 0 inutiles



typedef struct {
    int numeroPropriete;
    int etat; // 0 pour en vente / 1 pour acheter / 2 pour acheter et hypotheque / 3 chance / 4 communaute / 5 depart / 6 gare / 7 visite prison / 8 parc gratuit / 9 prison / 10 taxe
    int taxe;

    char* nom; //ex boulevard de belleville


}cases;

typedef struct {

    int numeroProprietaire;
    int nombreMaison, nombreHotel;
    int prixAchat; // prix achat de la propriete
    int hypotheque, prixTerrainNu, prix1Maison, prix2Maison, prix3Maison, prix4Maison, prixHotel, prixAchatMaison;
    int nombreProprieteDeCetteCouleur, couleur;
    int numeroCaseDesProprieteDeCetteCouleur[3];
}propriete;



typedef struct {
    int nombreJoueur, nombreMaison, nombreHotel, cheatMode, nombreJoueurLogique;
}donnees;

typedef struct {
    int aQuiDeJouer;
    donnees donnesDeLaPartie;
    cases* listeCase;
    propriete* listePropriete;
    joueur* listeJoueur;
    listeChaineCarte* listeChaineCarteChance;
    listeChaineCarte* listeChaineCarteCommunaute;
}dataPartie;

#endif //MONOPOLY_STRUCTURES_H
