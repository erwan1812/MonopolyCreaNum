//
// Created by morga on 20/11/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "structures.h"
#include "affichage.h"

#define NOMBRE_CASES_PLATEAU 32
#define PRIX_SORTIT_PRISON 50
#define NOMBRE_CASES_ENTRE_GARE 8
#define NOMBRE_PROPRIETE 16
#define SALAIRE_PAR_TOUR 200

void flush()
{
    int carac = 0;
    while (carac != '\n' && carac != EOF)
    {
        carac = getchar();
    }
} //permet de vider le buffer


int saisirCarac (char *phrase, int taille)
{
    char *positionEntree = NULL;
    if (fgets(phrase, taille, stdin) != NULL)
    {
        positionEntree = strchr(phrase, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            flush();
        }
        return(1);
    }
    else
    {
        flush();
        return(0);
    }
} //saisit de mots de manieres securisé


int saisirEntier()
{
    char nombre[20] = {0};

    if(saisirCarac(nombre, 20))
    {
        return(strtol(nombre, NULL, 10));
    }
    else
    {
        return (0);
    }
} //saisit de nombre de manieres securisé


int lancerDe(dataPartie* partie)
{
    if (partie->donnesDeLaPartie.cheatMode != 1)
    {
        return( rand() % 6 + 1 );
    }
    else
    {
        printf("Tu veux faire combien ?\n");
        return(saisirEntier());
    }
} //genere un chiffre entre 1 et 6 ou demande a l'utilisateur un chiffre si le cheat mode est actif








int tourDuJoueur(dataPartie* partie, int numeroJoueur, int compteurDoubleDaffile, int* finDeTour)  // le joueur veut avancer // renvoit un booleen de s'il a fait un double ou non
{
    int valeurDe1 = 0, valeurDe2 = 0, boolPrison = 0, choixPrison = 0, aPaye = 0, utilisationCarte = 0;
    char flushh[10];

    boolPrison = ( (partie->listeJoueur[numeroJoueur].etat >= 1) && (partie->listeJoueur[numeroJoueur].etat <=3) );


    if ( boolPrison == 1) // joueur en prison
    {
        if(partie->listeJoueur[numeroJoueur].carteSortiePrisonCommunaute > 0)
        {
            printf("Veux tu utiliser ta carte communaute sortie de prison ?\n1/ Oui\n2/ Non\n");
            utilisationCarte = saisirEntier();
            if (utilisationCarte == 1)
            {
                boolPrison = 0;
                partie->listeJoueur[numeroJoueur].carteSortiePrisonCommunaute -= 1;
                remiseCarteSortiePrison(partie, 2);
                printf("Vous n'etes plus en prison\nAppuyer sur entree pour lancer les des\n");
                saisirCarac(flushh, 10);
                valeurDe1 = lancerDe(partie);
                valeurDe2 = lancerDe(partie);
                aPaye = 1;
            }
        } //demande l'utilisation de la crate sortie d eprison (communaute)
        if (partie->listeJoueur[numeroJoueur].carteSortiePrisonChance > 0)
        {
            printf("Veux tu utiliser ta carte chance sortie de prison ?\n1/ Oui\n2/ Non\n");
            utilisationCarte = saisirEntier();
            if (utilisationCarte == 1)
            {
                boolPrison = 0;
                partie->listeJoueur[numeroJoueur].carteSortiePrisonChance -= 1;
                remiseCarteSortiePrison(partie, 1);
                printf("Vous n'etes plus en prison\nAppuyer sur entree pour lancer les des\n");
                saisirCarac(flushh, 10);
                valeurDe1 = lancerDe(partie);
                valeurDe2 = lancerDe(partie);
                aPaye = 1;
            }
        } //demande l'utilisation de la crate sortie de prison (chance)
        if (boolPrison == 1)
        {
            printf("Vous etes en prison !\n"
                   "Voulez-vous payer %d euro pour sortir de prison (saisissez 1)\nOu bien essayer de faire un double (saisissez 2)\n", PRIX_SORTIT_PRISON);
            choixPrison = saisirEntier();
            if (choixPrison == 1) //joueur paye pour sortir de prison
            {
                while (aPaye == 0)
                {
                    printf("Que veux tu faire :\n"
                           "1/ Payer les %d euros a pour sortir de prison\n"
                           "2/ Vendre des maisons  ou hypotheque\n"
                           "3/ Marchander\n", PRIX_SORTIT_PRISON);

                    menuAvantPaye(partie, numeroJoueur, -1, &aPaye);
                }
                partie->listeJoueur[numeroJoueur].argent -= PRIX_SORTIT_PRISON;
                boolPrison = 0;
                printf("Vous n'etes plus en prison\nAppuyer sur entree pour lancer les des\n");
                saisirCarac(flushh, 10);
                valeurDe1 = lancerDe(partie);
                valeurDe2 = lancerDe(partie);
            }
            else // joueur tente le double pour sortir de prison
            {
                printf("Appuyer sur entree pour lancer les des\n");
                saisirCarac(flushh, 10);
                valeurDe1 = lancerDe(partie);
                valeurDe2 = lancerDe(partie);


                if (valeurDe1 != valeurDe2){printf("Vous avez obtenu %d et %d soit %d. \nCe n'est pas un double\n", valeurDe1, valeurDe2, valeurDe1 + valeurDe2);}
                boolPrison = valeurDe1==valeurDe2 ? 0 : 1;
            }

            if (partie->listeJoueur[numeroJoueur].etat == 3 && boolPrison==1) // joueur a pas payer et pas reussis le double, et c'etait son 3eme tour en prison, il doit don cpayer et avancera de son jet
            {
                while (aPaye == 0)
                {
                    printf("Que veux tu faire :\n"
                           "1/ Payer les %d euros a pour sortir de prison\n"
                           "2/ Vendre des maisons  ou hypotheque\n"
                           "3/ Marchander\n", PRIX_SORTIT_PRISON);

                    menuAvantPaye(partie, numeroJoueur, -1, &aPaye);
                }
                partie->listeJoueur[numeroJoueur].argent -= PRIX_SORTIT_PRISON;
                boolPrison=0;
                aPaye =0;  //il a tente le double et n'as pas reussis donc ca ne change rien fait
            }
        }




        if (boolPrison == 0) // joueur est plus en prison
        {

            partie->listeJoueur[numeroJoueur].etat = 4;

            deplacementJoueur(partie, numeroJoueur, valeurDe1, valeurDe2, NULL); //on peut se permettre de mettre NULL car popur retourner en prson instantanement il faut faire 16 ce qui est impossible

            if (aPaye == 1) //si il a paye, il peut rejouer s'il fait un double
            {
                return(valeurDe1 == valeurDe2);
            }
            return(0);//un joueur n'ayant pas paye et faisant un double, ne rejoue pas d'apres les regles
        }

        else  // joueur est toujours en prison
        {
            printf("Vous restez en prison (c'etait votre %d tour en prison)\n", partie->listeJoueur[numeroJoueur].etat++);
            return(0);
        }

    }
    else // joueur pas en prison
    {
        printf("Appuyer sur entree pour lancer les des\n");
        saisirCarac(flushh, 10);
        valeurDe1 = lancerDe(partie);
        valeurDe2 = lancerDe(partie);

        if ( compteurDoubleDaffile == 1 && valeurDe1 == valeurDe2)
        {
            prison(partie->listeJoueur, numeroJoueur);
            affichagePlateau(*partie);
            printf("Vous vous faites arreter pour exces de vitesse de plus de 50 km/h\nVous passez 24h de garde a vue\n");
            return(0);
        }
        else
        {
            deplacementJoueur(partie, numeroJoueur, valeurDe1, valeurDe2, finDeTour);
            return(valeurDe1 == valeurDe2);
        }



        //verifier case et proposer acheter ou payer et si pas assez pour payer proposer hypothequer et si pas assez meme avec hypot => eliminer joueur(realloc listejoueur ou verifier au debut du tour si en vie) et repartir proprietes


    }
}



