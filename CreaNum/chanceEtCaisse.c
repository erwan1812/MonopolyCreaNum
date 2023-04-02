//
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "fonctions.h"
#include "affichage.h"


#define NOMBRE_CARTE_CHANCE 10
#define NOMBRE_CARTE_COMMUNAUTE 10
#define SALAIRE_PAR_TOUR 200
#define NOMBRE_PROPRIETE 16


void melangeCartes(char** listeCarteChance, char** listeCarteCommunaute)
{
    int melangeChance = 0, melangeCommunaute = 0;
    char memoire[200] = "";



    strcpy(listeCarteChance[0], "Allez a la case de depart. (Collectez 200 euros)");
    strcpy(listeCarteChance[1], "Allez a Rue Lecourbe (Propriete 2 Groupe 1). Collectez votre salaire si vous passez la case depart");
    strcpy(listeCarteChance[2], "Allez a Avenue de Breteuil (Propriete 1 Groupe 7). Collectez votre salaire si vous passez la case depart");
    strcpy(listeCarteChance[3], "La banque vous paie 50 euros");
    strcpy(listeCarteChance[4], "Carte sortez de prison");
    strcpy(listeCarteChance[5], "Reculez de 3 cases");
    strcpy(listeCarteChance[6], "Allez directement en prison, vous ne passez pas par la case depart");
    strcpy(listeCarteChance[7], "Vous faites des reparations sur vos proprietes : Payez 25 euros/maison et 100 euros/hotel");
    strcpy(listeCarteChance[8], "Vous avez ete elu maire, payez 50 euros a chaque joueur.euse");
    strcpy(listeCarteChance[9], "Exces de vitesse : payez 100 euros");



    strcpy(listeCarteCommunaute[0], "Allez a la case depart. (Collectez 200 euros)");
    strcpy(listeCarteCommunaute[1], "Frais de docteur. Payez 50 euros");
    strcpy(listeCarteCommunaute[2], "Carte sortie de prison");
    strcpy(listeCarteCommunaute[3], "Allez directement en prison, vous ne collectez pas votre salaire");
    strcpy(listeCarteCommunaute[4], "Vous faites un vide grenier et gagnez 30 euros");
    strcpy(listeCarteCommunaute[5], "C est votre anniversaire, collectez 10 euros de chaque joueur.euse");
    strcpy(listeCarteCommunaute[6], "Vous recuperez des rentes : gagnez 100 euros");
    strcpy(listeCarteCommunaute[7], "Payez des frais d hopital de 100 euros");
    strcpy(listeCarteCommunaute[8], "Vous avez obtenu la seconde place d un concours de beaute : gagnez 10 euros");
    strcpy(listeCarteCommunaute[9], "Vous heritez de 100 euros");






    for (int i = 0 ; i<NOMBRE_CARTE_CHANCE ; i++)
    {
        melangeChance = rand() % (NOMBRE_CARTE_CHANCE - i);
        strcpy(memoire, listeCarteChance[i]);
        strcpy(listeCarteChance[i], listeCarteChance[melangeChance + i]);
        strcpy(listeCarteChance[melangeChance + i], memoire);
    }
    for (int i = 0 ; i<NOMBRE_CARTE_COMMUNAUTE ; i++)
    {
        melangeCommunaute = rand()%(NOMBRE_CARTE_COMMUNAUTE-i);
        strcpy(memoire, listeCarteCommunaute[i]);
        strcpy(listeCarteCommunaute[i], listeCarteCommunaute[melangeCommunaute+i]);
        strcpy(listeCarteCommunaute[melangeCommunaute+i], memoire);
    }
    return;
}









