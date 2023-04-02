//
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "affichage.h"
#include "structures.h"

#define NOMBRE_PROPRIETE 16

void affichageMenuPrincipal()
{
    printf("\nMenu principal\n\n"
           "1) Lancer une nouvelle partie\n"
           "2) Sauvegarder la partie en cours\n"
           "3) Charger une ancienne partie\n"
           "4) Afficher les regles\n"
           "5) Afficher le nom des membres de l'equipe du projet\n"
           "6) Quitter\n");
}


void affichageNomEquipeProjet()
{
    printf("Ce projet d'informatique consistant a concevoir un monopoly a ete efectue par :\n\n"
           "Erwan BONNEFOND\n"
           "Tom LAURENT\n"
           "Margaux LEGLISE\n"
           "Xiomara PAVEZ-RAFALD\n");

}

void saisitInvalide()
{
    printf("Saisit invalide\n");
}

void afficherMenuJoueurDebut()
{
    printf("\nQue voulez-vous faire ?\n\n"
           "1) Lancer les des\n"
           "2) Acheter une maison ou un hotel\n"
           "3) Marchander une propriete avec un autre joueur\n"
           "4) Hypothequer ou vendre des maisons / hotels ou deshypothequer\n"
           "5) Suspendre la partie\n"
           "6) Declarer forfait\n");
}
void afficherMenuJoueurFinRien()
{
    printf("\nQue voulez-vous faire ?\n\n"
           "   Cette case ne peut pas etre acheter, et vous n'avez pas a payer\n"
           "2) Acheter une maison ou un hotel\n"
           "3) Marchander une propriete avec un autre joueur\n"
           "4) Hypothequer ou vendre des maisons / hotels ou deshypothequer\n"
           "5) Mettre fin a votre tour ou rejouez si vous avez fait un double\n"
           "6) Declarer forfait\n");
}
void afficherMenuJoueurFinAchat()
{
    printf("\nQue voulez-vous faire ?\n\n"
           "1) Acheter la propriete\n"
           "2) Acheter une maison ou un hotel\n"
           "3) Marchander une propriete avec un autre joueur\n"
           "4) Hypothequer ou vendre des maisons / hotels ou deshypothequer\n"
           "5) Mettre fin a votre tour ou rejouez si vous avez fait un double\n"
           "6) Declarer forfait\n");
}
void afficherMenuJoueurFinPaye()
{
    printf("\nQue voulez-vous faire ?\n\n"
           "1) Payer le proprietaire\n"
           "2) Acheter une maison ou un hotel\n"
           "3) Marchander une propriete avec un autre joueur\n"
           "4) Hypothequer ou vendre des maisons / hotels ou deshypothequer\n"
           "5) Mettre fin a votre tour ou rejouez si vous avez fait un double(vous devez d'abord payez le proprietaire)\n"
           "6) Declarer forfait\n");
}

void afficherMenuJoueurFinTaxe()
{
    printf("\nQue voulez-vous faire ?\n\n"
           "1) Payer la taxe ou recevoir le bonus de la case\n"
           "2) Acheter une maison ou un hotel\n"
           "3) Marchander une propriete avec un autre joueur\n"
           "4) Hypothequer ou vendre des maisons / hotels ou deshypothequer\n"
           "5) Mettre fin a votre tour ou rejouez si vous avez fait un double(vous devez d'abord avoir realise l'action 1)\n"
           "6) Declarer forfait\n");
}

void afficherMenuJoueurFinCarte()
{
    printf("\nQue voulez-vous faire ?\n\n"
           "1) Realiser la carte tire\n"
           "2) Acheter une maison ou un hotel\n"
           "3) Marchander une propriete avec un autre joueur\n"
           "4) Hypothequer ou vendre des maisons / hotels ou deshypothequer\n"
           "5) Mettre fin a votre tour ou rejouez si vous avez fait un double(vous devez d'abord avoir realise l'action 1)\n"
           "6) Declarer forfait\n");
}