void deplacementJoueur (dataPartie* partie, int numeroJoueur, int valeurDe1, int valeurDe2, int* finDeTour)
{
    unsigned int memoirePosition = 0;

    memoirePosition = partie->listeJoueur[numeroJoueur].position;

    if (partie->listeCase == NULL){printf("mauvaise initialisation des cases\n");}
    if (partie->listeJoueur[numeroJoueur].position > (partie->listeJoueur[numeroJoueur].position + valeurDe1+valeurDe2) % NOMBRE_CASES_PLATEAU){partie->listeJoueur[numeroJoueur].argent += SALAIRE_PAR_TOUR;}
    partie->listeJoueur[numeroJoueur].position = (partie->listeJoueur[numeroJoueur].position + valeurDe1+valeurDe2) % NOMBRE_CASES_PLATEAU;
    if (partie->listeCase[partie->listeJoueur[numeroJoueur].position].etat != 6 && partie->listeCase[partie->listeJoueur[numeroJoueur].position].etat != 9){affichagePlateau(*partie);}
    printf("Vous avez obtenu %d et %d soit %d\n", valeurDe1, valeurDe2, valeurDe1+valeurDe2);
    if (valeurDe1 == valeurDe2){printf("Bravo ! Vous avez fait un double\n");}
    printf("Vous etes tombe sur la case numero %d\n", partie->listeJoueur[numeroJoueur].position);
    switch (partie->listeCase[partie->listeJoueur[numeroJoueur].position].etat) //pointeur null (liste case surement)
    {
        case 0 : // 0 pour propriete en vente
            printf("Vous arrive a %s\n"
                   "Cette propriete n'appartient a personne\n"
                   "Voulez vous l'acheter pour %d euros ?\n",
                   partie->listeCase[partie->listeJoueur[numeroJoueur].position].nom,
                   partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prixAchat);
            partie->listeJoueur[numeroJoueur].etat = 4;
            break;

        case 1 :  //1 pour propriete deja acheter
            printf("Vous arrive a %s\n"
                   "Cette propriete appartient a %s\n",
                   partie->listeCase[partie->listeJoueur[numeroJoueur].position].nom,
                   partie->listeJoueur[partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].numeroProprietaire].nom);
            partie->listeJoueur[numeroJoueur].etat = 4;
            switch (partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].nombreMaison)
            {
                case 0 :
                    printf("Le terrain est nu, la place de camping est de %d euros.\n",
                           partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prixTerrainNu);
                    break;

                case 1 :
                    printf("Il y a 1 maison, le loyer de celle-ci est de %d euros.\n",
                           partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prix1Maison);
                    break;

                case 2 :
                    printf("Il y a 2 maisons, le loyer est de %d euros.\n",
                           partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prix2Maison);
                    break;

                case 3 :
                    printf("Il y a 3 maisons, le loyer est de %d euros.\nLes prix sont ils vraiments raisonnable ?\n",
                           partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prix3Maison);
                    break;

                case 4 :
                    printf("Il y a 4 maisons, le loyer est de %d euros.\nOui Oui, c'est autant pour juste une nuit ...\n",
                           partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prix4Maison);
                    break;

                case 5 :
                    printf("Vous y trouver un gigantesque hotel 5 etoiles, la nuite est de %d euros O_O.\n",
                           partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].prixHotel);
                    break;

                default :
                    printf("ERROR : nombre de maison de ce terrain non valide\n");
                    break;
            }

            break;

        case 2 : // 2 pour acheter et hypotheque
            printf("Vous arrive a %s\n"
                   "Cette propriete appartient a %s\n"
                   "Cependant l'endroit est desert, il n'y a qu'un petit cabanon\n"
                   "Vous parvenez a entrez dans le cabanon, et vous pourrez y dormir gratuitement\n",
                   partie->listeCase[partie->listeJoueur[numeroJoueur].position].nom,
                   partie->listeJoueur[partie->listePropriete[partie->listeCase[partie->listeJoueur[numeroJoueur].position].numeroPropriete].numeroProprietaire].nom);
            partie->listeJoueur[numeroJoueur].etat = 4;
            break;

        case 3 : // 3 chance
            printf("Vous arrive sur une case chance !\n"
                   "Vous tirez la premiere carte : %s\n",
                   partie->listeChaineCarteChance->carte[0]);
            partie->listeJoueur[numeroJoueur].etat = 4;
            break;

        case 4 : // 4 communaute
             printf("Vous arrive sur une case caise de communaute !\n"
                   "Vous tirez la premiere carte : %s\n",
                   partie->listeChaineCarteCommunaute->carte[0]);
            partie->listeJoueur[numeroJoueur].etat = 4;

            break;

        case 5 : // 5 depart
            printf("Vous arrive sur la case depart !\n");
            partie->listeJoueur[numeroJoueur].etat = 4;
            break;

        case 6 : // 6 gare
            partie->listeJoueur[numeroJoueur].position = (partie->listeJoueur[numeroJoueur].position + NOMBRE_CASES_ENTRE_GARE) % NOMBRE_CASES_PLATEAU;
            partie->listeJoueur[numeroJoueur].etat = 4;
            if (memoirePosition > (partie->listeJoueur[numeroJoueur].position + valeurDe1+valeurDe2) % NOMBRE_CASES_PLATEAU){partie->listeJoueur[numeroJoueur].argent += SALAIRE_PAR_TOUR;}
            affichagePlateau(*partie);
            printf("Vous arrive a une gare, vous sautez dans le premier train\nVous realisez une fois dans le train que vous n'avez pas achete de ticket\nVous descendez donc au premier arret avant que des controlleurs n'arrivent\n");
            break;

        case 7 : // 7 visite prison
            printf("Vous passez pres de la prison et decidez d'aller la visiter afin de narguer les prisonniers \n(faite attention au karma tout de meme)\n");
            partie->listeJoueur[numeroJoueur].etat = 4;
            break;

        case 8 : // 8 parc gratuit
            printf("Vous vous rendez dans un parc gratuit\n"
                   "le chant des oiseaux et le bruit du ruisseau vous distrait de votre travail, vous empechant de recolter les benefices de vos proprietes\n");
            partie->listeJoueur[numeroJoueur].etat = 0;
            break;

        case 9 : // 9 prison
            prison(partie->listeJoueur, numeroJoueur);
            affichagePlateau(*partie);
            printf("Vous marchez tranquillement quand soudainement un individu surgit d'une rue, vous coupe la route et disparait \ndans une petite rue.\n"
                   "Puis 3 policiers arrive de la d'ou vient l'individu suspect!\n"
                   "Vous essayer d'indiquer au policier la rue par laquelle s'est enfui l'individu recherche\n"
                   "Mais les policiers vous tire immediatement dessus avec leur taser\n"
                   "Vous ne vous reveillerez que le lendemain derriere les barreaux\n");
            *finDeTour = 1;

            break;

        case 10 : // 10 taxe
            if (partie->listeCase[partie->listeJoueur[numeroJoueur].position].taxe > 0)
            {
                printf("Il est temps de payer vos taxe !\n"
                       "%s\n", partie->listeCase[partie->listeJoueur[numeroJoueur].position].nom);
            }
            else
            {
                printf("C'est votre jour de chance\n%s", partie->listeCase[partie->listeJoueur[numeroJoueur].position].nom);
            }
            partie->listeJoueur[numeroJoueur].etat = 4;
            break;

        default :
            printf("ERROR : l'etat de votre case n'est pas repertorie (%d)\n", partie->listeCase[partie->listeJoueur[numeroJoueur].position].etat);
            break;
    }
} //on fait se deplacer le joueur