listeChaineCarte* creationListeChaineChance(char** listeCarteChance)
{


    listeChaineCarte *listeChaineCarteChance = NULL;


    listeChaineCarteChance = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteChance->carte = (char**) calloc( 1 , sizeof(char*) );
    listeChaineCarteChance->carte[0] = (char*) calloc( strlen(listeCarteChance[0])+1 , sizeof(char) );
    strcpy(listeChaineCarteChance->carte[0], listeCarteChance[0]);


    listeChaineCarteChance->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteChance->next->carte = (char**) calloc( 1, sizeof(char*) );
    listeChaineCarteChance->next->carte[0] = (char*) calloc(strlen(listeCarteChance[1])+1, sizeof(char) );
    strcpy(listeChaineCarteChance->next->carte[0], listeCarteChance[1]);

    listeChaineCarteChance->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteChance->next->next->carte = (char**) calloc( 1, sizeof(char*) );
    listeChaineCarteChance->next->next->carte[0] = (char*) calloc(strlen(listeCarteChance[2])+1, sizeof(char) );
    strcpy(listeChaineCarteChance->next->next->carte[0], listeCarteChance[2]);

    listeChaineCarteChance->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteChance->next->next->next->carte = (char**) calloc( 1, sizeof(char*) );
    listeChaineCarteChance->next->next->next->carte[0] = (char*) calloc(strlen(listeCarteChance[3])+1, sizeof(char) );
    strcpy(listeChaineCarteChance->next->next->next->carte[0], listeCarteChance[3]);

    listeChaineCarteChance->next->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteChance->next->next->next->next->carte = (char**) calloc( 1, sizeof(char*) );
    listeChaineCarteChance->next->next->next->next->carte[0] = (char*) calloc(strlen(listeCarteChance[4])+1, sizeof(char) );
    strcpy(listeChaineCarteChance->next->next->next->next->carte[0], listeCarteChance[4]);

    listeChaineCarteChance->next->next->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteChance->next->next->next->next->next->carte = (char**) calloc( 1, sizeof(char*) );
    listeChaineCarteChance->next->next->next->next->next->carte[0] = (char*) calloc(strlen(listeCarteChance[5])+1, sizeof(char) );
    strcpy(listeChaineCarteChance->next->next->next->next->next->carte[0], listeCarteChance[5]);

    listeChaineCarteChance->next->next->next->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteChance->next->next->next->next->next->next->carte = (char**) calloc( 1, sizeof(char*) );
    listeChaineCarteChance->next->next->next->next->next->next->carte[0] = (char*) calloc(strlen(listeCarteChance[6])+1, sizeof(char) );
    strcpy(listeChaineCarteChance->next->next->next->next->next->next->carte[0], listeCarteChance[6]);

    listeChaineCarteChance->next->next->next->next->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteChance->next->next->next->next->next->next->next->carte = (char**) calloc( 1, sizeof(char*) );
    listeChaineCarteChance->next->next->next->next->next->next->next->carte[0] = (char*) calloc(strlen(listeCarteChance[7])+1, sizeof(char) );
    strcpy(listeChaineCarteChance->next->next->next->next->next->next->next->carte[0], listeCarteChance[7]);

    listeChaineCarteChance->next->next->next->next->next->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteChance->next->next->next->next->next->next->next->next->carte = (char**) calloc( 1, sizeof(char*) );
    listeChaineCarteChance->next->next->next->next->next->next->next->next->carte[0] = (char*) calloc(strlen(listeCarteChance[8])+1, sizeof(char) );
    strcpy(listeChaineCarteChance->next->next->next->next->next->next->next->next->carte[0], listeCarteChance[8]);

    listeChaineCarteChance->next->next->next->next->next->next->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteChance->next->next->next->next->next->next->next->next->next->carte = (char**) calloc( 1 , sizeof(char*) );
    listeChaineCarteChance->next->next->next->next->next->next->next->next->next->carte[0] = (char*) calloc( strlen(listeCarteChance[9])+1 , sizeof(char) );
    strcpy(listeChaineCarteChance->next->next->next->next->next->next->next->next->next->carte[0], listeCarteChance[9]);

    listeChaineCarteChance->next->next->next->next->next->next->next->next->next->next = listeChaineCarteChance;



    return (listeChaineCarteChance);
}



