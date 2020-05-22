#if ! defined (LISTE_ENTIER_COUT_H)
#define LISTE_ENTIER_COUT_H 1

struct Maillon_Entier_Cout
{   int value;
    struct Maillon_Entier_Cout * suivant;
    double cout;
};

struct Liste_Entier_Cout 
{   struct Maillon_Entier_Cout* tete;
    struct Maillon_Entier_Cout* queue;
    int nbelem;
};




/**********************************************************************
 * PROTOTYPES DES FONCTIONS (TYPE ABSTRAIT)
 **********************************************************************/

/* 
 * Constructeur. Initialise son paramètre à la liste vide 
 */
extern void init_Liste_Entier_Cout (struct Liste_Entier_Cout*);


/* 
 * Destructeur 
 */
extern void clear_liste_Entier_Cout(struct Liste_Entier_Cout*);


/* 
 * Ajout d'un double en queue de liste 
 */
extern void ajouter_en_queue_Liste_Entier_Cout (struct Liste_Entier_Cout*, double, int);


/* 
 * Impression. 
 */
extern void imprimer_Liste_Entier_Cout (struct Liste_Entier_Cout*);

extern void imprimer_Liste_Entier_Cout_bis(struct Liste_Entier_Cout*);



#endif