void achatMaison(dataPartie* partie, int numeroJoueur)
{
    int quelleCouleur = 0, maisonOuHotel = 0, combienMaison = 0, quelTerrain =-1;

    printf("Il faut posseder toutes les proprietes d'une meme groupe pour pouvoir y construire des maisons\n");
    printf("0/ Retour\n");
    for (int i = 0 ; i < NOMBRE_PROPRIETE ; i+=2)
    {
        if (partie->listePropriete[partie->listeCase[partie->listePropriete[i].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].numeroProprietaire == numeroJoueur && partie->listePropriete[partie->listeCase[partie->listePropriete[i].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].numeroProprietaire == numeroJoueur)
        {
            printf("%d/ Vous possedez toutes les proprietes du groupe %d\n", partie->listePropriete[i].couleur, partie->listePropriete[i].couleur);
        }
    }
    printf("\nSaisissez le numero du groupe ou vous souhaitez construire des maisons\n");
    quelleCouleur = saisirEntier();
    if (quelleCouleur!=0 && partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].numeroProprietaire == numeroJoueur && partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].numeroProprietaire == numeroJoueur)
    {
        printf("Vous avez %d maison(s) et %d hotel sur %s\n"
               "Et %d maison(s) et %d hotel sur %s\n"
               "Vous devez construire uniformement sur chaque terrain (une maison coute %d euro)\n"
               "Que souhaitez vous acheter :\n"
               "1/ Maisons\n"
               "2/ Hotel\n"
               "3/ Retour\n",
               partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison,
               partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreHotel,
               partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].nom,
               partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison,
               partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreHotel,
               partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].nom,
               partie->listePropriete[(quelleCouleur-1)*2].prixAchatMaison);
        maisonOuHotel = saisirEntier();

        if (maisonOuHotel == 1)
        {
            printf("Combien de maison souhaite vous construire ?\n");
            combienMaison = saisirEntier();
            if (verifArgent(partie->listeJoueur, combienMaison*partie->listePropriete[(quelleCouleur-1)*2].prixAchatMaison,numeroJoueur)==0)
            {
                return;
            }
            if (partie->donnesDeLaPartie.nombreMaison >= combienMaison && partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison + partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison + combienMaison<=8)
            {
                if ((combienMaison + partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison + partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison)%2==1)
                {
                    printf("Sur quelle propriete souhaite vous construire la derniere maison\n1/ %s\n2/ %s\n",
                           partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].nom,
                           partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].nom);
                    quelTerrain = saisirEntier() - 1;
                }
                partie->listeJoueur[numeroJoueur].argent -= combienMaison*partie->listePropriete[(quelleCouleur-1)*2].prixAchatMaison;
                partie->donnesDeLaPartie.nombreMaison -= combienMaison;

                if ((partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison + partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison)%2==1)
                {
                    combienMaison-=1;
                    if ( partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison > partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison )
                    {
                        partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison += 1;
                    }
                    else
                    {
                        partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison += 1;
                    }

                }

                partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison += combienMaison/2;
                partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison += combienMaison/2;
                if (quelTerrain == 0 || quelTerrain == 1)
                {
                    partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[quelTerrain]].numeroPropriete].nombreMaison += 1;
                }
                affichagePlateau(*partie);
            }
            else
            {
                printf("La banque ne possede pas assez de maisons\n"
                       "Elle en a %d\n"
                       "(Rappel : vous pouvez construire que 4 maisons par proprietes maximum)",
                       partie->donnesDeLaPartie.nombreMaison);
            }
        }
        else if (maisonOuHotel == 2)
        {
            if (partie->donnesDeLaPartie.nombreHotel >= combienMaison && partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison + partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison ==8)
            {
                printf("Sur quelle propriete souhaite vous construire votre hotel\n%s(saisissez 0)\n%s(saisissez 1)",
                       partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].nom,
                       partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].nom);
                quelTerrain = saisirEntier();
                partie->listeJoueur[numeroJoueur].argent -= partie->listePropriete[(quelleCouleur-1)*2].prixAchatMaison;
                partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[quelTerrain]].numeroPropriete].nombreMaison = 0;
                partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[quelTerrain]].numeroPropriete].nombreHotel = 1;
                partie->donnesDeLaPartie.nombreHotel -= 1;
                affichagePlateau(*partie);
            }
            else
            {
                printf("C'est impossible car :\n"
                       "Soit vous n'avez pas 4 maisons sur toutes les proprietes de ce groupe\n"
                       "Soit la banque ne possede plus d'hotel\n");
            }
        }

    }
    else
    {
        printf("Vous n'avez pas ce groupe de proprietes\n");
    }
} //le joueur veut achter des maisons