listeChaineCarte* creationListeChaineCommunaute(char** listeCarteCommunaute)
{

    listeChaineCarte* listeChaineCarteCommunaute = NULL;


    listeChaineCarteCommunaute = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteCommunaute->carte = (char**) calloc( 1 , sizeof(char*) );
    listeChaineCarteCommunaute->carte[0] = (char*) calloc( strlen(listeCarteCommunaute[0])+1 , sizeof(char) );
    strcpy(listeChaineCarteCommunaute->carte[0], listeCarteCommunaute[0]);


    listeChaineCarteCommunaute->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteCommunaute->next->carte = (char**) calloc( 1 , sizeof(char*) );
    listeChaineCarteCommunaute->next->carte[0] = (char*) calloc( strlen(listeCarteCommunaute[1])+1 , sizeof(char) );
    strcpy(listeChaineCarteCommunaute->next->carte[0], listeCarteCommunaute[1]);

    listeChaineCarteCommunaute->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteCommunaute->next->next->carte = (char**) calloc( 1 , sizeof(char*) );
    listeChaineCarteCommunaute->next->next->carte[0] = (char*) calloc( strlen(listeCarteCommunaute[2])+1 , sizeof(char) );
    strcpy(listeChaineCarteCommunaute->next->next->carte[0], listeCarteCommunaute[2]);

    listeChaineCarteCommunaute->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteCommunaute->next->next->next->carte = (char**) calloc( 1 , sizeof(char*) );
    listeChaineCarteCommunaute->next->next->next->carte[0] = (char*) calloc( strlen(listeCarteCommunaute[3])+1 , sizeof(char) );
    strcpy(listeChaineCarteCommunaute->next->next->next->carte[0], listeCarteCommunaute[3]);

    listeChaineCarteCommunaute->next->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteCommunaute->next->next->next->next->carte = (char**) calloc( 1 , sizeof(char*) );
    listeChaineCarteCommunaute->next->next->next->next->carte[0] = (char*) calloc( strlen(listeCarteCommunaute[4])+1 , sizeof(char) );
    strcpy(listeChaineCarteCommunaute->next->next->next->next->carte[0], listeCarteCommunaute[4]);

    listeChaineCarteCommunaute->next->next->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteCommunaute->next->next->next->next->next->carte = (char**) calloc( 1 , sizeof(char*) );
    listeChaineCarteCommunaute->next->next->next->next->next->carte[0] = (char*) calloc( strlen(listeCarteCommunaute[5])+1 , sizeof(char) );
    strcpy(listeChaineCarteCommunaute->next->next->next->next->next->carte[0], listeCarteCommunaute[5]);

    listeChaineCarteCommunaute->next->next->next->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteCommunaute->next->next->next->next->next->next->carte = (char**) calloc( 1 , sizeof(char*) );
    listeChaineCarteCommunaute->next->next->next->next->next->next->carte[0] = (char*) calloc( strlen(listeCarteCommunaute[6])+1 , sizeof(char) );
    strcpy(listeChaineCarteCommunaute->next->next->next->next->next->next->carte[0], listeCarteCommunaute[6]);

    listeChaineCarteCommunaute->next->next->next->next->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteCommunaute->next->next->next->next->next->next->next->carte = (char**) calloc( 1 , sizeof(char*) );
    listeChaineCarteCommunaute->next->next->next->next->next->next->next->carte[0] = (char*) calloc( strlen(listeCarteCommunaute[7])+1 , sizeof(char) );
    strcpy(listeChaineCarteCommunaute->next->next->next->next->next->next->next->carte[0], listeCarteCommunaute[7]);

    listeChaineCarteCommunaute->next->next->next->next->next->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteCommunaute->next->next->next->next->next->next->next->next->carte = (char**) calloc( 1 , sizeof(char*) );
    listeChaineCarteCommunaute->next->next->next->next->next->next->next->next->carte[0] = (char*) calloc( strlen(listeCarteCommunaute[8])+1 , sizeof(char) );
    strcpy(listeChaineCarteCommunaute->next->next->next->next->next->next->next->next->carte[0], listeCarteCommunaute[8]);

    listeChaineCarteCommunaute->next->next->next->next->next->next->next->next->next = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
    listeChaineCarteCommunaute->next->next->next->next->next->next->next->next->next->carte = (char**) calloc( 1 , sizeof(char*) );
    listeChaineCarteCommunaute->next->next->next->next->next->next->next->next->next->carte[0] = (char*) calloc( strlen(listeCarteCommunaute[9])+1 , sizeof(char) );
    strcpy(listeChaineCarteCommunaute->next->next->next->next->next->next->next->next->next->carte[0], listeCarteCommunaute[9]);

    listeChaineCarteCommunaute->next->next->next->next->next->next->next->next->next->next = listeChaineCarteCommunaute;





    return(listeChaineCarteCommunaute);
}


