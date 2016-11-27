#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**************************************DEFINITION******************************************/

//Alias
typedef struct TCell* TPtr;
typedef struct TCell TCell;

//Fonction
void affiche_erreur(char typeErreur);
TPtr *creation_elem(int val);
void affiche_liste(TPtr *adr_liste);
void ins_en_tete(TPtr *adr_liste, int val, char bool_affiche);
void ins_pos_k(TPtr *adr_liste, int val, int pos_k, char bool_affiche);
void suppr_en_tete(TPtr *adr_liste, char bool_affiche);
void suppr_pos_k(TPtr *adr_liste, int k, char bool_affiche);
void acces_val(TPtr *adr_liste, int val, TPtr *adr_val);
void ins_liste_triee(TPtr *adr_liste, int val, char bool_affiche);
void lire_fichier(char nom_fichier[], char mode_ouverture[]);


/**************************************FONCTIONS**************************************/

//Alias

struct TypeChaine80{
    char chaineCaratere[80];
};

////////////////////////////////////////////////

typedef struct TCell{
    int info;
    TPtr suiv;
};




//Fonctions

////////////////////////////////////////////////

void affiche_erreur(char type_erreur){
    printf("Erreur: ");
    switch(type_erreur){
        case 'L':
            printf("liste vide.\n");
            break;
        case 'P':
            printf("position erronee.\n");
            break;
        case 'V':
            printf("valeur inexistante.\n");
        break;
        case 'F':
            printf("ouverture du fichier impossible.\n");
        break;
    }
}

////////////////////////////////////////////////

TPtr *creation_elem(int val){
    TPtr cell = (TPtr) malloc(sizeof(TPtr));
    cell -> info = val;

    //verification de reussite
    if(cell == NULL){
    exit(1);
    }

    return cell;
}

////////////////////////////////////////////////

void affiche_liste(TPtr *adr_liste){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        affiche_erreur('L');
        return;
    }

    TPtr p = *adr_liste;

    //afficher chaque cellule
    while (p != NULL)
    {
        printf("%d -> ", p->info);
        p = p -> suiv;
    }
    printf("NULL\n"); //marquer la fin de liste
}

////////////////////////////////////////////////

void ins_en_tete(TPtr *adr_liste, int val, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        affiche_erreur('L');
        return;
    }

    // creation du nouvel element
    TPtr p_nouv;
    p_nouv=creation_elem(val);
    // insertion de l'element au debut de la liste
    p_nouv -> suiv = *adr_liste;
    *adr_liste = p_nouv;

    if (bool_affiche=='T') affiche_liste(adr_liste);
}

////////////////////////////////////////////////

void ins_pos_k(TPtr *adr_liste, int val, int pos_k, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        affiche_erreur('L');
        return;
    }

    //variables
    TPtr p_prec = NULL, p = *adr_liste;
    int i = 1;

    //placement a la bonne position
    while(p != NULL && i < pos_k){
        p_prec = p;
        p = p -> suiv;
        i++;
    }
    if(pos_k==1){ //insertion en debut de liste (cas de liste vide [p == NULL] ET de liste preexistante)
        ins_en_tete(adr_liste, val, bool_affiche);
        return;
        }//sinon pos_k>1
    if (p == NULL && pos_k!= i){//pos_k > i (pos_k>longueur de la liste)
            affiche_erreur('P');
            return;
    }//sinon insertion en milieu de liste OU en fin de liste (p == NULL);
    ins_en_tete(&p_prec -> suiv, val, bool_affiche);
}

////////////////////////////////////////////////

void suppr_en_tete(TPtr *adr_liste, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        affiche_erreur('L');
        return;
    }

    //raccordements
    TPtr p = *adr_liste;
    *adr_liste = p -> suiv;

    free(p); //supression

    if (bool_affiche=='T') affiche_liste(adr_liste);
}

////////////////////////////////////////////////

void suppr_pos_k(TPtr *adr_liste, int k, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        affiche_erreur('L');
        return;
    }

    //variables
    TPtr p_prec = NULL, p = *adr_liste;
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
            affiche_erreur('P');
            return;
    }//sinon insertion en milieu de liste OU en fin de liste (p == NULL);
    suppr_en_tete(&p_prec -> suiv, bool_affiche);
}

////////////////////////////////////////////////

void acces_val(TPtr *adr_liste, int val, TPtr *adr_val){

    //variables
    TPtr p = *adr_liste;

    while(p != NULL){
        if(p -> info == val){//cas du match
        printf("%d\n", p->info);
        adr_val = p; return;
        }
        p = p -> suiv; //sinon incrementation
    }affiche_erreur('V');
    *adr_val = NULL; // si on ne trouve pas
}

////////////////////////////////////////////////

void ins_liste_triee(TPtr *adr_liste, int val, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        affiche_erreur('L');
        return;
    }

    //variables
    TPtr p = *adr_liste; TPtr p_prec = NULL;

    //placement a la bonne position
    while(p != NULL && val > p-> info){
        p_prec = p;
        p = p -> suiv;
    }//si liste vide, insertion en tete
    if (p_prec == NULL){
        ins_en_tete(adr_liste, val, bool_affiche);
        return;
    }//sinon insertion au milieu OU en fin de liste
    ins_en_tete(&p_prec -> suiv, val, bool_affiche);
}

////////////////////////////////////////////////

void lire_fichier(char nom_fichier[], char mode_ouverture[]){

    FILE* fichier = NULL;
    fichier = fopen(nom_fichier, mode_ouverture);

    if (fichier == NULL)
    {
        affiche_erreur('F');;
    }//sinon
    char chaine[50] = "";

    while (fgets(chaine, 50, fichier) != NULL)
    {
        printf("%s", chaine);
    }

        fclose(fichier);
}

/****************************************CORPS****************************************/

int main()
{
    TPtr *tete = (TPtr*) malloc(sizeof(TPtr));
    //tete = NULL;

    /*ins_pos_k(tete, 56, 1, 'F');
    ins_pos_k(tete, 33, 1, 'F');
    ins_en_tete(tete, 1, 'F');
    ins_pos_k(tete, 44, 3, 'F');
    ins_en_tete(tete, 2, 'F');
    ins_en_tete(tete, 3, 'F');
    ins_pos_k(tete, 88, 7, 'F');
    ins_pos_k(tete, 88, 9, 'F');
    suppr_en_tete(tete, 'F');
    suppr_pos_k(tete, 10, 'F');*/
    affiche_liste(tete);

    printf("\n");
    TPtr *adr_val = (TPtr*) malloc(sizeof(TPtr));
    acces_val(tete, 44, adr_val);
    //printf("%d\n", adr_val->info);
    return 0;
}