void marchandage(dataPartie* partie, int numeroJoueur)
{
    int avecQui = -1, quoiEchanger = -1, quiRecoit = -1, quellePropriete = -1, pourCombien = 0, confirmationAchat = -1, deshypotheque = -1;

    printf("Avec qui souhaitez vous marchandez ?\n");
    for (int i = 0 ; i < partie->donnesDeLaPartie.nombreJoueur ; i++)
    {
        if (partie->listeJoueur[i].etat != -1 && i!=numeroJoueur)
        {
            printf("%d/ %s\n", i, partie->listeJoueur[i].nom);
        }
    }
    avecQui = saisirEntier();

    printf("Que voulez vous marchandez ?\n"
           "1/ Propriete\n"
           "2/ Carte sortie de prison\n"
           "3/ Retour\n");
    quoiEchanger = saisirEntier();

    printf("Qui est le receveur de la carte ?\n"
           "1/ %s\n" //le joueur qui joue en ce moment (nommé je par la suite de cette fonction)
           "2/ %s\n",
           partie->listeJoueur[numeroJoueur].nom, partie->listeJoueur[avecQui].nom);
    quiRecoit = saisirEntier();

    if (quoiEchanger == 1)
    {
        if (quiRecoit == 1)    // je recoit une propriete
        {
            for (int i = 0; i < NOMBRE_CASES_PLATEAU ; i++) //affichage des propriete de l'autre joueur
            {
                if ( (partie->listeCase[i].etat==1 || partie->listeCase[i].etat==2) && partie->listePropriete[partie->listeCase[i].numeroPropriete].numeroProprietaire==avecQui)
                {
                    printf("%d/ %s\n", i, partie->listeCase[i].nom);
                }
            }
            quellePropriete = saisirEntier();
            if (verifPasDeMaison(partie->listePropriete, partie->listeCase, quellePropriete)==0){return;}
            printf("%s pour combien vend tu cette propriete ?\n", partie->listeJoueur[avecQui].nom);
            pourCombien = saisirEntier();

            if (partie->listeCase[quellePropriete].etat == 2) // la propriete est hypothequer
            {
                printf("Cette propriete est hypopthequer\n"
                       "Tu devras donc payer 10 pourcent de la valeur de l'hypotheque a la banque lors de l'achat, soit %f\n"
                       "Tu peux ensuite lever l'hypotheque immediatement (en payant la valeur de l'hypotheque a la banque soit %d)\n "
                       "ou la lever plus tard mais tu devras repayer 10 pourcent a la banque dans ce cas\n",
                       0.1f * (float) partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].hypotheque,
                       partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].hypotheque);
            }


            printf("ICI : %d\n", pourCombien);


            printf("%s souhaite tu bien acheter %s pour %d euros ?(Saisis 1 pour oui)\n", partie->listeJoueur[numeroJoueur].nom, partie->listeCase[quellePropriete].nom,pourCombien);
            confirmationAchat = saisirEntier();
            if (confirmationAchat == 1)
            {
                if (verifArgent(partie->listeJoueur, pourCombien, numeroJoueur)==0){return;}
                if (partie->listeCase[quellePropriete].etat == 2)
                {
                    printf("%s souhaites tu lever l'hypotheque immediatement ?(Saisis 1 pour oui)\n", partie->listeJoueur[numeroJoueur].nom);
                    deshypotheque = saisirEntier();
                    if (deshypotheque==1)
                    {
                        if (verifArgent(partie->listeJoueur, (int) (1.1 * (float) partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].hypotheque + pourCombien), numeroJoueur)==0){return;}
                        partie->listeJoueur[numeroJoueur].argent -= (int) (1.1 * (float) partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].hypotheque);
                        partie->listeCase[quellePropriete].etat=1;
                    }
                    else
                    {
                        if (verifArgent(partie->listeJoueur, (int) (0.1 * (float) partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].hypotheque + pourCombien), numeroJoueur)==0){return;}
                        partie->listeJoueur[numeroJoueur].argent -= (int) (0.1 * (float) partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].hypotheque);
                    }
                }
                partie->listeJoueur[numeroJoueur].argent -= pourCombien;
                partie->listeJoueur[avecQui].argent += pourCombien;
                partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].numeroProprietaire = numeroJoueur;
            }
        }
        else if (quiRecoit==2) //je vend une propriete
        {
            for (int i = 0; i < NOMBRE_CASES_PLATEAU ; i++) //affichage des propriete de l'autre joueur
            {
                if ( (partie->listeCase[i].etat==1 || partie->listeCase[i].etat==2) && partie->listePropriete[partie->listeCase[i].numeroPropriete].numeroProprietaire==numeroJoueur)
                {
                    printf("%d/ %s\n", i, partie->listeCase[i].nom);
                }
            }
            quellePropriete = saisirEntier();
            if (verifPasDeMaison(partie->listePropriete, partie->listeCase, quellePropriete)==0){return;}
            printf("%s pour combien vend tu cette propriete ?\n", partie->listeJoueur[numeroJoueur].nom);
            pourCombien = saisirEntier();

            if (partie->listeCase[quellePropriete].etat == 2) // la propriete est hypothequer
            {
                printf("Cette propriete est hypopthequer\n"
                       "Tu devras donc payer 10 pourcent de la valeur de l'hypotheque a la banque lors de l'achat, soit %f\n"
                       "Tu peux ensuite lever l'hypotheque immediatement (en payant la valeur de l'hypotheque a la banque soit %d)\n "
                       "ou la lever plus tard mais tu devras repayer 10 pourcent a la banque dans ce cas\n",
                       0.1f * (float) partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].hypotheque,
                       partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].hypotheque);
            }


            printf("%s souhaite tu bien acheter %s pour %d euros ?(Saisis 1 pour oui)\n", partie->listeJoueur[avecQui].nom, partie->listeCase[quellePropriete].nom,pourCombien);
            confirmationAchat = saisirEntier();
            if (confirmationAchat == 1)
            {
                if (verifArgent(partie->listeJoueur, pourCombien, avecQui)==0){return;}

                if (partie->listeCase[quellePropriete].etat == 2)
                {
                    printf("%s souhaites tu lever l'hypotheque immediatement ?(Saisis 1 pour oui)\n", partie->listeJoueur[avecQui].nom);
                    deshypotheque = saisirEntier();
                    if (deshypotheque==1)
                    {
                        if (verifArgent(partie->listeJoueur, (int) (1.1 * (float) partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].hypotheque + pourCombien), avecQui)==0){return;}
                        partie->listeJoueur[avecQui].argent -= (int) (1.1 * (float) partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].hypotheque);
                        partie->listeCase[quellePropriete].etat=1;
                    }
                    else
                    {
                        if (verifArgent(partie->listeJoueur, (int) (0.1 * (float) partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].hypotheque + pourCombien), avecQui)==0){return;}
                        partie->listeJoueur[avecQui].argent -= (int) (0.1 * (float) partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].hypotheque);
                    }
                }

                partie->listeJoueur[numeroJoueur].argent += pourCombien;
                partie->listeJoueur[avecQui].argent -= pourCombien;
                partie->listePropriete[partie->listeCase[quellePropriete].numeroPropriete].numeroProprietaire = avecQui;
            }
        }
    }
    else if (quoiEchanger == 2)
    {
        if (quiRecoit==1) //je recoit une carte sortir de prison
        {
            verifCarteSortieDePrison(partie->listeJoueur, avecQui);
            if (verifCarteSortieDePrison(partie->listeJoueur, avecQui)==0){return;}
            printf("%s pour combien vend tu cette carte sortie de prison ?\n", partie->listeJoueur[avecQui].nom);
            pourCombien = saisirEntier();
            printf("%s souhaite tu bien acheter une carte sortie de prison pour %d euros ?(Saisis 1 pour oui)\n", partie->listeJoueur[numeroJoueur].nom, pourCombien);
            confirmationAchat = saisirEntier();
            if (confirmationAchat == 1)
            {
                if (verifArgent(partie->listeJoueur, pourCombien, numeroJoueur)==0){return;}
                partie->listeJoueur[numeroJoueur].argent -= pourCombien;
                partie->listeJoueur[avecQui].argent += pourCombien;
                if (verifCarteSortieDePrison(partie->listeJoueur, avecQui) == 1)
                {
                    partie->listeJoueur[numeroJoueur].carteSortiePrisonChance +=1;
                    partie->listeJoueur[avecQui].carteSortiePrisonChance -=1;
                }
                else
                {
                    partie->listeJoueur[numeroJoueur].carteSortiePrisonCommunaute +=1;
                    partie->listeJoueur[avecQui].carteSortiePrisonCommunaute -=1;
                }
            }
        }
        else if (quiRecoit == 2) // je vend une carte sortir de prison
        {
            if (verifCarteSortieDePrison(partie->listeJoueur, numeroJoueur)==0){return;}
            printf("%s pour combien vend tu cette carte sortie de prison ?\n", partie->listeJoueur[numeroJoueur].nom);
            pourCombien = saisirEntier();
            printf("%s souhaite tu bien acheter une carte sortie de prison pour %d euros ?(Saisis 1 pour oui)\n", partie->listeJoueur[avecQui].nom, pourCombien);
            confirmationAchat = saisirEntier();
            if (confirmationAchat == 1)
            {
                if (verifArgent(partie->listeJoueur, pourCombien, numeroJoueur)==0){return;}
                partie->listeJoueur[numeroJoueur].argent += pourCombien;
                partie->listeJoueur[avecQui].argent -= pourCombien;
                if (verifCarteSortieDePrison(partie->listeJoueur, numeroJoueur) == 1)
                {
                    partie->listeJoueur[numeroJoueur].carteSortiePrisonChance -=1;
                    partie->listeJoueur[avecQui].carteSortiePrisonChance +=1;
                }
                else
                {
                    partie->listeJoueur[numeroJoueur].carteSortiePrisonCommunaute -=1;
                    partie->listeJoueur[avecQui].carteSortiePrisonCommunaute +=1;
                }
            }
        }
    }
} //le joueur veut marchander avec qq d'autre