void realisationCarteChance(dataPartie* partie, int numeroJoueur, int* estCeQuilAPaye, int* finDeTour)
{
    int nombreMaison = 0, nombreHotel = 0, quoiFaire = 0;

    if (strcmp(partie->listeChaineCarteChance->carte[0], "Allez a la case de depart. (Collectez 200 euros)")==0)
    {
        partie->listeJoueur[numeroJoueur].position = 0;
        partie->listeJoueur[numeroJoueur].argent += SALAIRE_PAR_TOUR;
        *estCeQuilAPaye = 1;
        affichagePlateau(*partie);
    }

    else if (strcmp(partie->listeChaineCarteChance->carte[0], "Allez a Rue Lecourbe (Propriete 2 Groupe 1). Collectez votre salaire si vous passez la case depart")==0)
    {
        partie->listeJoueur[numeroJoueur].position = 3;
        deplacementJoueur(partie, numeroJoueur, 1, -1, NULL);
        *estCeQuilAPaye = 2;
        if (partie->listeJoueur[numeroJoueur].position > 3)
        {
            partie->listeJoueur[numeroJoueur].argent += SALAIRE_PAR_TOUR;
        }
    }

    else if (strcmp(partie->listeChaineCarteChance->carte[0], "Allez a Avenue de Breteuil (Propriete 1 Groupe 7). Collectez votre salaire si vous passez la case depart")==0)
    {
        partie->listeJoueur[numeroJoueur].position = 25;
        deplacementJoueur(partie, numeroJoueur, 1, -1, NULL);
        *estCeQuilAPaye = 2;
        if (partie->listeJoueur[numeroJoueur].position > 25)
        {
            partie->listeJoueur[numeroJoueur].argent += SALAIRE_PAR_TOUR;
        }
    }

    else if (strcmp(partie->listeChaineCarteChance->carte[0], "La banque vous paie 50 euros")==0)
    {
        partie->listeJoueur[numeroJoueur].argent += 50;
        *estCeQuilAPaye = 1;
        affichagePlateau(*partie);
    }

    else if (strcmp(partie->listeChaineCarteChance->carte[0], "Carte sortez de prison")==0)
    {
        partie->listeJoueur[numeroJoueur].carteSortiePrisonChance +=1;
        partie->listeChaineCarteChance->next->next->next->next->next->next->next->next = partie->listeChaineCarteChance->next;
        *estCeQuilAPaye = 1;
        affichagePlateau(*partie);
    }

    else if (strcmp(partie->listeChaineCarteChance->carte[0], "Reculez de 3 cases")==0)
    {
        deplacementJoueur(partie, numeroJoueur, 0, -3, NULL);
    }

    else if (strcmp(partie->listeChaineCarteChance->carte[0], "Allez directement en prison, vous ne passez pas par la case depart")==0)
    {
        prison(partie->listeJoueur, numeroJoueur);
        *estCeQuilAPaye = 1;
        *finDeTour = 1;
        affichagePlateau(*partie);
    }

    else if (strcmp(partie->listeChaineCarteChance->carte[0], "Vous faites des reparations sur vos proprietes : Payez 25 euros/maison et 100 euros/hotel")==0)
    {
        for (int i = 0 ; i < NOMBRE_PROPRIETE ; i++)
        {
            if (partie->listePropriete[i].numeroProprietaire == numeroJoueur && (partie->listePropriete[i].nombreMaison + partie->listePropriete[i].nombreHotel > 0))
            {
                if (partie->listePropriete[i].nombreMaison > 0)
                {
                    nombreMaison += partie->listePropriete[i].nombreMaison;
                }
                else
                {
                    nombreHotel++;
                }
            }
        }
        *estCeQuilAPaye = paye(partie, numeroJoueur, -1, nombreMaison*25+nombreHotel*100);
        *estCeQuilAPaye = 1;
        printf("Vous avez %d maisons et %d hotels\nLa facture de reparation est donc de %d\n", nombreMaison, nombreHotel, nombreMaison*25+nombreHotel*100);
    }

    else if (strcmp(partie->listeChaineCarteChance->carte[0], "Vous avez ete elu maire, payez 50 euros a chaque joueur.euse")==0)
    {
        for (int i = 0 ; i < partie->donnesDeLaPartie.nombreJoueur ; i++)
        {
            if (partie->listeJoueur[i].etat != -1 && i != numeroJoueur && partie->listeJoueur[i].etat != 10)
            {
                while (*estCeQuilAPaye == 0)
                {
                    printf("Que veux tu faire :\n"
                           "1/ Payer les 50 euros a %s\n"
                           "2/ Vendre des maisons  ou hypotheque\n"
                           "3/ Marchander\n", partie->listeJoueur[i].nom);

                    menuAvantPaye(partie, numeroJoueur, i, estCeQuilAPaye);
                }

                *estCeQuilAPaye = 0;
            }
        }
        *estCeQuilAPaye = 1;
    }

    else if (strcmp(partie->listeChaineCarteChance->carte[0], "Exces de vitesse : payez 100 euros")==0)
    {
        *estCeQuilAPaye = paye(partie, numeroJoueur, -1, 100);
    }

}