void affichageRegles() {
    printf("\nTout le monde connait les regles, mais bon les voila ci jamais :)\n");

    printf("\n"
           "                        ///LE JEU///\n"
           "\n"
           "Au debut, et une fois que chaque joueur ait saisi son nom, Le programme choisira aleatoirement qui commence.\n"
           "Son jeton est affichee sur le coin marque GO, il lance les 2 des, et sera deplace du nombre indique.\n"
           "Apres qu'il ait terminee son jeu, le tour de jeu passe a sa gauche (sens horaire). Les jetons restent sur la case et \npartiront a partir de ce point au tour suivant.\n"
           "Deux ou plus de deux joueur peuvent etre sur la meme cases au meme moment.\n"
           "En fonction de la case que son jeton atteint, le joueur peut avoir le droit d'acheter des biens immobiliers ou d'autres proprietees ou etre oblige de payer un loyer, payer des impoots, tirer une carte chance ou communautee etc.\n"
           "\n"
           "                        ///LE BANQUIER///\n"
           "\n"
           "C'est le programme qui fera office de Banquier. Ce dernier est censee encaisser et distribuer l'argent aux joueurs.\n"
           "\n"
           "                        ///LA BANQUE///\n"
           "\n"
           "Outre son argent, la Banque detient les cartes des terrains, les maisons et les hotels avant leur achat et utilisation \npar les joueurs.\n"
           "La Banque paie les salaires (200 euros pour le passage de la case depart) et les bonus.\n"
           "Elle vend les maisons et les hotels pour les joueurs et prete de l'argent lorsque requis sur les hypotheques.\n"
           "La Banque percoit toutes les taxes, amendes, prets et interets. La Banque ne fait jamais faillite (elle dispose de \nfonds illimites).\n"
           "\n"
           "                       ///LES DOUBLES///\n"
           "\n"
           "Si un joueur lance des doubles, Il a alors le droit de relancer les des une deuxieme fois.\n"
           "Si un joueur lance des doubles trois fois de suite, il deplace immediatement son jeton dans l'espace : En prison.\n"
           "\n"
           "                       /// LE DEPART///\n"
           "\n"
           "Chaque fois qu'un jeton atterrit ou passe par-dessus la case depart, que ce soit en jetant les des ou en tirant une \ncarte, le banquier paie au joueur un salaire de 200 euros.\n"
           "Les 200 euros ne sont payes qu'une seule fois a chaque fois autour de la planche.\n"
           "Cependant, si un joueur qui passe le depart sur le jet d'un de atterrit 2 cases au-dela sur le Coffre de la communaute,\n"
           "Ou 7 cases au-dela sur la Chance, et tire la carte Avance au Depart, il ramasse 200 euros pour passer \npar le depart la premiere fois et 200 euros pour l'atteindre la deuxieme fois par des instructions sur la carte.\n"
           "\n"
           "                    ///ACHETER UNE PROPRIETEE///\n"
           "\n"
           "Chaque fois qu'un joueur atterrit sur une propriete non possedee, il peut acheter cette propriete a la Banque \na son prix imprime.\n"
           "Le joueur recoit la carte de titre de propriete et la place face visible devant lui.\n"
           "\n"
           "                    ///PAYER LE LOYER///\n"
           "\n"
           "Lorsqu'un joueur atterrit sur une propriete appartenant a un autre joueur,\n"
           "le proprietaire percoit le loyer du joueur conformement a la liste imprimee sur la carte de titre de propriete \nqui lui est applicable.\n"
           "Si la propriete est hypothequee, aucun loyer ne peut etre percu. Lorsqu'une propriete est hypothequee, \nsa carte de titre de propriete est placee face cachee devant le proprietaire.\n"
           "C'est un avantage de detenir toutes les cartes de titre de propriete dans un groupe de couleur \nparce que le proprietaire peut alors facturer un double loyer pour les proprietes non ameliorees \ndans ce groupe de couleur.\n"
           "Cette regle s'applique aux proprietes non hypothequees, meme si une autre propriete de ce groupe de couleur \nest hypothequee.\n"
           "Il est encore plus avantageux d'avoir des maisons et des hotels sur les proprietes parce que les loyers \nsont beaucoup plus eleves que pour les proprietes non ameliorees.\n"
           "Le loyer est retire automatiquement de la cagnotte de la personne qui doit payer : si le solde est insuffisant \non lui demande s'il veut hypothequer ou vendre des biens : \nsi ce n'est pas possible c'est la faillite et c'est perdu !\n"
           "\n"
           "                    ///CHANCE & COMMUNAUTE///\n"
           "\n"
           "Quand un joueur atterrit sur l'une de ces cases, il prend la carte du haut de la pioche indiquee,\n"
           "suit les instructions et retourne la carte face cachee au bas de la pioche. La carte Sortir de prison est conservee \njusqu'a ce qu'elle soit utilisee, puis retournee au fond du paquet.\n"
           "Lorsqu'un joueur atterrit sur Impôt sur le revenu, il doit payer l'impot de 200 euros a la Banque.\n"
           "\n"
           "                    ///LA PRISON///\n"
           "\n"
           "Un joueur atterrit en prison quand :\n"
           "    1. Son jeton atterrit dans l'espace marque ALLER EN PRISON\n"
           "    2. Il tire une carte marquee ALLER EN PRISON\n"
           "    3. Il lance trois fois de suite des doubles.\n"
           "Lorsqu'un joueur est envoye en prison, il ne peut pas recevoir 200 euros de salaire pour ce coup car,\n"
           "peu importe ou se trouve son jeton sur le plateau, il doit le deplacer directement en prison.\n"
           "Son tour se termine lorsqu'il est envoye en prison. Si un joueur n'est pas envoye en prison \nmais qu'il atterrit dans le cours normal du jeu sur cet case,\n"
           "Il est juste En visite, n'encourt aucune penalite, et avance de la maniere habituelle sur son prochain jet.\n"
           "Un joueur sort de prison lorsqu'il :\n"
           "    1. Lance des doubles sur l'un de ses trois tours suivants, s'il reussit a le faire,\n"
           "Il avance immediatement le nombre d'espaces indiques par son double, meme s'il a lance des doubles, \nil ne prend pas un autre tour\n"
           "    2. Utilise la carte Sortir de prison gratuitement s'il en a une\n"
           "    3. Achete la carte Sortir de prison gratuitement d'un autre joueur et la joue\n"
           "    4. Payer une amende de 50 euros avant de lancer les des lors de l'un ou l'autre de ses deux tours suivants.\n"
           "    5. Si le joueur ne lance pas le double a son troisieme tour, il doit payer l'amende de 50 euros.\n"
           "Il sort alors de prison et avance immediatement le nombre de cases indiquees par son jet.\n"
           "Meme s'il est en prison, un joueur peut encore acheter, vendre ou hypothequer une propriete, \nacheter ou vendre des maisons et des hotels, faire des echanges et percevoir des loyers.\n"
           "\n"
           "                    ///STATIONNEMENT GRATUIT///\n"
           "\n"
           "Un joueur qui atterrit sur Stationnement gratuit ne recoit pas d'argent, \nde biens ou de recompenses de quelque nature que ce soit. Ce n'est qu'un lieu de repos libre.\n"
           "\n"
           "                    ///LES MAISONS///\n"
           "\n"
           "Une maison peut etre achete sur n'importe quel case propriete possedee. S'il achete une maison, \nil peut la mettre sur la propriete ou il est.\n"
           "Le prix que le joueur doit payer a la Banque pour chaque maison est indique sur sa carte de titre de propriete \npour la propriete sur laquelle il erige la maison.\n"
           "Le proprietaire peut toujours percevoir un double loyer s'il possede tout un groupe de proprietes.\n"
           "Quand un joueur a quatre maisons sur une propriete, il peut acheter un hotel a la Banque et l'eriger \nsur cette propriete.\n"
           "\n"
           "                    ///LES HOTELS///\n"
           "\n"
           "Il rend les quatre maisons de cette propriete a la Banque et paie le prix de l'hotel tel qu'indique sur \nla carte de titre de propriete.\n"
           "Un seul hotel peut etre erige sur une meme propriete.\n"
           "\n"
           "                    ///PENURIE DE BATIMENTS///\n"
           "\n"
           "Lorsque la Banque n'a pas de maisons a vendre, les joueurs souhaitant construire doivent attendre \nqu'un autre joueur vende ses maisons a la Banque avant de construire.\n"
           "\n"
           ""
           "                    ///VENDRE/NEGOCIER UN BIEN IMMOBILIER///\n"
           "\n"
           "Les maisons et les hotels peuvent etre revendus a la Banque a tout moment pour la moitie du prix paye.\n"
           "Les hotels peuvent etre vendus en une seule fois. Ou bien ils peuvent etre vendus une maison a la fois \n(un hotel equivaut a cinq maisons), de maniere egale, a l'inverse de la maniere dont ils ont ete eriges.\n"
           "\n"
           "                    ///HYPOTEQUES///\n"
           "\n"
           "Les proprietes non ameliorees peuvent etre hypothequees par l'entremise de la Banque en tout temps.\n"
           "Avant qu'une propriete amelioree puisse etre hypothequee, tous les batiments sur toutes les proprietes \nde son groupe de couleur doivent etre revendus a la Banque a moitie prix.\n"
           "La valeur de l'hypotheque est imprimee sur chaque carte de titre de propriete.\n"
           "Aucun loyer ne peut etre percu sur les proprietes hypothequees ou les services publics, mais le loyer \npeut etre percu sur les proprietes non hypothequees du meme groupe de couleur.\n"
           "Afin de lever l'hypotheque, le proprietaire doit payer a la Banque le montant de l'hypotheque majore \nd'un interet de 10 pourcent .\n"
           "Toutefois, le proprietaire peut vendre ou echanger cette propriete hypothequee a un autre joueur a \nn'importe quel prix convenu.\n"
           "Le nouveau proprietaire peut lever l'hypotheque immediatement, s'il le desire, en remboursant \nl'hypotheque plus 10 pourcent d'interets a la Banque.\n"
           "S'il ne resilie pas l'hypotheque immediatement, il doit payer a la banque un interet de 10 pourcent\n lorsqu'il achete/recoit la propriete hypothequee, et s'il leve l'hypotheque plus tard, \nil doit payer a la Banque un interet additionnel de 10 pourcent ainsi que le montant de l'hypotheque.\n"
           "\n"
           "                ///FAILLITE///\n"
           "\n"
           "Un joueur est en faillite lorsqu'il doit plus qu'il ne peut payer a un autre joueur ou a la Banque. \nSi sa dette est envers un autre joueur, il doit remettre a ce joueur tout ce qu'il a de valeur \net se retirer du jeu.\n"
           "Dans le cadre de ce reglement, s'il est proprietaire de maisons ou d'hotels, il doit les restituer a \nla Banque en echange d'argent a hauteur de la moitie du montant paye et cet argent est remis au creancier.\n"
           "S'il a hypotheque un bien, il remet egalement son bien a ce creancier, mais le nouveau proprietaire \ndoit payer immediatement à la Banque le montant des interets sur le pret, soit 10 pourcent de la valeur du bien.\n"
           "Une fois que le nouveau proprietaire l'a fait, il peut, a son gre, payer le capital ou detenir la \npropriete jusqu'a une date ulterieure a laquelle il peut resilier l'hypotheque.\n"
           "S'il detient des biens de cette facon jusqu'a un tour ulterieur, il doit payer les interets a nouveau \nlorsqu'il leve l'hypotheque.\n"
           "Si un joueur doit a la Banque, au lieu d'un autre joueur, plus que ce qu'il peut payer \n(en raison de taxes ou de penalites), meme en vendant ses batiments, en hypothequant sa propriete ou en vendant \nou en echangeant avec d'autres joueurs, il doit remettre tous ses biens a la Banque.\n"
           "Un joueur devant payer plus qu'il n'a de liquide lorsque ce n'est pas son tour sera elimine meme s'il \n"
           "avait assez en vendant des biens(les sommes a payer durant les tours des autres etant assez faible, \n"
           "il est mieux de faire ainsi pour eviter que tout le monde joue durant le tour de quelqu'un d'autre \n"
           "ou que l'on est pas remarque c'etait a vous de jouer)\n"
           "\n"
           "                ///DIVERS///\n"
           "\n"
           "La Banque ne peut preter de l'argent a un joueur qu'en hypothequant un bien immobilier. Aucun joueur ne \npeut emprunter a ou preter de l'argent a un autre joueur.\n"
           "Voici une case type du plateau :\n"
           " ---------------------------------------------------------------------------------------------------------------------\n"
           "|                                Groupe de la propriete OU nom de la case                                             |\n"
           "|                                                                                                                     |\n"
           "|                                Numero des joueurs presents sur cette case                                           |\n"
           "|                                                                                                                     |\n"
           "| Prix de la propriete OU Numero du joueur a qui elle appartient et son nombre de maison(s)/hotel OU le nom de la case|\n"
           " ---------------------------------------------------------------------------------------------------------------------\n");
}