void hypotheque(dataPartie*  partie, int numeroJoueur)// fonction qui hypotheque ou vend des maisons
{
    int quoiFaire = 0, quelleCouleur = 0, combienMaison = 0, quelTerrain =-1, ToutVendreOuPas = 0;

    printf("Que voulez vous faire ?\n"
           "1/ Vendre des maisons \n"
           "2/ Vendre un hotel \n"
           "3/ Hypothequer\n"
           "4/ Lever une hypotheque\n"
           "(Rappel : le nombre de maison sur les propriete d'un meme groupe doivent etre uniforme, \n"
           "aussi bien lorsqu'on achete que lorsqu'on vend des maisons.\n"
           "Et hypothequer un terrain vendra instanement toutes les maisons de celui-ci.\n"
           "Les maisons sont vendu a la moitie de leur prix d'achat)\n");

    quoiFaire = saisirEntier();
    switch (quoiFaire)
    {
        case 1 :
            for (int i = 0 ; i < NOMBRE_PROPRIETE ; i+=2)
            {
                if (partie->listePropriete[partie->listeCase[partie->listePropriete[i].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].numeroProprietaire == numeroJoueur && partie->listePropriete[partie->listeCase[partie->listePropriete[i].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].numeroProprietaire == numeroJoueur)
                {
                    printf("Vous possedez toutes les proprietes du groupe %d\n", partie->listePropriete[i].couleur);
                }
            }
            printf("\nSaisissez le numero du groupe ou vous souhaitez construire des maisons\n");
            quelleCouleur = saisirEntier();
            if (partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].numeroProprietaire == numeroJoueur && partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].numeroProprietaire == numeroJoueur)
            {
                printf("Vous avez %d maison(s) et %d hotel sur %s\n"
                       "Et %d maison(s) et %d hotel sur %s\n"
                       "Vous devez vendre uniformement sur chaque terrain (une maison coute %d euro)\n",
                       partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison,
                       partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreHotel,
                       partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].nom,
                       partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison,
                       partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreHotel,
                       partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].nom,
                       partie->listePropriete[(quelleCouleur-1)*2].prixAchatMaison);


                printf("Combien de maison souhaite vous vendre ?\n");
                combienMaison = saisirEntier();

                if ((combienMaison + partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison + partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison)%2==1)
                {
                    printf("Sur quelle propriete souhaite vous vendre la derniere maison\n1/ %s\n2/ %s",
                           partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].nom,
                           partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].nom);
                    quelTerrain = saisirEntier() - 1;
                }
                partie->listeJoueur[numeroJoueur].argent += (int) ((float) combienMaison * (float) partie->listePropriete[(quelleCouleur-1)*2].prixAchatMaison/2.0f);
                partie->donnesDeLaPartie.nombreMaison += combienMaison;
                if ((partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison + partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison)%2==1)
                {
                    combienMaison-=1;
                    if ( partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison > partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison )
                    {
                        partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison -= 1;
                    }
                    else
                    {
                        partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison -= 1;
                    }

                }
                partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison -= combienMaison/2;
                partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison -= combienMaison/2;
                if (quelTerrain == 0 || quelTerrain == 1)
                {
                    partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[quelTerrain]].numeroPropriete].nombreMaison += 1;
                }


                affichagePlateau(*partie);

            }
            else
            {
                printf("Vous ne possedez pas ce groupe de propriete\n");
            }
            break;







        case 2 :
            for (int i = 0 ; i < NOMBRE_PROPRIETE ; i+=2)
            {
                if (partie->listePropriete[partie->listeCase[partie->listePropriete[i].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].numeroProprietaire == numeroJoueur && partie->listePropriete[partie->listeCase[partie->listePropriete[i].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].numeroProprietaire == numeroJoueur)
                {
                    printf("Vous possedez toutes les proprietes du groupe %d\n", partie->listePropriete[i].couleur);
                }
            }
            printf("\nSaisissez le numero du groupe ou vous souhaitez construire des maisons\n");
            quelleCouleur = saisirEntier();
            if (partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].numeroProprietaire == numeroJoueur && partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].numeroProprietaire == numeroJoueur)
            {
                printf("Vous avez %d hotel sur %s\n"
                       "Et %d hotel sur %s\n"
                       "La vente d'un hotel vous rapporte %f\n"
                       "Vous voulez vendre l'hotel de quel terrain ?\n"
                       "1/ %s\n"
                       "2/ %s\n"
                       "3/ Retour\n",
                       partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreHotel,
                       partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].nom,
                       partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreHotel,
                       partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].nom,
                       (5.0f * (float) partie->listePropriete[(quelleCouleur-1)*2].prixAchatMaison)/2.0f,
                       partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].nom,
                       partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].nom);

                quelTerrain = saisirEntier();
                printf("Que souhaitez vous faire\n"
                       "1/ Vendre 1 hotel, et avoir 4 maisons\n"
                       "2/ Vendre 1 hotel et ne plus avoir de maison (il resteras toujours une maison sur les autres proprietes)\n"
                       "3/ Retour\n");
                ToutVendreOuPas = saisirEntier();
                if (ToutVendreOuPas == 1)
                {
                    if (partie->donnesDeLaPartie.nombreMaison >= 4)
                    {
                        if (quelTerrain==1)
                        {
                            if (partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreHotel == 0){printf("Vous n'avez pas d'hotel sur cette propriete\n");return;}
                            partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreHotel = 0;
                            partie->listeJoueur[numeroJoueur].argent += (int) ((1.0f * (float) partie->listePropriete[(quelleCouleur-1)*2].prixAchatMaison)/2.0f);
                            partie->donnesDeLaPartie.nombreHotel+=1;
                            partie->donnesDeLaPartie.nombreMaison-=4;
                        }
                        else if (quelTerrain == 2)
                        {
                            if (partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreHotel == 0){printf("Vous n'avez pas d'hotel sur cette propriete\n");return;}
                            partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreHotel = 0;
                            partie->listeJoueur[numeroJoueur].argent += (int) ((1.0f * (float) partie->listePropriete[(quelleCouleur-1)*2].prixAchatMaison)/2.0f);
                            partie->donnesDeLaPartie.nombreHotel+=1;
                            partie->donnesDeLaPartie.nombreMaison-=4;
                        }
                    }
                    else
                    {
                        printf("La banque ne possede pas assez de maisons\n"
                               "Elle en a %d\n",
                               partie->donnesDeLaPartie.nombreMaison);
                    }
                }
                else if(ToutVendreOuPas == 2)
                {

                    if (quelTerrain == 1)
                    {
                        if (partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreHotel == 0){printf("Vous n'avez pas d'hotel sur cette propriete\n");return;}
                        partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreHotel = 0;
                        partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreMaison = 1;
                        partie->listeJoueur[numeroJoueur].argent += (int) ((9.0f * (float) partie->listePropriete[(quelleCouleur-1)*2].prixAchatMaison)/2.0f);
                        if (partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreHotel == 1)
                        {partie->donnesDeLaPartie.nombreMaison -=1;
                            partie->donnesDeLaPartie.nombreHotel += 2;}
                        else
                        {partie->donnesDeLaPartie.nombreMaison +=3;
                            partie->donnesDeLaPartie.nombreHotel += 1;}
                    }
                    else if (quelTerrain == 2)
                    {
                        if (partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreHotel == 0){printf("Vous n'avez pas d'hotel sur cette propriete\n");return;}
                        partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[1]].numeroPropriete].nombreHotel = 0;
                        partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreMaison = 1;
                        partie->listeJoueur[numeroJoueur].argent += (int) ((9.0f * (float) partie->listePropriete[(quelleCouleur-1)*2].prixAchatMaison)/2.0f);
                        if (partie->listePropriete[partie->listeCase[partie->listePropriete[(quelleCouleur-1)*2].numeroCaseDesProprieteDeCetteCouleur[0]].numeroPropriete].nombreHotel == 1)
                        {partie->donnesDeLaPartie.nombreMaison -=1;
                            partie->donnesDeLaPartie.nombreHotel += 2;}
                        else
                        {partie->donnesDeLaPartie.nombreMaison +=3;
                            partie->donnesDeLaPartie.nombreHotel += 1;}
                    }
                }
                affichagePlateau(*partie);
            }
            else
            {
                printf("Vous ne possedez pas ce groupe de propriete\n");
            }

            break;



        case 3 :
            printf("Voici vos terrain non hypothequer :\n0/ Retour\n");
            for (int i = 0 ; i < NOMBRE_CASES_PLATEAU ; i++)
            {
                if (partie->listeCase[i].numeroPropriete != -1 && partie->listeCase[i].etat != 2 && partie->listePropriete[partie->listeCase[i].numeroPropriete].numeroProprietaire == numeroJoueur)
                {
                    printf("%d/ %s (l'hyptoheque vous rapporte %d)\n", i, partie->listeCase[i].nom, partie->listePropriete[partie->listeCase[i].numeroPropriete].hypotheque);
                }
            }
            printf("Saisissez la propriete que vous souhaitez hyptohequer\n");
            quelTerrain = saisirEntier();
            if (partie->listePropriete[partie->listeCase[quelTerrain].numeroPropriete].numeroProprietaire != numeroJoueur || partie->listeCase[quelTerrain].etat == 2){printf("Ce terrain n'est pas a vous, ou est deja hypothequer\n");return;}
            if (verifPasDeMaison(partie->listePropriete, partie->listeCase, quelTerrain) == 0){return;}
            partie->listeJoueur[numeroJoueur].argent += partie->listePropriete[partie->listeCase[quelTerrain].numeroPropriete].hypotheque;
            partie->listeCase[quelTerrain].etat = 2;
            affichagePlateau(*partie);
            printf("%s est hypothequer !\n", partie->listeCase[quelTerrain].nom);
            break;

        case 4 :
            printf("Voici vos terrain hypothequer :\n0/ Retour\n");
            for (int i = 0 ; i < NOMBRE_CASES_PLATEAU ; i++)
            {
                if (partie->listeCase[i].numeroPropriete != -1 && partie->listeCase[i].etat == 2 && partie->listePropriete[partie->listeCase[i].numeroPropriete].numeroProprietaire == numeroJoueur)
                {
                    printf("%d/ %s (lever l'hypotheque vous coute %f)\n", i, partie->listeCase[i].nom, 1.1f * (float) partie->listePropriete[partie->listeCase[i].numeroPropriete].hypotheque);
                }
            }
            printf("Saisissez la propriete ou vous souhaitez lever l'hyptohequer\n");
            quelTerrain = saisirEntier();
            if (partie->listePropriete[partie->listeCase[quelTerrain].numeroPropriete].numeroProprietaire != numeroJoueur || partie->listeCase[quelTerrain].etat != 2){printf("Ce terrain n'est pas a vous, ou n'est pas hypothequer\n");return;}
            if (verifArgent(partie->listeJoueur, (int) (1.1f * (float) partie->listePropriete[partie->listeCase[quelTerrain].numeroPropriete].hypotheque), numeroJoueur) == 0){return;}
            partie->listeJoueur[numeroJoueur].argent -= (int) (1.1f * (float) partie->listePropriete[partie->listeCase[quelTerrain].numeroPropriete].hypotheque);
            partie->listeCase[quelTerrain].etat = 1;
            affichagePlateau(*partie);
            printf("%s n'est plus hypothequer !\n", partie->listeCase[quelTerrain].nom);
            break;

        default :
            saisitInvalide();
    }
}











