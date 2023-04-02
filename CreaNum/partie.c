//

//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions.h"
#include "affichage.h"
#include "partie.h"
#include "structures.h"
#include "chanceEtCaisse.h"
#include "initProprietes.h"

#define MAX_CARAC_NOM_JOUEUR 53
#define ARGENT_AU_DEPART 1500
#define NOMBRE_CARTE_CHANCE 10
#define NOMBRE_CARTE_COMMUNAUTE 10
#define MAX_CARAC_CARTE 200
#define MAX_MAISONS 32
#define MAX_HOTELS 12

//fonction qui initialise toutes les donnees d'une partie a NULL
void initDataPartie(dataPartie* partie)
{
    partie->listePropriete = NULL;
    partie->listeCase = NULL;
    partie->listeChaineCarteCommunaute = NULL;
    partie->listeChaineCarteChance = NULL;
    partie->listeJoueur = NULL;
    partie->donnesDeLaPartie.nombreMaison = 0;
    partie->donnesDeLaPartie.nombreHotel = 0;
    partie->donnesDeLaPartie.nombreJoueur = 0;
    partie->donnesDeLaPartie.nombreJoueurLogique = 0;
}



//fonction qui crée une partie / elle initialise les cases, cartes, joueurs...
dataPartie creePartie()
{
    /**************************************************************************
     *                            CHEAT MODE                                   *
     * ************************************************************************/

    donnees donneesDeLaPartie;
    printf("Voulez vous activez le cheat mode\n1/ Oui\n2/ Non\n");
    donneesDeLaPartie.cheatMode = saisirEntier();




    /**************************************************************************
     * ALLOCUTION LISTE DE CARTES CHANCES ET COMMUNAUTE ET MELANGE DES CARTES *
     * ************************************************************************/

    listeChaineCarte* listeChaineCarteChance = NULL;
    listeChaineCarte* listeChaineCarteCommunaute = NULL;


    char** listeCarteChance = (char**) calloc(NOMBRE_CARTE_CHANCE, sizeof(char*));
    for (int i = 0 ; i<NOMBRE_CARTE_CHANCE ; i++)
    {
        listeCarteChance[i] = (char*) calloc(MAX_CARAC_CARTE, sizeof(char));
    }

    char** listeCarteCommunaute = (char**) calloc(NOMBRE_CARTE_COMMUNAUTE, sizeof(char*));
    for (int i = 0 ; i<NOMBRE_CARTE_COMMUNAUTE ; i++)
    {
        listeCarteCommunaute[i] = (char*) calloc(MAX_CARAC_CARTE, sizeof(char));
    }


    melangeCartes(listeCarteChance, listeCarteCommunaute);


    for (int i = 0 ; i<NOMBRE_CARTE_CHANCE ; i++)
    {
        listeCarteChance[i] = realloc(listeCarteChance[i], (strlen(listeCarteChance[i])+1)*sizeof(char));
    }
    for (int i = 0 ; i<NOMBRE_CARTE_COMMUNAUTE ; i++)
    {
        listeCarteCommunaute[i] = realloc(listeCarteCommunaute[i], (strlen(listeCarteCommunaute[i])+1)*sizeof(char));
    }

    listeChaineCarteChance = creationListeChaineChance(listeCarteChance);
    listeChaineCarteCommunaute = creationListeChaineCommunaute(listeCarteCommunaute);
    libererListeCarte(listeCarteChance, listeCarteCommunaute);





    /**************************************************************************
     * ALLOCUTION LISTE DE PROPRIETES ET INITIALISATION DE LEUR DONNEES       *
     * ************************************************************************/

    cases* listeCase;
    propriete* listePropriete;

    initCases(&listeCase);
    initPropriete(&listePropriete);







    /**************************************************************************
     *             INITIALISATION DES DONNES DE LA PARTIE                     *
     * ************************************************************************/

    printf("Saisissez le nombre de joueurs (entre 2 et 8) :\n");
    while (donneesDeLaPartie.nombreJoueur<2 || donneesDeLaPartie.nombreJoueur>8)
    {
        donneesDeLaPartie.nombreJoueur = saisirEntier();

        if (donneesDeLaPartie.nombreJoueur<2 || donneesDeLaPartie.nombreJoueur>8)
        {
            saisitInvalide();
        }
    }
    donneesDeLaPartie.nombreHotel = MAX_HOTELS;
    donneesDeLaPartie.nombreMaison = MAX_MAISONS;
    donneesDeLaPartie.nombreJoueurLogique = donneesDeLaPartie.nombreJoueur;





    /**************************************************************************
     *      ALLOCUTION LISTE DE JOUEURS ET INITIALISATION DE LEUR DONNEE      *
     * ************************************************************************/

    char memoireNom[MAX_CARAC_NOM_JOUEUR];
    joueur* listeJoueur = NULL;


    listeJoueur = (joueur*) calloc(donneesDeLaPartie.nombreJoueur+1, sizeof(joueur));  //ya un bug qui fait que le nom du dernier joueur est change du coup j'ai crée un bot

    for (int i=0 ; i<donneesDeLaPartie.nombreJoueur ; i++)
    {
        printf("Saisissez le nom du %d joueur (50 caracteres max et n'accepte pas les accents):\n", i+1);
        saisirCarac(memoireNom, MAX_CARAC_NOM_JOUEUR);
        listeJoueur[i].nom = (char*) calloc(strlen(memoireNom), sizeof(char));
        for (int j=0 ; j<strlen(memoireNom) ; j++)
        {
            listeJoueur[i].nom[j] = memoireNom[j];
        }
        listeJoueur[i].argent = ARGENT_AU_DEPART;
        listeJoueur[i].position = 0;
        listeJoueur[i].etat = 4;
        listeJoueur[i].carteSortiePrisonChance=0;
        listeJoueur[i].carteSortiePrisonCommunaute=0;

    }



    listeJoueur[donneesDeLaPartie.nombreJoueur].nom = (char*) calloc(1, sizeof(char)); //le nom du bot qui sera changé sans raison, permet d'eviter que ca soit le nom d'un joueur qui soit perdu
    listeJoueur[donneesDeLaPartie.nombreJoueur].nom[0]='b';
    listeJoueur[donneesDeLaPartie.nombreJoueur].etat = -1;



    /**************************************************************************
     *                       LANCEMENT DE LA PARTIE                           *
     * ************************************************************************/

    dataPartie dataPartie1;
    initDataPartie(&dataPartie1);
    dataPartie1.donnesDeLaPartie = donneesDeLaPartie;
    dataPartie1.listePropriete = listePropriete;
    dataPartie1.listeCase = listeCase;
    dataPartie1.listeChaineCarteChance = listeChaineCarteChance;
    dataPartie1.listeChaineCarteCommunaute = listeChaineCarteCommunaute;
    dataPartie1.listeJoueur = listeJoueur;
    dataPartie1.aQuiDeJouer = rand() % donneesDeLaPartie.nombreJoueur;

    dataPartie1 = bouclePartie(&dataPartie1);
    return (dataPartie1);
}








