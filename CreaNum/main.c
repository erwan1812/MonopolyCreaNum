#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "partie.h"
#include "fonctions.h"
#include "affichage.h"
#include "structures.h"



int main() {
    int choixMenu = 0;

    dataPartie dataPartie1;
    initDataPartie(&dataPartie1);

    srand(time(NULL));

    do {
        affichageMenuPrincipal();
        choixMenu = saisirEntier();
        switch (choixMenu)
        {
            case 1 :
                if (dataPartie1.listePropriete == NULL)
                {
                    dataPartie1 = creePartie();
                }
                else
                {
                    bouclePartie(&dataPartie1);
                }
                break;

            case 2 :
                sauvegardeToiDansUnFichierBinaire(&dataPartie1);
                break;
            case 3 :
                chargeToiBinaire(&dataPartie1);
                break;
            case 4 :
                affichageRegles();
                break;
            case 5 :
                affichageNomEquipeProjet();
                break;
            case 6 :
                libererTout(&dataPartie1);
                printf("\nA bientot !\n");
                break;
            default :
                saisitInvalide();
                break;
        }
    }while (choixMenu != 6);

    return(0);
}
