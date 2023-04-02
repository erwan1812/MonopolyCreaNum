//

//


#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "initProprietes.h"

#define MAX_CARAC_NOM_CASE 87
#define NOMBRE_CASE 32
#define NOMBRE_PROPRIETE 16

void initCases(cases** listeCase)
{
    *listeCase = (cases *) calloc(NOMBRE_CASE, sizeof(cases));

    for (int i = 0 ; i<32 ; i++)
    {
        (*listeCase)[i].nom = (char*) calloc(MAX_CARAC_NOM_CASE, sizeof(char));
    }

    (*listeCase)[0].numeroPropriete = -1;
    strcpy((*listeCase)[0].nom, "Depart");
    (*listeCase)[0].etat = 5;


    (*listeCase)[1].numeroPropriete = 0;
    strcpy((*listeCase)[1].nom, "Boulevard de Belleville");


    (*listeCase)[2].numeroPropriete = -1;
    strcpy((*listeCase)[2].nom, "Taxe d'habitation : Payez 100 euros");
    (*listeCase)[2].etat = 10;
    (*listeCase)[2].taxe = 100;



    (*listeCase)[3].numeroPropriete = 1;
    strcpy((*listeCase)[3].nom, "Rue Lecourbe");


    (*listeCase)[4].numeroPropriete = -1;
    strcpy((*listeCase)[4].nom, "Raccourci : Avancez a la case 13");
    (*listeCase)[4].etat = 6;


    (*listeCase)[5].numeroPropriete = 2;
    strcpy((*listeCase)[5].nom, "Rue de Vaugirard");


    (*listeCase)[6].numeroPropriete = -1;
    strcpy((*listeCase)[6].nom, "Tirez une carte communaute");
    (*listeCase)[6].etat = 4;



    (*listeCase)[7].numeroPropriete = 3;
    strcpy((*listeCase)[7].nom, "Avenue de la Republique");


    (*listeCase)[8].numeroPropriete = -1;
    strcpy((*listeCase)[8].nom, "Case prison");
    (*listeCase)[8].etat = 7;



    (*listeCase)[9].numeroPropriete = 4;
    strcpy((*listeCase)[9].nom, "Boulevard de la Villette");


    (*listeCase)[10].numeroPropriete = -1;
    strcpy((*listeCase)[10].nom, "Impot sur la fortune : Payez 100 euros");
    (*listeCase)[10].etat = 10;
    (*listeCase)[10].taxe = 100;



    (*listeCase)[11].numeroPropriete = 5;
    strcpy((*listeCase)[11].nom, "Rue de Paradis");


    (*listeCase)[12].numeroPropriete = -1;
    strcpy((*listeCase)[12].nom, "Raccourci : Avancez a la case 21");
    (*listeCase)[12].etat = 6;




    (*listeCase)[13].numeroPropriete = 6;
    strcpy((*listeCase)[13].nom, "Avenue Mozart");


    (*listeCase)[14].numeroPropriete = -1;
    strcpy((*listeCase)[14].nom, "Tirez une carte chance");
    (*listeCase)[14].etat = 3;



    (*listeCase)[15].numeroPropriete = 7;
    strcpy((*listeCase)[15].nom, "Place Pigalle");


    (*listeCase)[16].numeroPropriete = -1;
    strcpy((*listeCase)[16].nom, "Case stationnement gratuit");
    (*listeCase)[16].etat = 8;



    (*listeCase)[17].numeroPropriete = 8;
    strcpy((*listeCase)[17].nom, "Avenue Matignon");


    (*listeCase)[18].numeroPropriete = -1;
    strcpy((*listeCase)[18].nom, "Taxe sur les produits de luxe : Payez 200 euros");
    (*listeCase)[18].etat = 10;
    (*listeCase)[18].taxe = 200;


    (*listeCase)[19].numeroPropriete = 9;
    strcpy((*listeCase)[19].nom, "Avenue Henri-Martin");


    (*listeCase)[20].numeroPropriete = -1;
    strcpy((*listeCase)[20].nom, "Raccourci : Avancez a la case 29");
    (*listeCase)[20].etat = 6;



    (*listeCase)[21].numeroPropriete = 10;
    strcpy((*listeCase)[21].nom, "Faubourg Saint-Honore");


    (*listeCase)[22].numeroPropriete = -1;
    strcpy((*listeCase)[22].nom, "Tirez une carte communaute");
    (*listeCase)[22].etat = 4;



    (*listeCase)[23].numeroPropriete = 11;
    strcpy((*listeCase)[23].nom, "Rue la Fayette");


    (*listeCase)[24].numeroPropriete = -1;
    strcpy((*listeCase)[24].nom, "Allez en prison");
    (*listeCase)[24].etat = 9;



    (*listeCase)[25].numeroPropriete = 12;
    strcpy((*listeCase)[25].nom, "Avenue de Breteuil");


    (*listeCase)[26].numeroPropriete = -1;
    strcpy((*listeCase)[26].nom, "Vous trouvez 50 euros par terre");
    (*listeCase)[26].etat = 10;
    (*listeCase)[26].taxe = -50;



    (*listeCase)[27].numeroPropriete = 13;
    strcpy((*listeCase)[27].nom, "Boulevard des Capucines");


    (*listeCase)[28].numeroPropriete = -1;
    strcpy((*listeCase)[28].nom, "Raccourci : Avancez a la case 5 (Vous passez par la case depart et collectez 200 euros");
    (*listeCase)[28].etat = 6;



    (*listeCase)[29].numeroPropriete = 14;
    strcpy((*listeCase)[29].nom, "Avenue des Champs-Elysees");


    (*listeCase)[30].numeroPropriete = -1;
    strcpy((*listeCase)[30].nom, "Tirez une carte chance");
    (*listeCase)[30].etat = 3;



    (*listeCase)[31].numeroPropriete = 15;
    strcpy((*listeCase)[31].nom, "Rue de la Paix");


    for (int i = 0 ; i<32 ; i++)
    {
        realloc((*listeCase)[i].nom,(strlen((*listeCase)[i].nom)+1) * sizeof(char)); //reallocution a la bonne taille (pas de gachi)
    }

    return;
} //initialise les cases du plateau (allocution dynamique)