//Fonction qui realise une boucle tant qu'il y a des joueurs en lice et tant que les joueurs souhaitent continuer de jouer
//dans cette fonction il y a une boucle for representant le tour d'un joueur
dataPartie bouclePartie(dataPartie* partie)
{
    int choixJoueur = 1,           //valeur choisit par le joueur pour naviguer dans le menu
       boolDouble = 0,             //booleen : 1 si le joueur a fait un double, 0 s'il n'en a pas fait
       payeOuAchatOuChanceOuCommu = 0, // Le joueur est tombe sur une case ou il doit : 0 = rien faire de special / 1 = paye un proprio / 2 = peut acheter une propriete / 3 = doit tirer une carte chance / 4 = doit tirer une carte communaute / 5 = payer une taxe ou recevoir un bonus (il est tombe sur une case taxe)
       boolSauvegarde=0,               //booleen : 1 si les joueurs veulent sauvegarder, 0 si non
       compteurDoubleDaffile =0,       //permet de compter le nombre de double d'affilee. S'il atteint 1 alors le joueur a fait deux doubles et le prochain l'emmene direct en prison
       estCeQuilAPaye = 0,             //booleen : 1 si le joueur a fait la premiere action du menu (paye/tirerune carte...) ce qui lui permet de rejouer ou de mettre fin a son tour, 0 sinon
       finDeTour = 0,                  //booleen : 1 si le joueur a ete envoye en prison (l'empechant de rejouer s'il avais fait un double), 0 sinon
       numeroJoueur = partie->aQuiDeJouer; //valeur correspondant au numero du joueur qui commence (ou celui qui devait jouer avant de sauvegarder)


    printf("C'est %s qui commence !\n", partie->listeJoueur[partie->aQuiDeJouer].nom);


    // boucle tant qu'il ya des joueurs ou que les jours ne souhaite pas arreter
    while (partie->donnesDeLaPartie.nombreJoueurLogique>1 && choixJoueur != 100)
    {

        // boucle pour faire jouer les joueurs les uns apres les autres
        for (numeroJoueur ; numeroJoueur < partie->donnesDeLaPartie.nombreJoueur ; numeroJoueur++)
        {

            // verifie si le joueur est mort ou si les joueurs souhaite arreter
            if (partie->listeJoueur[numeroJoueur].etat == -1 || choixJoueur == 100) {}


            //Tour d'un joueur (si le joueur n'est pas mort et que tout le monde souhaite continuer)
            else
            {
                     /**************************************************************************
                     *               Premiere partie du tour du joueur                         *
                     * ************************************************************************/
                finDeTour = 0;
                do //affiche le menu du joueur
                {
                    affichagePlateau(*partie);
                    printf("C'est a %s de jouer \n", partie->listeJoueur[numeroJoueur].nom);
                    afficherMenuJoueurDebut();
                    choixJoueur = saisirEntier();
                    switch (choixJoueur)
                    {
                        case 1 : //le joueur lance les des
                            boolDouble = tourDuJoueur(partie, numeroJoueur, compteurDoubleDaffile, &finDeTour);
                            break;

                        case 2 : //le joueur souhaite acheter des maisons
                            achatMaison(partie, numeroJoueur);
                            break;

                        case 3 : //le joueur souhaite marchander avec qql d'autre
                            marchandage(partie, numeroJoueur);
                            affichagePlateau(*partie);
                            break;

                        case 4 : //le joueur souhaite hypothequer ou lever une hypotheque ou vendre des maisons/hotels
                            hypotheque(partie, numeroJoueur);
                            break;

                        case 5 : //le joueur souhaite suspendre la partie

                            break;

                        case 6 : //le joueur souhaite abandonner
                            abandon(partie, numeroJoueur);
                            if(partie->listeJoueur[numeroJoueur].etat != -1){choixJoueur = 0;}
                            break;

                        default : //la saisit du choix du joueur dans le menu ne correspond a aucune valeur propose // on ne reaffiche pas le menu car le joueur a juste a srcoll up et car c'est plus beau
                            saisitInvalide();
                            break;
                    }
                }while(choixJoueur!= 5 && choixJoueur!=1 && choixJoueur != 6); //affiche le menu tant que le joueur a pas lancer les dés ou decider de suspendre la partie ou abandonner






                if (choixJoueur==5) //si les joueurs souhaite arreter
                {
                    partie->aQuiDeJouer = numeroJoueur; //on retient le numero du joueur a qui c'etait le tour pour la prochaine fois
                    numeroJoueur = partie->donnesDeLaPartie.nombreJoueur;//on se fait se terminer la boucle for en faisant comme si c'etait le dernier joueur qui jouait
                    choixJoueur = 100; // 100 = les joueurs souhaite suspendre la partie
                }



                estCeQuilAPaye = 0;
                // tant que le joueur n'a pas mis fin a son tour // on ne rentre pas dans la boucle si les joueurs voullaient suspendre la partie, si le joueur a abandonner
                while(choixJoueur!= 5 && choixJoueur != 100 && choixJoueur != 6)
                {

                    //si fin de tour vaut 1, le joueur n'a plus le droit de relancer les dés meme s'il avait fait un double
                    if (finDeTour == 1)
                    {
                        boolDouble = 0;
                    }

                    printf("C'est a %s de jouer \n", partie->listeJoueur[numeroJoueur].nom);






                    /**************************************************************************
                     *                Affichage menu apres avoir lancer les dés               *
                     * ************************************************************************/

                    //affichage menu si le joueur tombe sur une propriete en vente
                    if (partie->listeCase[partie->listeJoueur[numeroJoueur].position].etat == 0 )
                    {
                        afficherMenuJoueurFinAchat();
                        payeOuAchatOuChanceOuCommu = 2; //2eme mot de la variale = achat, sert par la suit a effectuer les bonnes fonctions s'il saisit 1
                        estCeQuilAPaye = 1; //le joueur peut mettre fin a son tour s'il le souhaite
                    }


                    //affichage menu si le joueur tombe sur case chance ou communaute
                    else if (estCeQuilAPaye == 0 && (partie->listeCase[partie->listeJoueur[numeroJoueur].position].etat == 3 || partie->listeCase[partie->listeJoueur[numeroJoueur].position].etat == 4))
                    {
                        afficherMenuJoueurFinCarte();
                        payeOuAchatOuChanceOuCommu = partie->listeCase[partie->listeJoueur[numeroJoueur].position].etat;
                    }


                    //affichage menu si le joueur tombe sur une propriete appartenant a qql d'autre que lui
                    else if ( partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].numeroProprietaire != numeroJoueur && estCeQuilAPaye==0 && (partie->listeCase[partie->listeJoueur[numeroJoueur].position].etat == 1 ) && partie->listeJoueur[partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].numeroProprietaire].etat != 0)
                    {
                        afficherMenuJoueurFinPaye();
                        payeOuAchatOuChanceOuCommu = 1;
                    }


                    //affichage menu si le joueur tombe sur une case taxe ou bonus
                    else if (estCeQuilAPaye == 0 && partie->listeCase[partie->listeJoueur[numeroJoueur].position].etat == 10)
                    {
                        afficherMenuJoueurFinTaxe();
                        payeOuAchatOuChanceOuCommu = 5;
                    }


                    //affichage menu si le joueur tombe sur sans specificiter (pas besoin de payer, tirer une carte ou autre)
                    else
                    {
                        afficherMenuJoueurFinRien();
                        payeOuAchatOuChanceOuCommu = 0;
                        estCeQuilAPaye = 1;
                    }



                    //Le joueur choisit ce qu'il veut faire
                    choixJoueur = saisirEntier();


                    /**************************************************************************
                     *                Deuxieme partie du tour du joueur                       *
                     * ************************************************************************/
                    switch (choixJoueur)
                    {
                        case 1 : //Le joueur realise l'action de sa case : payer le proprio / tirer une carte ou autre
                            if (payeOuAchatOuChanceOuCommu==2)
                            {
                                achat(partie, numeroJoueur, partie->listeJoueur[numeroJoueur].position);
                                estCeQuilAPaye = 1;
                            } //Le joueur achete la propriete sur laquele il se trouve
                            else if (payeOuAchatOuChanceOuCommu==1)
                            {

                                //nombre de construction sur le terrain où est le joueur (maisons+hotel)
                                switch(partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].nombreMaison +partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].nombreHotel)
                                {
                                    case 0 : //la propriete a pas de construction
                                        if ( partie->listePropriete[partie->listeCase[partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].numeroProprietaire == partie->listePropriete[partie->listeCase[partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].numeroProprietaire)
                                        {
                                            //le proprio possede toutes les proprietes de ce groupe, le loyer sur terrain nu est donc doublé
                                            estCeQuilAPaye = paye(partie, numeroJoueur, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].numeroProprietaire, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prixTerrainNu * 2);
                                        }
                                        else //la propriete est nu et le proprio a pas tous les terrain de ce groupe
                                        {
                                            estCeQuilAPaye = paye(partie, numeroJoueur, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].numeroProprietaire, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prixTerrainNu);
                                        }
                                        break;

                                    case 1 : //la propriete a 1 maison
                                        estCeQuilAPaye = paye(partie, numeroJoueur, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].numeroProprietaire, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prix1Maison);
                                        break;

                                    case 2 : //la propriete a 2 maisons
                                        estCeQuilAPaye = paye(partie, numeroJoueur, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].numeroProprietaire, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prix2Maison);
                                        break;

                                    case 3 : //la propriete a 3 maisons
                                        estCeQuilAPaye = paye(partie, numeroJoueur, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].numeroProprietaire, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prix3Maison);
                                        break;

                                    case 4 : //la propriete a 4 maisons
                                        estCeQuilAPaye = paye(partie, numeroJoueur, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].numeroProprietaire, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prix4Maison);
                                        break;

                                    case 5 : //la proprietes a 5 maisons
                                        estCeQuilAPaye = paye(partie, numeroJoueur, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].numeroProprietaire, partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prixHotel);
                                        break;
                                    default : //le nombre de batiments construit n'est pas reglementé
                                        printf("ERROR : nombre de batiments construit sur %s invalide\n", partie->listeCase[partie->listeJoueur[numeroJoueur].position].nom);
                                        break;
                                }
                            }//Le joueur paye le proprietaire chez qui il est tombe
                            else if (payeOuAchatOuChanceOuCommu == 3)
                            {
                                realisationCarteChance(partie, numeroJoueur, &estCeQuilAPaye,&finDeTour);
                                if (estCeQuilAPaye == 1 || estCeQuilAPaye == 2)//permet d'eviter de mettre plusieurs carte en dessous du paquet, si le joueur a tente de realiser la carte mais n'avait pas les sous en liquide
                                {
                                    partie->listeChaineCarteChance = partie->listeChaineCarteChance->next; //on place la carte en dessous du paquet si la carte a bien été realise
                                }

                            }//Le joueur tire une carte chance
                            else if (payeOuAchatOuChanceOuCommu == 4)
                            {

                                realisationCarteCommunaute(partie, numeroJoueur, &estCeQuilAPaye, &finDeTour);
                                printf("ICI : %d", estCeQuilAPaye);
                                if (estCeQuilAPaye == 1)//permet d'eviter de mettre plusieurs carte en dessous du paquet, si le joueur a tente de realiser la carte mais n'avait pas les sous en liquide
                                {
                                    partie->listeChaineCarteCommunaute = partie->listeChaineCarteCommunaute->next;//on place la carte en dessous du paquet si la carte a bien été realise
                                }

                            }//Le joueur tire une carte caisse de communaute
                            else if (payeOuAchatOuChanceOuCommu == 5)
                            {

                                realisationCaseTaxe(partie, numeroJoueur, &estCeQuilAPaye);
                                affichagePlateau(*partie);
                            }//Le joueur paye la taxe ou recoit le bonus de sa case
                            break;

                        case 2 : //Le joueur souhaite acheter des maisons
                            achatMaison(partie, numeroJoueur);

                            break;

                        case 3 : //le joeur souhaite marchander avec qql d'autre
                            marchandage(partie, numeroJoueur);
                            affichagePlateau(*partie);
                            break;

                        case 4 : //le joueur souhaite hyppotheque ou ever une hypotheque ou vendre des maisons
                            hypotheque(partie, numeroJoueur);
                            break;

                        case 5 :
                            if (estCeQuilAPaye == 0) //si le joueur n'a pas effectuer l'action de sa case, il n epeut pas mettre fin a son tour ou rejouez
                            {
                                choixJoueur = 0;
                            }
                            else
                            {
                                if (boolDouble==1 ) //le joueur a fait un double
                                {
                                    boolDouble = tourDuJoueur(partie, numeroJoueur, compteurDoubleDaffile, &finDeTour);
                                    estCeQuilAPaye = 0;
                                    choixJoueur=0;
                                    compteurDoubleDaffile++;
                                }
                                else //le joueur a finit son tour
                                {
                                    printf("Le tour de %s est termine !\n", partie->listeJoueur[numeroJoueur].nom);
                                    compteurDoubleDaffile = 0;
                                }
                            }
                            break;

                        case 6 : //le joueur souhaite abandonner
                            abandon(partie, numeroJoueur);
                            if(partie->listeJoueur[numeroJoueur].etat != -1){choixJoueur = 0;}
                            break;

                        default : //la saisit du choix du joueur dans le menu ne correspond a aucune valeur propose // on ne reaffiche pas le menu car le joueur a juste a srcoll up et car c'est plus beau
                            saisitInvalide();
                            break;
                    }
                }

                if (partie->donnesDeLaPartie.nombreJoueurLogique==1) // ya plus qu'un joueur !
                {
                    numeroJoueur = partie->donnesDeLaPartie.nombreJoueur;
                    choixJoueur = 100;
                }

            }
        }
        numeroJoueur = 0;
    }


    if (partie->donnesDeLaPartie.nombreJoueurLogique == 1) //Verifie si la partie s'est arreter psq il y a un gagnant
    {
        printf("C'est finit !\n");
        for (numeroJoueur = 0 ; numeroJoueur < partie->donnesDeLaPartie.nombreJoueur ; numeroJoueur++) //affiche le gagnant
        {
            if (partie->listeJoueur[numeroJoueur].etat != -1){printf("Felicitation a %s pour cette victoire ecrasante !", partie->listeJoueur[numeroJoueur].nom);}
        }
        libererTout(partie);
        initDataPartie(partie); //renitiallise toutes les données a 0, les joeurs peuevnt relancer directement une partie
        return(*partie);
    }
    else //Il n'y a pas de gagnant, donc les joueurs ont suspendu la partie. On leur demande s'ils veulent sauvegarder (il peuevnt egalement sauvegarder dans le menu)
    {
        printf("Voulez-vous sauvegardez cette partie pour la reprendre plus tard ?\n"
               "1/ Oui\n"
               "2/ Non\n");
        boolSauvegarde = saisirEntier();
        if (boolSauvegarde == 1)
        {
            sauvegardeToiDansUnFichierBinaire(partie); //les joueurs veulent sauvegarder
        }
        return(*partie);
    }
}



