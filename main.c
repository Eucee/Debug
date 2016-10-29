#include <stdio.h>
#include <stdlib.h>
//Alias
typedef struct TypeCell* TypePtrListe;
typedef struct TypeCell TypeCell;

//Fonction
void afficher_erreur(char typeErreur);
TypePtrListe *creation_elem(int val);
void afficherListe(TypePtrListe *adr_liste);
void inserer_en_tete(TypePtrListe *adr_liste, int val);
void inserer_pos_k(TypePtrListe *adr_liste, int val, int pos);
void supprimer_en_tete(TypePtrListe *adr_liste);


/**************************************FONCTIONS**************************************/

//Alias

struct TypeChaine80{
    char chaineCaratere[80];
};


typedef struct TypeCell{
    int info;
    TypeCell *suiv;
};
/*
void afficher_erreur(char typeErreur){
    printf("Erreur: ");
    switch(typeErreur){
        case 'M':
            printf("allocation memoire\n");
            break;
        case 'L':
            printf("liste vide\n");
            break;
        case 'P':
            printf("position erronee\n");
            break;
    }
}*/

TypePtrListe *creation_elem(int val){
TypePtrListe cell = (TypeCell*) malloc(sizeof(TypeCell));
    cell->info = val;

    /*if(cell == NULL){
    afficher_erreur('M');
    return;
    }*/

    return cell;
}

void afficherListe(TypePtrListe *adr_liste){
    /*if (adr_liste == NULL)
    {
        afficher_erreur('L');
        return;
    }*/
    TypePtrListe p = *adr_liste;

    while (p != NULL)
    {
        printf("%d -> ", p->info);
        p = p->suiv;
    }
    printf("NULL\n");
}


void inserer_en_tete(TypePtrListe *adr_liste, int val){

    // creation du nouvel element
    TypePtrListe p_nouv;
    p_nouv=creation_elem(val);
    // insertion de l'element au debut de la liste
    p_nouv -> suiv = *adr_liste;
    *adr_liste = p_nouv;
}

void supprimer_en_tete(TypePtrListe *adr_liste){

    /*if (adr_liste == NULL)
    {
        afficher_erreur('L');
        return;
    }*/

    TypePtrListe p = *adr_liste;
    *adr_liste = p->suiv;
    free(p);
}

int main()
{
TypePtrListe *maListe = malloc(sizeof(TypePtrListe));
inserer_en_tete(maListe, 1);
inserer_en_tete(maListe, 2);
inserer_en_tete(maListe, 3);
supprimer_en_tete(maListe);
afficherListe(maListe);

TypePtrListe ptr3=(TypePtrListe*) malloc(sizeof(TypeCell)), coucou;
ptr3->suiv=NULL;
ptr3 -> info=13;
coucou=creation_elem(15);


    printf("%d", coucou->info);
    return 0;
}
