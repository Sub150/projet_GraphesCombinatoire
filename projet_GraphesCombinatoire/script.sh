#!/bin/bash
date
echo "Compilation..." ;

gcc -c liste_entier_cout.c -Wall
gcc -c main.c -Wall
gcc -c algorithmes.c -Wall
gcc -c lecture_donnees.c -Wall
gcc -o main main.o liste_entier_cout.o algorithmes.o lecture_donnees.o

echo "Fini" ;