void parcourTableau(unsigned int tableau[8], int tailleLogiqueTableau, int** position, int numeroCase)
{
    int tailleLogiquePosition = 1;

    if (tableau == NULL){printf("ERROR : tableau de position pointe sur NULL\n");return;}

    free(*position);
    (*position) = NULL;
    (*position) = (int*) calloc(1, sizeof(int)); //1ere case = tailleLogique-1 et la suite = joueur qui se trouve sur la case nombre
    (*position)[0] = 1;

    for (int i=0 ; i < tailleLogiqueTableau ; i++)
    {
        if (tableau[i] == numeroCase)
        {
            (*position) = realloc((*position), (1 + tailleLogiquePosition) * sizeof(int));
            tailleLogiquePosition += 1;
            (*position)[0] = tailleLogiquePosition;
            (*position)[tailleLogiquePosition-1] = i;
        }
    }
}


void affichageJoueur(dataPartie partie, unsigned int positionDeTous[8], int numeroCase)
{
    int compteurNombreJoueur = 0;
    int* quelJoueur = NULL;
    parcourTableau(positionDeTous, partie.donnesDeLaPartie.nombreJoueur, &quelJoueur, numeroCase);
    if (quelJoueur[0] > 0)
    {
        for (int j = 1 ; j < quelJoueur[0] ; j++)
        {
            if (partie.listeJoueur[quelJoueur[j]].etat != -1)
            {
                printf(" %d", quelJoueur[j]+1);
            }
            else
            {
                compteurNombreJoueur ++;
            }
        }
        for (int j = 0 ; j < 12-2*quelJoueur[0]+2*compteurNombreJoueur ; j++)
        {
            printf(" ");
        }
    }
    else
    {
        printf("          ");
    }
}


