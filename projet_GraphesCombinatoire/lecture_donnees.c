#include "lecture_donnees.h"
#include <stdio.h>
#include <stdlib.h>

void lecture_client(int *nb_client)
{
    scanf("%d",nb_client);
}

void lecture_quantite(int *Q)
{
    scanf("%d",Q);
}

void lecture_demandes(int nb_client,int *q)
{
    for(int i=0;i<nb_client;i++)
    {
        scanf("%d",&q[i]);
    }
}

double** lecture_matrice(int nb_client)
{
    /*_______________________________________________________________________________________________________________*/
    //Déclaration dynamique et lecture de notre graphe//
    //------------------------------------------------//
    double **matrice_adjacence;
    matrice_adjacence = (double**)malloc((nb_client+1)*sizeof(double*));

    for(int i = 0;i<=nb_client;i++)
    {
        matrice_adjacence[i] = (double*)malloc((nb_client+1)*sizeof(double));
        for(int j = 0;j<=nb_client;j++)
        {
            scanf("%lf",&matrice_adjacence[i][j]);
        }
    }
    /*_______________________________________________________________________________________________________________*/
    return matrice_adjacence;
}

void affichage_info(int nb_client,int Q,int *q,double **matrice_adjacence)
{
    printf("Nombre de clients: %d\nCapacité des camions: %d\n",nb_client,Q);
}







