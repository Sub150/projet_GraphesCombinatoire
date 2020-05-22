#include <stdio.h>
#include <stdlib.h>
#include "liste_entier_cout.h"
#include "lecture_donnees.h"
#include "algorithmes.h"

int main(){
    
    /*_______________________________________________________________________________________________________________*/
    //Déclaration des structures utilisées dans les algorithmes//
    //---------------------------------------------------------//
    int* T;                             //Résultat du Tour Géant
    struct Liste_Entier_Cout* H;        //Résultat de SPLIT
    struct Liste_Entier_Cout* L;        //Résultat de Bellman
    struct Liste_Entier_Cout* trajet;   //Liste des trajets de chaque camion
    struct Liste_Entier_Cout* camion;   //Plus court du chemin pour aller à la dernière étape de livraison
    /*_______________________________________________________________________________________________________________*/
    
    
    
    /*_______________________________________________________________________________________________________________*/
    //Allocation de la mémoire et initialisation de la donnée/résultat pour l'algorithme de Bellman//
    //---------------------------------------------------------------------------------------------//
    
    L = malloc(sizeof(struct Liste_Entier_Cout));
    init_Liste_Entier_Cout(L);
    /*_______________________________________________________________________________________________________________*/
    
    
    
    /*_______________________________________________________________________________________________________________*/
    //Lecture des données//
    //-------------------//
    
    int nb_client,Q;
    lecture_client(&nb_client);
    lecture_quantite(&Q);
    int q[nb_client];
    lecture_demandes(nb_client,q);
    double **matrice_adjacence;         //Graphe
    matrice_adjacence=lecture_matrice(nb_client);
    affichage_info(nb_client,Q,q,matrice_adjacence);

    /*_______________________________________________________________________________________________________________*/

    
    
    /*_______________________________________________________________________________________________________________*/
    //Applications des différents algorithmes//
    //---------------------------------------//
    
    T=tour_geant(nb_client,matrice_adjacence,1);
    H=SPLIT(T, Q,nb_client,matrice_adjacence,q);
    Bellman(H,L,nb_client);
    camion = trajet_camion(L,nb_client);
    trajet = client_camion(camion,T);
    /*_______________________________________________________________________________________________________________*/
    
    
    /*_______________________________________________________________________________________________________________*/
    //Affichage des résultats//
    //---------------------------------------//
    
    printf("Nombre de trajets ( camions ) : %d\n", camion->nbelem);
    printf("Cout total : %lf\n\n",L->queue->cout);
    int som_client=0;
    for(int i=0;i<camion->nbelem;i++)
    {
        printf("Camion n°%d => %d clients\n",i+1,trajet[i].nbelem);
        som_client += trajet[i].nbelem;
        imprimer_Liste_Entier_Cout_bis(&trajet[i]);
        printf("--Cout:%lf--\n\n",trajet[i].tete->cout);
    }
    printf("%d clients livrés\n",som_client);
    
    /*_______________________________________________________________________________________________________________*/

    
    
    
    /*__________________________________________________________*/
    //Libération de l'espace mémoire alloué//
    //-------------------------------------//
    
    clear_liste_Entier_Cout(L);
    free(L);
    int nb_camion = camion->nbelem;
    for(int i=0; i<nb_client;i++)
    {
        clear_liste_Entier_Cout(&H[i]);
    }
    free(H);
    for(int i=0; i<nb_camion;i++)
    {
        clear_liste_Entier_Cout(&trajet[i]);
    }
    free(trajet);
    for(int i=0;i<=nb_client;i++)
    {
        free(matrice_adjacence[i]);
    }
    free(matrice_adjacence);
    clear_liste_Entier_Cout(camion);
    free(camion);
    free(T);
    /*__________________________________________________________*/
    
    
    printf("\n--Fin--\n");
    
    return 0;
}