void affichageStatsJoueur(dataPartie partie, int numeroJoueur)
{
    if ( partie.donnesDeLaPartie.nombreJoueur>numeroJoueur && (partie.listeJoueur[numeroJoueur].etat != -1 && partie.listeJoueur[numeroJoueur].argent <= 999))
    {
        printf("         %d/%s :  %d euros / %d carte sortie de prison", numeroJoueur+1, partie.listeJoueur[numeroJoueur].nom, partie.listeJoueur[numeroJoueur].argent, partie.listeJoueur[numeroJoueur].carteSortiePrisonCommunaute + partie.listeJoueur[numeroJoueur].carteSortiePrisonChance);
        for (int i = 1 ; i < 26 - strlen(partie.listeJoueur[numeroJoueur].nom); i++)
        {
            printf(" ");
        }
    }
    else if (partie.donnesDeLaPartie.nombreJoueur>numeroJoueur && (partie.listeJoueur[numeroJoueur].etat != -1 && partie.listeJoueur[numeroJoueur].argent > 999))
    {
        printf("         %d/%s : %d euros / %d carte sortie de prison", numeroJoueur+1, partie.listeJoueur[numeroJoueur].nom, partie.listeJoueur[numeroJoueur].argent, partie.listeJoueur[numeroJoueur].carteSortiePrisonCommunaute + partie.listeJoueur[numeroJoueur].carteSortiePrisonChance);
        for (int i = 1 ; i < 26 - strlen(partie.listeJoueur[numeroJoueur].nom); i++)
        {
            printf(" ");
        }
    }
    else
    {
        printf("                                                                            ");
    }
}