void realisationCarteCommunaute(dataPartie* partie, int numeroJoueur, int* estCeQuilAPaye, int* finDeTour )
{

    if (strcmp(partie->listeChaineCarteCommunaute->carte[0], "Allez a la case depart. (Collectez 200 euros)")==0)
    {
        partie->listeJoueur[numeroJoueur].position = 0;
        partie->listeJoueur[numeroJoueur].argent += SALAIRE_PAR_TOUR;
        *estCeQuilAPaye = 1;
        affichagePlateau(*partie);
    }

    else if (strcmp(partie->listeChaineCarteCommunaute->carte[0], "Frais de docteur. Payez 50 euros")==0)
    {
        *estCeQuilAPaye = paye(partie, numeroJoueur, -1, 50);
        *estCeQuilAPaye = 1;
    }

    else if (strcmp(partie->listeChaineCarteCommunaute->carte[0], "Carte sortie de prison")==0)
    {
        partie->listeJoueur[numeroJoueur].carteSortiePrisonCommunaute +=1;
        partie->listeChaineCarteCommunaute->next->next->next->next->next->next->next->next = partie->listeChaineCarteChance->next;
        *estCeQuilAPaye = 1;
        affichagePlateau(*partie);
    }

    else if (strcmp(partie->listeChaineCarteCommunaute->carte[0], "Allez directement en prison, vous ne collectez pas votre salaire")==0)
    {
        prison(partie->listeJoueur, numeroJoueur);
        *estCeQuilAPaye = 1;
        *finDeTour = 1;
        affichagePlateau(*partie);
    }

    else if (strcmp(partie->listeChaineCarteCommunaute->carte[0], "Vous faites un vide grenier et gagnez 30 euros")==0)
    {
        partie->listeJoueur[numeroJoueur].argent += 30;
        *estCeQuilAPaye = 1;
        affichagePlateau(*partie);
    }

    else if (strcmp(partie->listeChaineCarteCommunaute->carte[0], "C est votre anniversaire, collectez 10 euros de chaque joueur.euse")==0)
    {
        for (int i = 0 ; i < partie->donnesDeLaPartie.nombreJoueur ; i++)
        {
            if (partie->listeJoueur[i].etat != -1 && i != numeroJoueur)
            {
                *estCeQuilAPaye = paye(partie, i, numeroJoueur, 10); //un joueur n'ayant pas assez en liquide sera elimine
                if (*estCeQuilAPaye == 0)
                {
                    faillite(partie, i, numeroJoueur);
                }
            }
        }
        *estCeQuilAPaye = 1;
    }

    else if (strcmp(partie->listeChaineCarteCommunaute->carte[0], "Vous recuperez des rentes : gagnez 100 euros")==0)
    {
        partie->listeJoueur[numeroJoueur].argent += 100;
        *estCeQuilAPaye = 1;
        affichagePlateau(*partie);
    }

    else if (strcmp(partie->listeChaineCarteCommunaute->carte[0], "Payez des frais d hopital de 100 euros")==0)
    {
        *estCeQuilAPaye = paye(partie, numeroJoueur, -1, 100);
    }

    else if (strcmp(partie->listeChaineCarteCommunaute->carte[0], "Vous avez obtenu la seconde place d un concours de beaute : gagnez 10 euros")==0)
    {
        partie->listeJoueur[numeroJoueur].argent += 10;
        *estCeQuilAPaye = 1;
        affichagePlateau(*partie);
    }

    else if (strcmp(partie->listeChaineCarteCommunaute->carte[0], "Vous heritez de 100 euros")==0)
    {
        partie->listeJoueur[numeroJoueur].argent += 100;
        *estCeQuilAPaye = 1;
        affichagePlateau(*partie);
    }
}




