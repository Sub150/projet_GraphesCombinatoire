#include <stdio.h>
#include <stdlib.h>
#include "liste_entier_cout.h"
#define NIL (struct Maillon_Entier_Cout*)0

void init_Liste_Entier_Cout (struct Liste_Entier_Cout * L)
{   L->tete = NIL;
    L->queue = NIL;
    L->nbelem = 0;
}

void ajouter_en_queue_Liste_Entier_Cout (struct Liste_Entier_Cout * L, double cost, int client)
{   struct Maillon_Entier_Cout* M;
    struct Maillon_Entier_Cout* nouveau;
    
    nouveau = (struct Maillon_Entier_Cout*)malloc(sizeof(struct Maillon_Entier_Cout));
    
    nouveau->value = client ;
    nouveau->suivant = NIL;
    nouveau->cout=cost;
    if ( L->tete == NIL ) {
        L->tete = nouveau;
        L->nbelem += 1;
    }
    else {
        M=L->tete;
        while ( M->suivant != NIL ) {
            M=M->suivant;
        }
    M->suivant = nouveau;
    L->queue = nouveau;
    L->nbelem += 1 ;
    }
}


void clear_liste_Entier_Cout(struct Liste_Entier_Cout* L)
{   struct Maillon_Entier_Cout* courant;
    struct Maillon_Entier_Cout* suivant;

    courant = L->tete;
    for(int i=0; i<L->nbelem;i++)
    {   
        suivant = courant->suivant;
        free (courant);
        courant = suivant;
    }
    
}


void imprimer_Liste_Entier_Cout (struct Liste_Entier_Cout* L)
{   struct Maillon_Entier_Cout* M;
    int i;

    printf ("[");
    M = L->tete;
    for (i = 0; i < L->nbelem; i++)
    {   if (i == 0)
            printf ("%d - %lf", M->value, M->cout);
        else
            printf (", %d - %lf", M->value, M->cout);
        M = M->suivant;
    }
    printf ("]\n");
}

void imprimer_Liste_Entier_Cout_bis (struct Liste_Entier_Cout* L)
{   struct Maillon_Entier_Cout* M;
    int i;

    printf ("[");
    M = L->tete;
    for (i = 0; i < L->nbelem; i++)
    {   if (i == 0)
            printf ("%d ", M->value);
        else
            printf (", %d ", M->value);
        M = M->suivant;
    }
    printf ("]");
}
