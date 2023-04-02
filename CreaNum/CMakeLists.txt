cmake_minimum_required(VERSION 3.20)
project(Monopoly C)

set(CMAKE_C_STANDARD 99)

add_executable(Monopoly main.c fonctions.c fonctions.h affichage.c affichage.h structures.h partie.c partie.h chanceEtCaisse.c chanceEtCaisse.h initProprietes.c initProprietes.h)