void achat(dataPartie* partie, int numeroJoueur, unsigned int quelTerrain)
{
    if (verifArgent(partie->listeJoueur, partie->listePropriete[partie->listeCase[quelTerrain].numeroPropriete].prixAchat,numeroJoueur) == 0){return;}
    if (partie->listeCase[quelTerrain].etat != 0 || partie->listePropriete[partie->listeCase[quelTerrain].numeroPropriete].numeroProprietaire != -1){return;}
    partie->listePropriete[partie->listeCase[quelTerrain].numeroPropriete].numeroProprietaire = numeroJoueur;
    partie->listeCase[quelTerrain].etat = 1;
    partie->listeJoueur[numeroJoueur].argent -= partie->listePropriete[partie->listeCase[quelTerrain].numeroPropriete].prixAchat;
    affichagePlateau(*partie);
    printf("%s est maintenant la propriete de %s\n", partie->listeCase[quelTerrain].nom,partie->listeJoueur[numeroJoueur].nom);
} // le joueur veut acheter une propriete



void remiseCarteSortiePrison(dataPartie* partie, int chanceOuCommunaute)
{
    if (chanceOuCommunaute == 1)
    {
        listeChaineCarte* listeChaineCarteChance = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
        listeChaineCarteChance->carte = (char**) calloc( 1 , sizeof(char*) );
        listeChaineCarteChance->carte[0] = (char*) calloc( 23 , sizeof(char) );
        strcpy(listeChaineCarteChance->carte[0], "Carte sortie de prison\0");
        listeChaineCarteChance->next = partie->listeChaineCarteChance;
        partie->listeChaineCarteChance->next->next->next->next->next->next->next->next = listeChaineCarteChance;
    }
    else
    {
        listeChaineCarte* listeChaineCarteCommunaute = (listeChaineCarte*) calloc(1, sizeof(listeChaineCarte));
        listeChaineCarteCommunaute->carte = (char**) calloc( 1 , sizeof(char*) );
        listeChaineCarteCommunaute->carte[0] = (char*) calloc( 23 , sizeof(char) );
        strcpy(listeChaineCarteCommunaute->carte[0], "Carte sortie de prison\0");
        listeChaineCarteCommunaute->next = partie->listeChaineCarteCommunaute;
        partie->listeChaineCarteCommunaute->next->next->next->next->next->next->next->next->next = listeChaineCarteCommunaute;
    }
}//remmet une carte sortie de prison sous le paquet