void affichagePrixOuProprietaire(dataPartie partie, int numeroPropriete, int quelPropriete)
{
    if (partie.listePropriete[numeroPropriete].numeroProprietaire == -1)
    {
        if (partie.listePropriete[numeroPropriete].prixAchat > 99)
        {
            printf(" %d euros", partie.listePropriete[numeroPropriete].prixAchat);
        }
        else
        {
            printf("  %d euros", partie.listePropriete[numeroPropriete].prixAchat);
        }
    }
    else
    {
        if (partie.listeCase[partie.listePropriete[numeroPropriete].numeroCaseDesProprieteDeCetteCouleur[quelPropriete]].etat == 2)
        {
            printf("  %d / Hypo", partie.listePropriete[numeroPropriete].numeroProprietaire+1);
        }
        else if (partie.listePropriete[numeroPropriete].nombreHotel == 0)
        {
            printf("  %d / %dM  ", partie.listePropriete[numeroPropriete].numeroProprietaire+1, partie.listePropriete[numeroPropriete].nombreMaison);
        }
        else
        {
            printf("  %d / %dH  ", partie.listePropriete[numeroPropriete].numeroProprietaire+1, partie.listePropriete[numeroPropriete].nombreHotel);
        }
    }
}




void affichagePlateau(dataPartie partie)
{
    unsigned int positionDeTous[8];
    int* quelJoueur = NULL;
    int compteurNombreJoueur = 0;;

    for (int i = 0 ; i < partie.donnesDeLaPartie.nombreJoueur ; i++)
    {
        positionDeTous[i] = partie.listeJoueur[i].position;
    }



    //Affichage 1ère ligne
    printf(" ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------\n");

    //Affichage 2ème ligne
    printf("|   Parc   |    5     |   Taxe   |    5     |   Gare   |    6     | Caisse de|    6     |  ALLLER  |  maisons dispo :%d\n", partie.donnesDeLaPartie.nombreMaison);

    //Affichage 3ème ligne
    printf("|");
    affichageJoueur(partie, positionDeTous, 16);
    printf("|");
    affichageJoueur(partie, positionDeTous, 17);
    printf("|");
    affichageJoueur(partie, positionDeTous, 18);
    printf("|");
    affichageJoueur(partie, positionDeTous, 19);
    printf("|");
    affichageJoueur(partie, positionDeTous, 20);
    printf("|");
    affichageJoueur(partie, positionDeTous, 21);
    printf("|");
    affichageJoueur(partie, positionDeTous, 22);
    printf("|");
    affichageJoueur(partie, positionDeTous, 23);
    printf("|    EN    |  Hotels dispo : %d\n", partie.donnesDeLaPartie.nombreHotel);

    //Affichage 4ème ligne
    printf("| GRATUIT  |");
    affichagePrixOuProprietaire(partie, 8, 0);
    printf ("| 200 euros|");
    affichagePrixOuProprietaire(partie, 9, 1);
    printf("|          |");
    affichagePrixOuProprietaire(partie, 10, 0);
    printf("|Communaute|");
    affichagePrixOuProprietaire(partie, 11, 1);
    printf("|  PRISON  |\n");

    //Affichage 5ème ligne
    printf(" ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------\n");

    //Affichage 6ème ligne
    printf("|    4     |                                                                            |    7     |\n");

    //Affichage 7ème ligne
    printf("|");
    affichageJoueur(partie, positionDeTous, 15);
    printf("|");
    affichageStatsJoueur(partie, 0);
    printf("|");
    affichageJoueur(partie, positionDeTous, 25);
    printf("|\n");

    //Affichage 8ème ligne
    printf("|");
    affichagePrixOuProprietaire(partie, 7, 1);
    printf("|                                                                            |");
    affichagePrixOuProprietaire(partie, 12, 0);
    printf("|\n");

    //Affichage 9ème ligne
    printf(" ----------                                                                              ----------\n");

    //Affichage 10ème ligne
    printf("|  Carte   |                                                                            |  Bonus   |\n");

    //Affichage 11ème ligne
    printf("|");
    affichageJoueur(partie, positionDeTous, 14);
    printf("|");
    affichageStatsJoueur(partie, 1);
    printf("|");
    affichageJoueur(partie, positionDeTous, 26);
    printf("|\n");

    //Affichage 12ème ligne
    printf("|  Chance  |                                                                            | 50 euros |\n");

    //Affichage 13ème ligne
    printf(" ----------                                                                              ----------\n");

    //Affichage 14ème ligne
    printf("|    4     |                                                                            |    7     |\n");

    //Affichage 15ème ligne
    printf("|");
    affichageJoueur(partie, positionDeTous, 13);
    printf("|");
    affichageStatsJoueur(partie, 2);
    printf("|");
    affichageJoueur(partie, positionDeTous, 27);
    printf("|\n");

    //Affichage 16ème ligne
    printf("|");
    affichagePrixOuProprietaire(partie, 6, 0);
    printf("|                                                                            |");
    affichagePrixOuProprietaire(partie, 13, 1);
    printf("|\n");

    //Affichage 17ème ligne
    printf(" ----------                                                                              ----------\n");

    //Affichage 18ème ligne
    printf("|   Gare   |                                                                            |   Gare   |\n");

    //Affichage 19ème ligne
    printf("|");
    affichageJoueur(partie, positionDeTous, 12);
    printf("|");
    affichageStatsJoueur(partie, 3);
    printf("|");
    affichageJoueur(partie, positionDeTous, 28);
    printf("|\n");

    //Affichage 20ème ligne
    printf("|          |                                                                            |          |\n");

    //Affichage 21ème ligne
    printf(" ----------                                                                              ----------\n");

    //Affichage 22ème ligne
    printf("|    3     |                                                                            |    8     |\n");

    //Affichage 23ème ligne
    printf("|");
    affichageJoueur(partie, positionDeTous, 11);
    printf("|");
    affichageStatsJoueur(partie, 4);
    printf("|");
    affichageJoueur(partie, positionDeTous, 29);
    printf("|\n");

    //Affichage 24ème ligne
    printf("|");
    affichagePrixOuProprietaire(partie, 5, 1);
    printf("|                                                                            |");
    affichagePrixOuProprietaire(partie, 14, 0);
    printf("|\n");

    //Affichage 25ème ligne
    printf(" ----------                                                                              ----------\n");

    //Affichage 26ème ligne
    printf("|  Impot   |                                                                            |  Carte   |\n");

    //Affichage 27ème ligne
    printf("|");
    affichageJoueur(partie, positionDeTous, 10);
    printf("|");
    affichageStatsJoueur(partie, 5);
    printf("|");
    affichageJoueur(partie, positionDeTous, 30);
    printf("|\n");

    //Affichage 28ème ligne
    printf("| 100 euros|                                                                            |  Chance  |\n");

    //Affichage 29ème ligne
    printf(" ----------                                                                              ----------\n");

    //Affichage 30ème ligne
    printf("|    3     |");
    affichageStatsJoueur(partie, 6);
    printf("|    8     |\n");

    //Affichage 31ème ligne
    printf("|");
    affichageJoueur(partie, positionDeTous, 9);
    printf("|                                                                            |");
    affichageJoueur(partie, positionDeTous, 31);
    printf("|\n");

    //Affichage 32ème ligne
    printf("|");
    affichagePrixOuProprietaire(partie, 4, 0);
    printf("|");
    affichageStatsJoueur(partie, 7);
    printf("|");
    affichagePrixOuProprietaire(partie, 15, 1);
    printf("|\n");

    //Affichage 33ème ligne
    printf(" ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------\n");

    //Affichage 34ème ligne
    printf("|  |");
    compteurNombreJoueur = 0;                                                                     //affichage Prison
    for (int joueur = 0; joueur < partie.donnesDeLaPartie.nombreJoueur ; joueur ++)
    {
        if (partie.listeJoueur[joueur].etat >=1 && partie.listeJoueur[joueur].etat <=3)
        {
            printf("%d", joueur+1);
            compteurNombreJoueur++;
        }
    }
    for (int j = 0 ; j < 7-compteurNombreJoueur ; j++)
    {
        printf(" ");
    }
    printf("|    2     | Caisse de|    2     |   Gare   |    1     |   Taxe   |    1     |   Case   |\n");

    //Affichage 35ème ligne
    printf("|  |_______|");
    affichageJoueur(partie, positionDeTous, 7);
    printf("|");
    affichageJoueur(partie, positionDeTous, 6);
    printf("|");
    affichageJoueur(partie, positionDeTous, 5);
    printf("|");
    affichageJoueur(partie, positionDeTous, 4);
    printf("|");
    affichageJoueur(partie, positionDeTous, 3);
    printf("|");
    affichageJoueur(partie, positionDeTous, 2);
    printf("|");
    affichageJoueur(partie, positionDeTous, 1);
    printf("|");
    affichageJoueur(partie, positionDeTous, 0);
    printf("|\n");

    //Affichage 36ème ligne
    printf("|");
    compteurNombreJoueur = 0;                                                                         //Affichage joueur en visite de la prison
    parcourTableau(positionDeTous, partie.donnesDeLaPartie.nombreJoueur, &quelJoueur, 8);
    if (quelJoueur[0] > 0)
    {
        for (int j = 1 ; j < quelJoueur[0] ; j++)
        {
            if (partie.listeJoueur[quelJoueur[j]].etat > 3)
            {
                printf(" %d", quelJoueur[j] + 1);
                compteurNombreJoueur++;
            }
        }
        for (int j = 0 ; j < 10-2*compteurNombreJoueur ; j++)
        {
            printf(" ");
        }
    }
    else
    {
        printf("          ");
    }
    printf("|");
    affichagePrixOuProprietaire(partie, 3, 1);
    printf("|Communaute|");
    affichagePrixOuProprietaire(partie, 2, 0);
    printf("|          |");
    affichagePrixOuProprietaire(partie, 1, 1);
    printf("| 100 euros|");
    affichagePrixOuProprietaire(partie, 0, 0);
    printf("|  Depart  |\n");

    //Affichage 37ème ligne
    printf(" ---------  ---------- ---------- ---------- ---------- ---------- ---------- ---------- ----------\n");


    free(quelJoueur);
    quelJoueur = NULL;
}