//fonction qui libere toutes les donnees d'une partie (tout les tableaux dynamiques)
void libererTout(dataPartie* partie)
{
    libererListeCase(partie->listeCase);
    libererListePropriete(partie->listePropriete);
    libererListeChaineCarte(partie->listeChaineCarteChance, partie->listeChaineCarteCommunaute);
}












//j'ai corrige le bug avec la carte chance allez a la propriete :...
//la carte est bien remise en dessous du paquet
//j'ai corrige le cheat mode off






//diviser le code en ptite fonction
//commentter le code
//securiser le jeu (si qql tape un truc invalide, ca redemande)





                        //Peut etre fait apres le projet
//GENERALISATION (couleur de 2 ou 3 propriete / compagnie eau et electricite...) faire le vrai monopoly
//interface graphique



//pour les cartes chances et commu j'ai du mettre un char** (dans la structure du maillon) pour que ca marche mais je comrend pas trop pk
//et j'ai oublie de allouer une case de plus pour le \0, les deux erreurs m'ont fait perdre 2h


//on ne paut pas etre 6 ou plus sur une case (ca decale toute le plateau)
// amelioration : liste de joueur : faire une liste chainé pour prendre moins de memoire lorsque un joueur meurt plutot que de stocker des 0 inutiles
//on doit quand meme stocker des donnes pour un eventuel palmares

//new mode de jeu

//pas de faillite si le joueur vend une potentielle carte sortie de prison ou un terrain a un autre joueur
// on part du principe qu'il ne peut pas marchander tant qu'il a pas payer ! potentielle amelioration
//si bob faillite sur le terrain de toto mais que toto a pas les moyen de racheter les terrain hypothequer / autorisation vente maison, marchandage ? / faillite ? / propriete revient a la banque ? /