void libererListeCarte(char** listeCarteChance, char** listeCarteCommunaute)
{
    if (listeCarteChance != NULL)
    {
        for (int i = 0 ; i<NOMBRE_CARTE_CHANCE ; i++)
        {
            if (listeCarteChance[i] != NULL)
            {
                free(listeCarteChance[i]);
            }
        }
        free(listeCarteChance);
    }


    if (listeCarteCommunaute != NULL)
    {
        for (int i = 0 ; i<NOMBRE_CARTE_COMMUNAUTE ; i++)
        {
            if (listeCarteCommunaute[i] != NULL)
            {
                free(listeCarteCommunaute[i]);
            }
        }
        free(listeCarteCommunaute);
    }

    return;
}

void libererListeChaineCarte(listeChaineCarte* listeChaineCarteChance, listeChaineCarte* listeChaineCarteCommunaute)
{
    listeChaineCarte *memoireChance = NULL;
    listeChaineCarte *memoireCommunaute = NULL;




    for (int i = 0 ; i<NOMBRE_CARTE_CHANCE ; i++)
    {
        if (listeChaineCarteChance != NULL)
        {
            memoireChance = listeChaineCarteChance->next;

            if (listeChaineCarteChance->carte != NULL)
            {
                free(listeChaineCarteChance->carte[0]);
                free(listeChaineCarteChance->carte);
            }


            free(listeChaineCarteChance);
        }

        listeChaineCarteChance = memoireChance ;
    }

    for (int i = 0 ; i<NOMBRE_CARTE_COMMUNAUTE ; i++)
    {
        if (listeChaineCarteCommunaute != NULL)
        {
            memoireCommunaute = listeChaineCarteCommunaute->next;

            if (listeChaineCarteCommunaute->carte != NULL)
            {
                free(listeChaineCarteCommunaute->carte[0]);
                free(listeChaineCarteCommunaute->carte);
            }

            free(listeChaineCarteCommunaute);
        }

        listeChaineCarteCommunaute = memoireCommunaute;
    }

    return;
}