int paye(dataPartie* partie, int quiPaye, int quiRecoit, int combien)// fonction permettant de payer en verifiant s'il peut payer // lorsque c'est la banque qui recoit on met -1
{
    if (boolFaillite(partie, quiPaye, combien) == 1){faillite(partie, quiPaye, quiRecoit);return(1);}
    if (verifArgent(partie->listeJoueur, combien, quiPaye) == 0){return(0);}
    if (quiRecoit != -1)
    {
        partie->listeJoueur[quiRecoit].argent += combien;
    }
    partie->listeJoueur[quiPaye].argent -= combien;
    affichagePlateau(*partie);
    return(1);
}



int boolFaillite(dataPartie* partie, int numeroJoueur, int combien)
{
    unsigned int memoireArgent = 0;
    memoireArgent = partie->listeJoueur[numeroJoueur].argent;
    for (int i = 0 ; i < NOMBRE_CASES_PLATEAU ; i++)
    {
        if (partie->listeCase[i].numeroPropriete != -1 && partie->listeCase[i].etat != 2 && partie->listePropriete[partie->listeCase[i].numeroPropriete].numeroProprietaire == numeroJoueur)
        {
            memoireArgent += partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreMaison * (int) ( (float)partie->listePropriete[partie->listeCase[i].numeroPropriete].prixAchatMaison / 2.0f);
            memoireArgent += partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreHotel * (int) ( (float)partie->listePropriete[partie->listeCase[i].numeroPropriete].prixAchatMaison * 5.0f/ 2.0f);
            memoireArgent += partie->listePropriete[partie->listeCase[i].numeroPropriete].hypotheque;
        }
    }
    if (memoireArgent < combien)
    {
        printf("Vous n'avez pas assez d'argent meme si vous vendez tout vos hotels, maisons et proprietes a la banque\nLe marchandage avec d'autre joueur ne peut se faire qu'avant le lance de de ou apres la paye\nToutes vos biens revienne a votre crediteur (sans maison et hypothequer si le bien l'etait)");
        return(1);
    }
    else
    {
        return(0);
    }
} //booleen de si le joueur est en failite (pas assez d'argent meme en vendant tout -> renvoit 1) ou non



void faillite(dataPartie* partie, int numeroJoueur, int quiRecoit) // lorsque c'est la banque qui recoit on met -1
{
    int choixHypotheque = 0;

    if (quiRecoit == -1)
    {
        partie->listeJoueur[numeroJoueur].etat = -1;
        partie->listeJoueur[numeroJoueur].argent = 0;
        partie->donnesDeLaPartie.nombreJoueurLogique -= 1;
        for (int i = 0; i < partie->listeJoueur[numeroJoueur].carteSortiePrisonChance ; i++)
        {
            remiseCarteSortiePrison(partie, 1);
        }
        for (int i = 0; i < partie->listeJoueur[numeroJoueur].carteSortiePrisonCommunaute ; i++)
        {
            remiseCarteSortiePrison(partie, 2);
        }
        for (int i = 0; i < NOMBRE_CASES_PLATEAU ; i++)
        {
            if ((partie->listeCase[i].etat == 1 || partie->listeCase[i].etat == 2) &&
                    partie->listePropriete[partie->listeCase[i].numeroPropriete].numeroProprietaire == numeroJoueur) {
                partie->donnesDeLaPartie.nombreMaison += partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreMaison;
                partie->donnesDeLaPartie.nombreHotel += partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreHotel;
                partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreMaison = 0;
                partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreHotel = 0;
                partie->listePropriete[partie->listeCase[i].numeroPropriete].numeroProprietaire = -1;
                partie->listeCase[i].etat = 0;
            }
        }
    }
    else
    {
        partie->listeJoueur[numeroJoueur].etat = -1;
        for (int i = 0 ; i < NOMBRE_CASES_PLATEAU ; i++) // vente de toutes les maisons
        {
            if (partie->listePropriete[partie->listeCase[i].numeroPropriete].numeroProprietaire == numeroJoueur)
            {
                partie->listeJoueur[numeroJoueur].argent += partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreMaison * partie->listePropriete[partie->listeCase[i].numeroPropriete].prixAchatMaison + partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreHotel * 5 * partie->listePropriete[partie->listeCase[i].numeroPropriete].prixAchatMaison;
            }
        }
        partie->listeJoueur[quiRecoit].argent += partie->listeJoueur[numeroJoueur].argent;
        partie->donnesDeLaPartie.nombreJoueurLogique -= 1;
        for (int i = 0; i < NOMBRE_CASES_PLATEAU ; i++)
        {
            if ((partie->listeCase[i].etat == 1 || partie->listeCase[i].etat == 2) &&
                    partie->listePropriete[partie->listeCase[i].numeroPropriete].numeroProprietaire == numeroJoueur)
            {
                partie->donnesDeLaPartie.nombreMaison += partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreMaison;
                partie->donnesDeLaPartie.nombreHotel += partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreHotel;
                partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreMaison = 0;
                partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreHotel = 0;
                partie->listePropriete[partie->listeCase[i].numeroPropriete].numeroProprietaire = quiRecoit;
                partie->listeJoueur[quiRecoit].carteSortiePrisonChance += partie->listeJoueur[numeroJoueur].carteSortiePrisonChance;
                partie->listeJoueur[quiRecoit].carteSortiePrisonCommunaute += partie->listeJoueur[numeroJoueur].carteSortiePrisonCommunaute;
                if (partie->listeCase[i].etat == 2)
                {
                    printf("%s veux tu lever l'hypotheque de %s \n"
                           "1/ Immediatemment en payant %d\n"
                           "2/ Ou bien payer 10 pourcent de l'hypoptheque et lever l'hypotheque plus tard \n"
                           "(tu devras repayer 10 pourcent en plus de la valeur de l'hypotheque)\n",
                           partie->listeJoueur[quiRecoit].nom,
                           partie->listeCase[i].nom,
                           partie->listePropriete[partie->listeCase[i].numeroPropriete].hypotheque);
                    choixHypotheque = saisirEntier();
                    while (choixHypotheque != 1 && choixHypotheque != 2)
                    {
                        saisitInvalide();
                        choixHypotheque = saisirEntier();
                    }
                    if (choixHypotheque == 1)
                    {
                        if (verifArgent(partie->listeJoueur, (int) ((float) partie->listePropriete[partie->listeCase[i].numeroPropriete].hypotheque * 0.1f), quiRecoit) == 0){printf("Vous n'avez pas assez d'argent\n");choixHypotheque = 2;}
                        else
                        {
                            partie->listeJoueur[quiRecoit].argent -= (int) ((float) partie->listePropriete[partie->listeCase[i].numeroPropriete].hypotheque * 1.1f);
                            partie->listeCase[i].etat = 1;
                        }
                    }
                    if (choixHypotheque == 2)
                    {
                        if (verifArgent(partie->listeJoueur, (int) ((float) partie->listePropriete[partie->listeCase[i].numeroPropriete].hypotheque * 0.1f), quiRecoit) == 0)
                        {
                            printf("Vous n'avez pas assez d'argent pour racheter le terrain hypothequer !\n"
                                   "Cette propriete revient donc a la banque\n");
                            partie->listePropriete[partie->listeCase[i].numeroPropriete].numeroProprietaire = -1;
                            partie->listeCase[i].etat = 0;
                        }
                        else
                        {
                            partie->listeJoueur[quiRecoit].argent -= (int) ((float) partie->listePropriete[partie->listeCase[i].numeroPropriete].hypotheque * 0.1f);
                        }
                    }
                }
            }
        }
    }
}



