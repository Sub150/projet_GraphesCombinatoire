#include <stdio.h>



/**********************************************************************
 * PROTOTYPES DES FONCTIONS (TYPE ABSTRAIT)
 **********************************************************************/


/* 
 * lecture du nombre de client
 */
extern void lecture_client(int *);

/* 
 * lecture de la capacité des camions
 */
extern void lecture_quantite(int*);

/* 
 * lecture des demandes des clients
 */
extern void lecture_demandes(int,int*);

/* 
 * lecture des coûts des trajets
 */
extern double** lecture_matrice(int);

/* 
 * Affichage de différentes infos relatives aux données
 */
extern void affichage_info(int,int,int*,double**);




