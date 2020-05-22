#include<stdio.h>
#include<stdlib.h>
#include "algorithmes.h"
#include "liste_entier_cout.h"
#define INF (double)-1

int* tour_geant(int n, double** graphe, int c)
{

    /*_______________________________________________________________________________________________________________*/
    //Déclaration des structures et variables utilisées dans l'algorithme//
    //-------------------------------------------------------------------//

    int suivant,current,cmp;            //suivant désigne le client suivant, current le client actuel et cmp est un compteur
    double cout;                        //variable permettant de stocker un cout entre 2clients
    int* Mark;                          //Vecteur dynamique permettant de marquer les sommets visités
    Mark= malloc(n*sizeof(int));
    int* T;                             //Vecteur dynamique résultat du Tour géant (liste de client)
    T = malloc(n*sizeof(int));

    /*_______________________________________________________________________________________________________________*/



    /*_______________________________________________________________________________________________________________*/
    //Initialisation//
    //--------------//

    for (int i=0;i<n;i++)
    {
        Mark[i] = 0;
        T[i]=-1;
    }
    T[0]=c;
    Mark[c-1]=1;

    cmp = 1;
    cout = -1;

    current = T[0];
    /*_______________________________________________________________________________________________________________*/


    /*_______________________________________________________________________________________________________________*/
    //Calcul du tour géant//
    //--------------------//

    while(T[n-1]==-1)
    {
        for(int i = 0;i<n;i++)
        {
            if((Mark[i]==0)&&(i+1!=current))
            {
                if((graphe[current][i+1]<cout)||(cout==-1))
                {
                    cout = graphe[current][i+1];
                    suivant = i+1;
                }
            }
        }
        T[cmp] = suivant;
        Mark[suivant-1]=1;
        current = suivant;
        cmp +=1;
        cout = -1;
    }
    /*_______________________________________________________________________________________________________________*/

    free(Mark); //libération de l'espace mémoire alloué

    return T;
}


struct Liste_Entier_Cout* SPLIT(int* T, int Q, int n, double** graphe, int *q ){

    /*_______________________________________________________________________________________________________________*/
    //Déclaration des structures et variables utilisées dans l'algorithme//
    //-------------------------------------------------------------------//
    int load ;                          //Chargement du camion
    int j;                              //Indice de boucle
    double cost;                        //Cout entre 2 client
    struct Liste_Entier_Cout *H;        //Vecteur dynamique de liste: résultat

    //Initialisation du résultat
    H = malloc(n*sizeof(struct Liste_Entier_Cout));
    for(int i =0;i<n;i++)
    {
        H[i].tete = NIL;
        H[i].nbelem = 0;
    }
    /*_______________________________________________________________________________________________________________*/



    /*_______________________________________________________________________________________________________________*/
    //SPLIT//
    //-----//
    for (int i = 1; i<=n ; i++ ){
        j = i;
        load = 0;
        while ( (j<=n) && (load<Q) ){
            load += q[T[j-1]-1];
            if ( i == j ){
                cost = graphe[0][T[i-1]] + graphe[T[i-1]][0];       //T[i-1] car le sommet i est stocké à l'indice i-1
            }
            else
            {
                cost = cost - graphe[T[j-2]][0] + graphe[T[j-2]][T[j-1]] + graphe[T[j-1]][0];
            }
            if ( load <= Q ){
                ajouter_en_queue_Liste_Entier_Cout(&H[i-1], cost, j);  //Ajout du sommet dans le résultat
            }
            j++;
        }
    }

    /*_______________________________________________________________________________________________________________*/
    return H;
}

void Bellman (struct Liste_Entier_Cout* H,struct Liste_Entier_Cout* L,int n)
{
    /*_______________________________________________________________________________________________________________*/
    //Déclaration des structures et variables utilisées dans l'algorithme//
    //-------------------------------------------------------------------//

    int *pere;                          //Vecteur dynamique d'entier: Prédécesseur
    double *cost,inter;                 //cost : vecteur dynamique des coûts entre le sommet d'indice i dans Prédécesseur et le sommet i.
                                        //inter : cout intermédiaire

    cost=malloc((n+1)*sizeof(double));
    pere = malloc((n+1)*sizeof(int));
    struct Maillon_Entier_Cout* M;
    /*_______________________________________________________________________________________________________________*/



    /*_______________________________________________________________________________________________________________*/
    //Initialisation//
    //--------------//

    for(int i =1;i<=n;i++)
    {
        cost[i]=INF;                    //INF représente un cout infini, initialisation de cout
        pere[i]=-1;
    }



    L->tete=0;
    cost[0]=0;
    pere[0]=0;
    /*_______________________________________________________________________________________________________________*/



    /*_______________________________________________________________________________________________________________*/
    //BELLMAN//
    //-------//


    //Détermination des vecteurs des valeurs de pere et cout

    //Parcours de tous les sommets initiaux renvoyée par SPLIT
    for(int i = 0;i<n;i++)
    {
        M=H[i].tete;


        //Parcours des listes renvoyée par SPLIT, les maillons de H[i] représentent les sommets atteignables à partir du sommet de tete de H[i]
        while(M!=NIL)
        {
            inter=cost[i]+M->cout;      //Stockage du cout par aller du sommet précédent au suivant

            if(inter<cost[M->value]||(cost[M->value]==INF))     //Si le coup inter est inférieur au cout précédent pour atteindre le sommet du maillon suivant(sommet) alors on conserve ce cout
            {
                cost[M->value]= inter;
                pere[M->value]=i;
            }
            M=M->suivant;
        }
    }

    //Ajout dans la liste résultat la suite des sommets de père à parcourir avec leur cout minimisé
    for(int i = 0;i<=n;i++)
    {
        ajouter_en_queue_Liste_Entier_Cout(L,cost[i],pere[i]);
    }


    /*__________________________________________________________*/
    //Libération de l'espace mémoire alloué//
    //-------------------------------------//
    free(pere);
    free(cost);
    /*__________________________________________________________*/
}



