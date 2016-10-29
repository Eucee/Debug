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
void ins_en_tete(TypePtrListe *adr_liste, int val, char bool_affiche);
void ins_pos_k(TypePtrListe *adr_liste, int val, int pos, char bool_affiche);
void suppr_en_tete(TypePtrListe *adr_liste, char bool_affiche);
void suppr_pos_k(TypePtrListe *adr_liste, int k, char bool_affiche);
void accesVal(TypePtrListe *adr_liste, int val, TypePtrListe *adr_ptrCell);


/**************************************FONCTIONS**************************************/

//Alias

struct TypeChaine80{
    char chaineCaratere[80];
};

////////////////////////////////////////////////

typedef struct TypeCell{
    int info;
    TypePtrListe suiv;
};




//Fonctions

////////////////////////////////////////////////

void afficher_erreur(char typeErreur){
    printf("Erreur: ");
    switch(typeErreur){
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
    exit(1);
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
    printf("NULL\n"); //marquer la fin de liste
}

////////////////////////////////////////////////

void ins_en_tete(TypePtrListe *adr_liste, int val, char bool_affiche){

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

    if (bool_affiche=='T') afficherListe(adr_liste);
}

////////////////////////////////////////////////

void ins_pos_k(TypePtrListe *adr_liste, int val, int k, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficher_erreur('L');
        return;
    }

    //variables
    TypePtrListe p_prec = NULL, p = *adr_liste;
    int i = 1;

    //placement a la bonne position
    while(p != NULL && i < k){
        p_prec = p;
        p = p -> suiv;
        i++;
    }
    if(k==1){ //insertion en debut de liste (cas de liste vide [p == NULL] ET de liste preexistante)
        ins_en_tete(adr_liste, val, bool_affiche);
        return;
        }//sinon k>1
    if (p == NULL && k!= i){//k > i (k>longueur de la liste)
            afficher_erreur('P');
            return;
    }//sinon insertion en milieu de liste OU en fin de liste (p == NULL);
    ins_en_tete(&p_prec -> suiv, val, bool_affiche);
}

////////////////////////////////////////////////

void suppr_en_tete(TypePtrListe *adr_liste, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficher_erreur('L');
        return;
    }

    //raccordements
    TypePtrListe p = *adr_liste;
    *adr_liste = p -> suiv;

    free(p); //supression

    if (bool_affiche=='T') afficherListe(adr_liste);
}

////////////////////////////////////////////////

void suppr_pos_k(TypePtrListe *adr_liste, int k, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficher_erreur('L');
        return;
    }

    //variables
    TypePtrListe p_prec = NULL, p = *adr_liste;
    int i = 1;

    //placement a la bonne position
    while(p != NULL && i < k){
        p_prec = p;
        p = p -> suiv;
        i++;
    }
    if(k==1){ //insertion en debut de liste (cas de liste vide ET de liste preexistante)
        suppr_en_tete(adr_liste, bool_affiche);
        return;
        }//sinon k>1
    if (p == NULL && k!= i){//k > i (k>longueur de la liste)
            afficher_erreur('P');
            return;
    }//sinon insertion en milieu de liste OU en fin de liste (p == NULL);
    suppr_en_tete(&p_prec -> suiv, bool_affiche);
}

void accesVal(TypePtrListe *adr_liste, int val, TypePtrListe *adr_ptrCell){

    //variables
    TypePtrListe p = *adr_liste;

    while(p != NULL){
        if(p -> info == val){//cas du match
        printf("%d\n", p->info);
        adr_ptrCell = p; return;
        }
        p = p -> suiv; //sinon incrementation
    }printf("pas ok");
    *adr_ptrCell = NULL; // si on ne trouve pas
}
/****************************************CORPS****************************************/

int main()
{
    TypePtrListe *maListe = (TypePtrListe*) malloc(sizeof(TypePtrListe));

    ins_pos_k(maListe, 56, 1, 'F');
    ins_pos_k(maListe, 33, 1, 'F');
    ins_en_tete(maListe, 1, 'F');
    ins_pos_k(maListe, 44, 3, 'F');
    ins_en_tete(maListe, 2, 'F');
    ins_en_tete(maListe, 3, 'F');
    ins_pos_k(maListe, 88, 7, 'F');
    ins_pos_k(maListe, 88, 9, 'F');
    suppr_en_tete(maListe, 'F');
    suppr_pos_k(maListe, 10, 0);
    afficherListe(maListe);

    printf("\n");
    TypePtrListe *adr_ptrCell = (TypePtrListe*) malloc(sizeof(TypePtrListe));
    accesVal(maListe, 44, adr_ptrCell);
    //printf("%d\n", adr_ptrCell->info);
    return 0;
}
