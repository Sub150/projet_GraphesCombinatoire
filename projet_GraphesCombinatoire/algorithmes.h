#if ! defined (ALGORITHMES_H)
#define ALGORITHMES_H 1
#define NIL (struct Maillon_Entier_Cout*)0

/*
 * Fonction tour géant
 * Prend en argument
 */
int* tour_geant(int, double**, int);

/*
 * Fonction SPLIT
 */
struct Liste_Entier_Cout* SPLIT(int*, int, int, double**, int *);

/*
 * Fonction Bellmann (Plus court chemin)
 */
void Bellman (struct Liste_Entier_Cout*,struct Liste_Entier_Cout*,int);

/*
 * Fonction permettant de déterminer le plus court chemin entre le depot et la dernière étape de livraison
 */
struct Liste_Entier_Cout* trajet_camion (struct Liste_Entier_Cout*,int);

/*
 * Fonction permettant de déterminer les clients visités en sens inverse, à partir d'un plus court chemin entre 2 sommets
 */
struct Liste_Entier_Cout* client_camion(struct Liste_Entier_Cout*,int*);


#endif