int verifArgent(joueur* listeJoueur, int combien, int numeroJoueur)
{
    if (listeJoueur[numeroJoueur].argent - combien >= 0)
    {
        return(1);
    }
    else
    {
        printf("Vous n'avez pas assez d'argent !\n");
        return(0);
    }
}//verifie si le joueur a assez d'argent liquide



int verifPasDeMaison(propriete* listePropriete, cases* listeCase, int quellePropriete)
{


    if (listePropriete[listeCase[quellePropriete].numeroPropriete].nombreMaison == 0 && listePropriete[listeCase[quellePropriete].numeroPropriete].nombreHotel==0)
    {
        return(1);
    }
    else
    {
        printf("Il y a des maisons sur cette propriete\nIl faut que toutes les maisons soit d'abord vendu\n"); // le joeur peut pas acheter un terrain avec des maisons avec le tour du proprio ou il devra vendre ses maisons
        return(0);
    }
}//verifie si la propriete n'a pas de maisons (renvoit si yen a pas)



int verifCarteSortieDePrison(joueur* listeJoueur, int numeroJoueur)
{
    if (listeJoueur[numeroJoueur].carteSortiePrisonChance>=1)
    {
        return (1);
    }
    else if (listeJoueur[numeroJoueur].carteSortiePrisonCommunaute)
    {
        return(2);
    }
    else
    {
        return(0);
    }
}//verifie si le joueur possede une carte sortie de prison (renvoit 1 pour oui)



void abandon(dataPartie* partie, int numeroJoueur)
{
    int abandon = 0;

    printf("Veux tu vraiment abandonner %s ?\n"
           "Toute ton argent, tes proprietes, tes maisons retournerons a la banque\n"
           "1/ Oui j'abandonne\n"
           "2/ Non je veux continuer\n",
           partie->listeJoueur[numeroJoueur].nom);
    abandon = saisirEntier();
    if (abandon == 1)
    {
        partie->listeJoueur[numeroJoueur].etat = -1;
        partie->donnesDeLaPartie.nombreJoueurLogique -= 1;
        for (int i = 0; i < NOMBRE_CASES_PLATEAU ; i++) //affichage des propriete de l'autre joueur
        {
            if ( (partie->listeCase[i].etat==1 || partie->listeCase[i].etat==2) && partie->listePropriete[partie->listeCase[i].numeroPropriete].numeroProprietaire==numeroJoueur)
            {
                partie->donnesDeLaPartie.nombreMaison += partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreMaison;
                partie->donnesDeLaPartie.nombreHotel += partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreHotel;
                partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreMaison = 0;
                partie->listePropriete[partie->listeCase[i].numeroPropriete].nombreHotel = 0;
                partie->listePropriete[partie->listeCase[i].numeroPropriete].numeroProprietaire = -1 ;
                partie->listeCase[i].etat = 0;
            }
        }

    }
}//permet de tuer un joueur s'il le souhaite reellement



void prison(joueur* listeJoueur, int numeroJoueur)
{
    listeJoueur[numeroJoueur].etat = 1;
    listeJoueur[numeroJoueur].position = 8;
}//envoit un joueur en prison



void sauvegardeToiDansUnFichierBinaire(dataPartie * tab){
    FILE* pf = NULL;
    if ((pf = fopen("../monFichier.dat", "w")) == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
    }
    fseek(pf, SEEK_SET, 0);
    if (fwrite(tab, sizeof(dataPartie), 1, pf) != 1) {
        printf("Problème d'écriture dans le fichier.\n"); }
    fclose(pf);
    pf = NULL;
    printf("fichier sauvegarder\n");
}//sauvegarde la partie dans un fichier binaire



void chargeToiBinaire(dataPartie * tab){

    FILE* pf = fopen("../monFichier.dat", "r");
    fseek(pf, SEEK_SET, 0);
    if (pf == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
    }

    if (fread(tab, sizeof(dataPartie),1 ,pf) != 1) {
        printf("Probleme de fichier.\n"); }
    else
    {
        printf("fichier charge\n");
    }
    fclose(pf);
    pf = NULL;
}//charge une partie depuis un fichier binaire



void realisationCaseTaxe(dataPartie* partie, int numeroJoueur, int* EstCeQuIlAPaye)
{
    if (partie->listeJoueur[numeroJoueur].position == 2 || partie->listeJoueur[numeroJoueur].position == 10)
    {
        *EstCeQuIlAPaye = paye(partie, numeroJoueur, -1, 100);
    }

    else if (partie->listeJoueur[numeroJoueur].position == 18)
    {
        *EstCeQuIlAPaye =paye(partie, numeroJoueur, -1, 200);
    }

    else if (partie->listeJoueur[numeroJoueur].position == 10)
    {
        partie->listeJoueur[numeroJoueur].argent += 50;
    }
}//fait payer au joueur la taxe de sa case ou lui offre le bonus de sa case



void menuAvantPaye(dataPartie* partie, int numeroJoueur, int aQuiPaye, int* estCeQuilAPaye)
{
    int quoiFaire = 0;

    quoiFaire = saisirEntier();
    switch(quoiFaire)
    {
        case 1 :
            *estCeQuilAPaye = paye(partie, numeroJoueur, aQuiPaye, 50);
            break;
        case 2 :
            hypotheque(partie, numeroJoueur);
            break;
        case 3 :
            marchandage(partie, numeroJoueur);
            break;
        default :
            saisitInvalide();
            break;
    }
}//si un joueur doit payer mais n'a pas assez de liquide sans etre en faillite, il peut vendre des batiments