struct Liste_Entier_Cout* trajet_camion(struct Liste_Entier_Cout* L,int nb_client)
{

    /*_______________________________________________________________________________________________________________*/
    //Déclaration des structures et variables utilisées dans l'algorithme//
    //-------------------------------------------------------------------//

    struct Liste_Entier_Cout* camion;   //Résultat sous forme d'une liste
    struct Maillon_Entier_Cout *M;      //Maillon intermédiaire pour le parcours de liste
    int current,prec;                   //current : étape de livraison(sommet) en cours d'exploration
                                        //prec : étape de livraison(sommet) exploré précédemment
    double cout_prec;                   //cout_prec: cout de l'étape de livraison précédente

    /*_______________________________________________________________________________________________________________*/



    /*_______________________________________________________________________________________________________________*/
    //Initialisation//
    //--------------//
    camion = malloc(sizeof(struct Liste_Entier_Cout));
    init_Liste_Entier_Cout(camion);


    M=L->queue;                          //On se positionne sur le dernier maillon de la liste
    current = M->value;                  //la résolution se fait en partant de la dernièere étape de livraison
    cout_prec = M->cout;
    prec = L->nbelem-1;
    /*_______________________________________________________________________________________________________________*/



    /*_______________________________________________________________________________________________________________*/
    //Résolution//
    //----------//

    while(current!=0)                   //Tant que nous ne sommes pas revenu à l'étape 0, on regarde le n° du maillon
    {                                   //indiqué par le maillon précédent.
        M=L->tete;                      //Exemple: le maillon5 indique que le plus court chemin pour y arriver
        for(int i=0;i<current;i++)      //est de passer par l'étape3. Le maillon trois indique que le plus court
        {                               //chemin pour y arriver est l'étape0.
            M=M->suivant;
        }
        ajouter_en_queue_Liste_Entier_Cout(camion,cout_prec-M->cout,prec);  //ajout du maillon précédent au résultat
        prec = current;
        cout_prec = M->cout;
        current = M->value;
    }


    ajouter_en_queue_Liste_Entier_Cout(camion,M->cout,prec);    //Ajout du dernier maillon à la liste

    return camion;
}


struct Liste_Entier_Cout* client_camion(struct Liste_Entier_Cout* PCC,int* Tour_geant)
{
    /*_______________________________________________________________________________________________________________*/
    //Déclaration des structures et variables utilisées dans l'algorithme//
    //-------------------------------------------------------------------//

    struct Maillon_Entier_Cout *M;      //Maillon intermédiaire pour le parcours de liste
    struct Liste_Entier_Cout *res ;     //résultat : vecteur dynamique de Listes d'entier/cout
    int etape_cur,etape_next;           //permet de stocker les sommets en cours d'exploration et le sommet suivant
    double cost;                        //stocke le cout entre 2 sommets
    int num_camion=0;                   //compteur du nombre de camion

    /*_______________________________________________________________________________________________________________*/



    /*_______________________________________________________________________________________________________________*/
    //Initialisation//
    //--------------//
    res = malloc((PCC->nbelem)*sizeof(struct Liste_Entier_Cout));
    for(int i =0;i<PCC->nbelem;i++)
    {
        init_Liste_Entier_Cout(&res[i]);
    }

    M = PCC->tete;
    /*_______________________________________________________________________________________________________________*/




    /*_______________________________________________________________________________________________________________*/
    //Résolution//
    //----------//

    while(M !=NIL)                              //Permet d'ajouter les sommets compris entre les indices [a,b[ dans
    {                                           // le tour géant correspondent au chemin de livraison d'un camion.
        etape_cur = M->value;                   //a correspond au sommet du Maillon courrant(etape_cur) et b
        cost = M->cout;                         //correspond au Maillon suivant(etape_next).
        if(M->suivant !=NIL)
        {
            etape_next=M->suivant->value;
        }
        else
        {
            etape_next=0;
        }
        if (etape_cur-etape_next>1)             //Si il n'y a pas plus d'1 sommet entre a et b, alors on insère simplement
        {                                       //le sommet "a"(etape_cur) au résultat
            for(int i = etape_cur;i>etape_next;i--)
            {
                ajouter_en_queue_Liste_Entier_Cout(&res[num_camion],cost,Tour_geant[i-1]);
            }
            num_camion++;
        }
        else
        {
            ajouter_en_queue_Liste_Entier_Cout(&res[num_camion],cost,Tour_geant[etape_cur-1]);
            num_camion++;
        }
        M = M->suivant;
    }
    /*_______________________________________________________________________________________________________________*/

    return res;
}




