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
void insert_liste_triee(TypePtrListe *adr_liste, int val, char bool_affiche);


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
    TypePtrListe prec = NULL, p = *adr_liste;
    int i = 1;

    //placement a la bonne position
    while(p != NULL && i < k){
        prec = p;
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
    ins_en_tete(&prec -> suiv, val, bool_affiche);
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
    TypePtrListe prec = NULL, p = *adr_liste;
    int i = 1;

    //placement a la bonne position
    while(p != NULL && i < k){
        prec = p;
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
    suppr_en_tete(&prec -> suiv, bool_affiche);
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

void insert_liste_triee(TypePtrListe *adr_liste, int val, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficher_erreur('L');
        return;
    }

    //variables
    TypePtrListe p = *adr_liste; TypePtrListe prec = NULL;

    //placement a la bonne position
    while(p != NULL && val > p-> info){
        prec = p;
        p = p -> suiv;
    }//si liste vide, insertion en tete
    if (prec == NULL){
        ins_en_tete(adr_liste, val, bool_affiche);
        return;
    }//sinon insertion au milieu OU en fin de liste
    ins_en_tete(&prec -> suiv, val, bool_affiche);
}
/****************************************CORPS****************************************/

int main()
{
    TypePtrListe *maListe = (TypePtrListe*) malloc(sizeof(TypePtrListe));
    int i;

    for(i=10; i>1; i-=2){
    ins_en_tete(maListe, i, 'F');
    }

    afficherListe(maListe);

    insert_liste_triee(maListe, 5, 'F');
    afficherListe(maListe);

    TypePtrListe *Liste = (TypePtrListe*) malloc(sizeof(TypePtrListe));
    insert_liste_triee(Liste, 5, 'F');
    insert_liste_triee(Liste, 5, 'F');
    insert_liste_triee(Liste, 1, 'F');
    afficherListe(Liste);

    return 0;
}
