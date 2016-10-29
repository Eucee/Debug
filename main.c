#include <stdio.h>
#include <stdlib.h>

/**************************************DEFINITION******************************************/

//Alias
typedef struct TypeCell* TypePtrListe;
typedef struct TypeCell TypeCell;

//Fonction
void afficher_erreur(char typeErreur);
TypePtrListe *creation_elem(int val);
void afficherListe(TypePtrListe *adr_liste);
void ins_en_tete(TypePtrListe *adr_liste, int val);
void ins_pos_k(TypePtrListe *adr_liste, int val, int pos);
void suppr_en_tete(TypePtrListe *adr_liste);


/**************************************FONCTIONS**************************************/

//Alias

struct TypeChaine80{
    char chaineCaratere[80];
};

////////////////////////////////////////////////

typedef struct TypeCell{
    int info;
    TypeCell *suiv;
};


//Fonctions

////////////////////////////////////////////////

void afficher_erreur(char typeErreur){
    printf("Erreur: ");
    switch(typeErreur){
        case 'M':
            printf("allocation memoire.\n");
            break;
        case 'L':
            printf("liste vide.\n");
            break;
        case 'P':
            printf("position erronee.\n");
            break;
    }
}

////////////////////////////////////////////////

TypePtrListe *creation_elem(int val){
    TypePtrListe cell = (TypeCell*) malloc(sizeof(TypeCell));
    cell -> info = val;

    //verification de reussite
    if(cell == NULL){
    afficher_erreur('M');
    return;
    }

    return cell;
}

////////////////////////////////////////////////

void afficherListe(TypePtrListe *adr_liste){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficher_erreur('L');
        return;
    }

    TypePtrListe p = *adr_liste;

    //afficher chaque cellule
    while (p != NULL)
    {
        printf("%d -> ", p->info);
        p = p -> suiv;
    }
    printf("NULL\n"); //marquer la fin de list
}

////////////////////////////////////////////////

void ins_en_tete(TypePtrListe *adr_liste, int val){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficher_erreur('L');
        return;
    }

    // creation du nouvel element
    TypePtrListe p_nouv;
    p_nouv=creation_elem(val);
    // insertion de l'element au debut de la liste
    p_nouv -> suiv = *adr_liste;
    *adr_liste = p_nouv;
}

////////////////////////////////////////////////

void ins_pos_k(TypePtrListe *adr_liste, int val, int k){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficher_erreur('L');
        return;
    }

    //variables
    TypePtrListe p_prec = NULL, p = *adr_liste, p_nouv;
    int i = 1;

    //placement a la bonne position
    while(p != NULL && i < k){
        p_prec = p;
        p = p -> suiv;
        i++;
    }
    if(k==1){ //insertion en debut de liste (cas de liste vide [p == NULL] ET de liste preexistante)
        ins_en_tete(adr_liste, val);
        return;
        }
    if (p == NULL){
        if(k!= i){//k > longueur de la liste
            afficher_erreur('P');
            return;
        }//sinon k>1, insertion en fin de liste
        p_nouv=creation_elem(val);
        p_nouv -> suiv = p_prec -> suiv;
        p_prec -> suiv = p_nouv;
        return;
    }//sinon insertion en milieu de liste
    ins_en_tete(&p_prec -> suiv, val);
}

////////////////////////////////////////////////

void suppr_en_tete(TypePtrListe *adr_liste){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficher_erreur('L');
        return;
    }

    TypePtrListe p = *adr_liste;
    *adr_liste = p -> suiv;
    free(p);
}

////////////////////////////////////////////////

void suppr_pos_k(TypePtrListe *adr_liste, int val, int k){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficher_erreur('L');
        return;
    }

    //variables
    TypePtrListe p_prec = NULL, p = *adr_liste, p_nouv;
    int i = 1;

    while(p != NULL && i < k){
        p_prec = p;
        p = p -> suiv;
        i++;
    }
    if(k==1){ //insertion en debut de liste (cas de liste vide ET de liste preexistante)
        ins_en_tete(adr_liste, val);
        return;
        }//sinon k>1
    if (p == NULL){//k > i (k>longueur de la liste)
            afficher_erreur('P');
            return;
    }//sinon insertion en milieu de liste OU en fin de liste (p == NULL);
    ins_en_tete(&p_prec -> suiv, val);
}


/****************************************CORPS****************************************/

int main()
{
    TypePtrListe *maListe = (TypePtrListe*) malloc(sizeof(TypePtrListe));

    ins_pos_k(maListe, 56, 1);
    afficherListe(maListe);
    ins_pos_k(maListe, 33, 1);
    afficherListe(maListe);
    ins_en_tete(maListe, 1);
    afficherListe(maListe);
    ins_pos_k(maListe, 44, 3);
    afficherListe(maListe);
    ins_en_tete(maListe, 2);
    afficherListe(maListe);
    ins_en_tete(maListe, 3);
    afficherListe(maListe);
    ins_pos_k(maListe, 88, 7);
    afficherListe(maListe);
    ins_pos_k(maListe, 88, 9);
    afficherListe(maListe);
    suppr_en_tete(maListe);
    afficherListe(maListe);

   /* TypePtrListe ptr3 = (TypePtrListe*) malloc(sizeof(TypeCell)), coucou;
    ptr3 -> suiv=NULL;
    ptr3 -> info=13;
    coucou=creation_elem(15);
    printf("%d\n", coucou->info);

    TypePtrListe Liste=NULL;
    //ins_pos_k(maListe, 44, 1);*/

    return 0;
}