void initPropriete(propriete** listePropriete)
{
    (*listePropriete) = (propriete *) calloc(NOMBRE_PROPRIETE, sizeof(propriete));


    (*listePropriete)[0].numeroProprietaire = -1;
    (*listePropriete)[0].prixAchat = 60;
    (*listePropriete)[0].hypotheque = 30;
    (*listePropriete)[0].prixTerrainNu = 2;
    (*listePropriete)[0].prix1Maison = 10;
    (*listePropriete)[0].prix2Maison = 30;
    (*listePropriete)[0].prix3Maison = 90;
    (*listePropriete)[0].prix4Maison = 160;
    (*listePropriete)[0].prixHotel = 250;
    (*listePropriete)[0].prixAchatMaison = 50;
    (*listePropriete)[0].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[0].couleur = 1;
    (*listePropriete)[0].numeroCaseDesProprieteDeCetteCouleur[0] = 1;
    (*listePropriete)[0].numeroCaseDesProprieteDeCetteCouleur[1] = 3;


    (*listePropriete)[1].numeroProprietaire = -1;
    (*listePropriete)[1].prixAchat = 60;
    (*listePropriete)[1].hypotheque = 30;
    (*listePropriete)[1].prixTerrainNu = 4;
    (*listePropriete)[1].prix1Maison = 20;
    (*listePropriete)[1].prix2Maison = 60;
    (*listePropriete)[1].prix3Maison = 180;
    (*listePropriete)[1].prix4Maison = 320;
    (*listePropriete)[1].prixHotel = 450;
    (*listePropriete)[1].prixAchatMaison = 50;
    (*listePropriete)[1].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[1].couleur = 1;
    (*listePropriete)[1].numeroCaseDesProprieteDeCetteCouleur[0] = 1;
    (*listePropriete)[1].numeroCaseDesProprieteDeCetteCouleur[1] = 3;


    (*listePropriete)[2].numeroProprietaire = -1;
    (*listePropriete)[2].prixAchat = 100;
    (*listePropriete)[2].hypotheque = 50;
    (*listePropriete)[2].prixTerrainNu = 6;
    (*listePropriete)[2].prix1Maison = 30;
    (*listePropriete)[2].prix2Maison = 90;
    (*listePropriete)[2].prix3Maison = 270;
    (*listePropriete)[2].prix4Maison = 400;
    (*listePropriete)[2].prixHotel = 550;
    (*listePropriete)[2].prixAchatMaison = 50;
    (*listePropriete)[2].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[2].couleur = 2;
    (*listePropriete)[2].numeroCaseDesProprieteDeCetteCouleur[0] = 5;
    (*listePropriete)[2].numeroCaseDesProprieteDeCetteCouleur[1] = 7;


    (*listePropriete)[3].numeroProprietaire = -1;
    (*listePropriete)[3].prixAchat = 120;
    (*listePropriete)[3].hypotheque = 60;
    (*listePropriete)[3].prixTerrainNu = 8;
    (*listePropriete)[3].prix1Maison = 40;
    (*listePropriete)[3].prix2Maison = 100;
    (*listePropriete)[3].prix3Maison = 300;
    (*listePropriete)[3].prix4Maison = 450;
    (*listePropriete)[3].prixHotel = 600;
    (*listePropriete)[3].prixAchatMaison = 50;
    (*listePropriete)[3].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[3].couleur = 2;
    (*listePropriete)[3].numeroCaseDesProprieteDeCetteCouleur[0] = 5;
    (*listePropriete)[3].numeroCaseDesProprieteDeCetteCouleur[1] = 7;


    (*listePropriete)[4].numeroProprietaire = -1;
    (*listePropriete)[4].prixAchat = 140;
    (*listePropriete)[4].hypotheque = 70;
    (*listePropriete)[4].prixTerrainNu = 10;
    (*listePropriete)[4].prix1Maison = 50;
    (*listePropriete)[4].prix2Maison = 150;
    (*listePropriete)[4].prix3Maison = 450;
    (*listePropriete)[4].prix4Maison = 625;
    (*listePropriete)[4].prixHotel = 750;
    (*listePropriete)[4].prixAchatMaison = 100;
    (*listePropriete)[4].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[4].couleur = 3;
    (*listePropriete)[4].numeroCaseDesProprieteDeCetteCouleur[0] = 9;
    (*listePropriete)[4].numeroCaseDesProprieteDeCetteCouleur[1] = 11;


    (*listePropriete)[5].numeroProprietaire = -1;
    (*listePropriete)[5].prixAchat = 160;
    (*listePropriete)[5].hypotheque = 80;
    (*listePropriete)[5].prixTerrainNu = 12;
    (*listePropriete)[5].prix1Maison = 60;
    (*listePropriete)[5].prix2Maison = 180;
    (*listePropriete)[5].prix3Maison = 500;
    (*listePropriete)[5].prix4Maison = 700;
    (*listePropriete)[5].prixHotel = 900;
    (*listePropriete)[5].prixAchatMaison = 100;
    (*listePropriete)[5].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[5].couleur = 3;
    (*listePropriete)[5].numeroCaseDesProprieteDeCetteCouleur[0] = 9;
    (*listePropriete)[5].numeroCaseDesProprieteDeCetteCouleur[0] = 11;


    (*listePropriete)[6].numeroProprietaire = -1;
    (*listePropriete)[6].prixAchat = 180;
    (*listePropriete)[6].hypotheque = 90;
    (*listePropriete)[6].prixTerrainNu = 14;
    (*listePropriete)[6].prix1Maison = 70;
    (*listePropriete)[6].prix2Maison = 200;
    (*listePropriete)[6].prix3Maison = 550;
    (*listePropriete)[6].prix4Maison = 750;
    (*listePropriete)[6].prixHotel = 950;
    (*listePropriete)[6].prixAchatMaison = 100;
    (*listePropriete)[6].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[6].couleur = 4;
    (*listePropriete)[6].numeroCaseDesProprieteDeCetteCouleur[0] = 13;
    (*listePropriete)[6].numeroCaseDesProprieteDeCetteCouleur[1] = 15;


    (*listePropriete)[7].numeroProprietaire = -1;
    (*listePropriete)[7].prixAchat = 200;
    (*listePropriete)[7].hypotheque = 100;
    (*listePropriete)[7].prixTerrainNu = 16;
    (*listePropriete)[7].prix1Maison = 80;
    (*listePropriete)[7].prix2Maison = 220;
    (*listePropriete)[7].prix3Maison = 600;
    (*listePropriete)[7].prix4Maison = 800;
    (*listePropriete)[7].prixHotel = 1000;
    (*listePropriete)[7].prixAchatMaison = 100;
    (*listePropriete)[7].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[7].couleur = 4;
    (*listePropriete)[7].numeroCaseDesProprieteDeCetteCouleur[0] = 13;
    (*listePropriete)[7].numeroCaseDesProprieteDeCetteCouleur[1] = 15;


    (*listePropriete)[8].numeroProprietaire = -1;
    (*listePropriete)[8].prixAchat = 220;
    (*listePropriete)[8].hypotheque = 110;
    (*listePropriete)[8].prixTerrainNu = 18;
    (*listePropriete)[8].prix1Maison = 90;
    (*listePropriete)[8].prix2Maison = 250;
    (*listePropriete)[8].prix3Maison = 700;
    (*listePropriete)[8].prix4Maison = 875;
    (*listePropriete)[8].prixHotel = 1050;
    (*listePropriete)[8].prixAchatMaison = 150;
    (*listePropriete)[8].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[8].couleur = 5;
    (*listePropriete)[8].numeroCaseDesProprieteDeCetteCouleur[0] = 17;
    (*listePropriete)[8].numeroCaseDesProprieteDeCetteCouleur[0] = 19;


    (*listePropriete)[9].numeroProprietaire = -1;
    (*listePropriete)[9].prixAchat = 240;
    (*listePropriete)[9].hypotheque = 120;
    (*listePropriete)[9].prixTerrainNu = 20;
    (*listePropriete)[9].prix1Maison = 100;
    (*listePropriete)[9].prix2Maison = 300;
    (*listePropriete)[9].prix3Maison = 750;
    (*listePropriete)[9].prix4Maison = 925;
    (*listePropriete)[9].prixHotel = 1100;
    (*listePropriete)[9].prixAchatMaison = 150;
    (*listePropriete)[9].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[9].couleur = 5;
    (*listePropriete)[9].numeroCaseDesProprieteDeCetteCouleur[0] = 17;
    (*listePropriete)[9].numeroCaseDesProprieteDeCetteCouleur[0] = 19;


    (*listePropriete)[10].numeroProprietaire = -1;
    (*listePropriete)[10].prixAchat = 260;
    (*listePropriete)[10].hypotheque = 130;
    (*listePropriete)[10].prixTerrainNu = 22;
    (*listePropriete)[10].prix1Maison = 110;
    (*listePropriete)[10].prix2Maison = 330;
    (*listePropriete)[10].prix3Maison = 800;
    (*listePropriete)[10].prix4Maison = 975;
    (*listePropriete)[10].prixHotel = 1150;
    (*listePropriete)[10].prixAchatMaison = 150;
    (*listePropriete)[10].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[10].couleur = 6;
    (*listePropriete)[10].numeroCaseDesProprieteDeCetteCouleur[0] = 21;
    (*listePropriete)[10].numeroCaseDesProprieteDeCetteCouleur[1] = 23;


    (*listePropriete)[11].numeroProprietaire = -1;
    (*listePropriete)[11].prixAchat = 280;
    (*listePropriete)[11].hypotheque = 140;
    (*listePropriete)[11].prixTerrainNu = 24;
    (*listePropriete)[11].prix1Maison = 120;
    (*listePropriete)[11].prix2Maison = 360;
    (*listePropriete)[11].prix3Maison = 850;
    (*listePropriete)[11].prix4Maison = 1025;
    (*listePropriete)[11].prixHotel = 1200;
    (*listePropriete)[11].prixAchatMaison = 150;
    (*listePropriete)[11].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[11].couleur = 6;
    (*listePropriete)[11].numeroCaseDesProprieteDeCetteCouleur[0] = 21;
    (*listePropriete)[11].numeroCaseDesProprieteDeCetteCouleur[0] = 23;


    (*listePropriete)[12].numeroProprietaire = -1;
    (*listePropriete)[12].prixAchat = 300;
    (*listePropriete)[12].hypotheque = 150;
    (*listePropriete)[12].prixTerrainNu = 26;
    (*listePropriete)[12].prix1Maison = 130;
    (*listePropriete)[12].prix2Maison = 390;
    (*listePropriete)[12].prix3Maison = 900;
    (*listePropriete)[12].prix4Maison = 1100;
    (*listePropriete)[12].prixHotel = 1275;
    (*listePropriete)[12].prixAchatMaison = 200;
    (*listePropriete)[12].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[12].couleur = 7;
    (*listePropriete)[12].numeroCaseDesProprieteDeCetteCouleur[0] = 25;
    (*listePropriete)[12].numeroCaseDesProprieteDeCetteCouleur[1] = 27;


    (*listePropriete)[13].numeroProprietaire = -1;
    (*listePropriete)[13].prixAchat = 320;
    (*listePropriete)[13].hypotheque = 160;
    (*listePropriete)[13].prixTerrainNu = 28;
    (*listePropriete)[13].prix1Maison = 150;
    (*listePropriete)[13].prix2Maison = 450;
    (*listePropriete)[13].prix3Maison = 1000;
    (*listePropriete)[13].prix4Maison = 1200;
    (*listePropriete)[13].prixHotel = 1400;
    (*listePropriete)[13].prixAchatMaison = 200;
    (*listePropriete)[13].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[13].couleur = 7;
    (*listePropriete)[13].numeroCaseDesProprieteDeCetteCouleur[0] = 25;
    (*listePropriete)[13].numeroCaseDesProprieteDeCetteCouleur[1] = 27;


    (*listePropriete)[14].numeroProprietaire = -1;
    (*listePropriete)[14].prixAchat = 350;
    (*listePropriete)[14].hypotheque = 175;
    (*listePropriete)[14].prixTerrainNu = 35;
    (*listePropriete)[14].prix1Maison = 175;
    (*listePropriete)[14].prix2Maison = 500;
    (*listePropriete)[14].prix3Maison = 1100;
    (*listePropriete)[14].prix4Maison = 1300;
    (*listePropriete)[14].prixHotel = 1500;
    (*listePropriete)[14].prixAchatMaison = 200;
    (*listePropriete)[14].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[14].couleur = 8;
    (*listePropriete)[14].numeroCaseDesProprieteDeCetteCouleur[0] = 29;
    (*listePropriete)[14].numeroCaseDesProprieteDeCetteCouleur[1] = 31;


    (*listePropriete)[15].numeroProprietaire = -1;
    (*listePropriete)[15].prixAchat = 400;
    (*listePropriete)[15].hypotheque = 200;
    (*listePropriete)[15].prixTerrainNu = 50;
    (*listePropriete)[15].prix1Maison = 200;
    (*listePropriete)[15].prix2Maison = 600;
    (*listePropriete)[15].prix3Maison = 1400;
    (*listePropriete)[15].prix4Maison = 1700;
    (*listePropriete)[15].prixHotel = 2000;
    (*listePropriete)[15].prixAchatMaison = 200;
    (*listePropriete)[15].nombreProprieteDeCetteCouleur = 2;
    (*listePropriete)[15].couleur = 8;
    (*listePropriete)[15].numeroCaseDesProprieteDeCetteCouleur[0] = 29;
    (*listePropriete)[15].numeroCaseDesProprieteDeCetteCouleur[0] = 31;


    return;
} //initialise toutes les proprietes du plateau


void libererListeCase(cases* listeCase)
{
    if (listeCase != NULL)
    {
        for (int i = 0 ; i < NOMBRE_CASE ; i++)
        {
            if (listeCase[i].nom != NULL)
            {
                free(listeCase[i].nom);
            }

        }
        free(listeCase);
    }
    return;
} //libere toutes les donnes des cases

void libererListePropriete(propriete* listePropriete)
{
    if (listePropriete != NULL)
    {
        free(listePropriete);
    }
    return;
} //libere toutes les donnees des proprietes
