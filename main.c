#include <stdio.h>
#include <stdlib.h>

/**************************************DEFINITION******************************************/

//Alias
typedef struct TCell* TPtr;
typedef struct TCell TCell;

//Fonction
void afficherErreur(char typeErreur);
TPtr *creationElem(int val);
void afficherListe(TPtr *adr_liste);
void insDebut(TPtr *adr_liste, int val, char bool_affiche);
void insPos(TPtr *adr_liste, int val, int pos, char bool_affiche);
void supprDebut(TPtr *adr_liste, char bool_affiche);
void supprPos(TPtr *adr_liste, int k, char bool_affiche);
void accesVal(TPtr *adr_liste, int val, TPtr *adr_ptrCell);
void inserListeTriee(TPtr *adr_liste, int val, char bool_affiche);
void lireFichier(char nomDuFichier[], char modeOuverture[]);
/*void tri_rapide(int vect[],int taille);
void triRapide2(int vect[], int debut, int fin);
int partitionner(int vect[], int debut, int fin);*/
void echanger(int v[], int i, int j);
void tri_bulles(int v[], int n);
int echanger_jusqua_pos(int v[], int i, int en_desordre);
void afficherVect(int v[], int taille);

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

void afficherErreur(char typeErreur){
    printf("Erreur: ");
    switch(typeErreur){
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

TPtr *creationElem(int val){
    TPtr cell = (TCell*) malloc(sizeof(TCell));
    cell -> info = val;

    //verification de reussite
    if(cell == NULL){
    exit(1);
    }

    return cell;
}

////////////////////////////////////////////////

void afficherListe(TPtr *adr_liste){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficherErreur('L');
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

void insDebut(TPtr *adr_liste, int val, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficherErreur('L');
        return;
    }

    // creation du nouvel element
    TPtr p_nouv;
    p_nouv=creationElem(val);
    // insertion de l'element au debut de la liste
    p_nouv -> suiv = *adr_liste;
    *adr_liste = p_nouv;

    if (bool_affiche=='T') afficherListe(adr_liste);
}

////////////////////////////////////////////////

void insPos(TPtr *adr_liste, int val, int k, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficherErreur('L');
        return;
    }

    //variables
    TPtr prec = NULL, p = *adr_liste;
    int i = 1;

    //placement a la bonne position
    while(p != NULL && i < k){
        prec = p;
        p = p -> suiv;
        i++;
    }
    if(k==1){ //insertion en debut de liste (cas de liste vide [p == NULL] ET de liste preexistante)
        insDebut(adr_liste, val, bool_affiche);
        return;
        }//sinon k>1
    if (p == NULL && k!= i){//k > i (k>longueur de la liste)
            afficherErreur('P');
            return;
    }//sinon insertion en milieu de liste OU en fin de liste (p == NULL);
    insDebut(&prec -> suiv, val, bool_affiche);
}

////////////////////////////////////////////////

void supprDebut(TPtr *adr_liste, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficherErreur('L');
        return;
    }

    //raccordements
    TPtr p = *adr_liste;
    *adr_liste = p -> suiv;

    free(p); //supression

    if (bool_affiche=='T') afficherListe(adr_liste);
}

////////////////////////////////////////////////

void supprPos(TPtr *adr_liste, int k, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficherErreur('L');
        return;
    }

    //variables
    TPtr prec = NULL, p = *adr_liste;
    int i = 1;

    //placement a la bonne position
    while(p != NULL && i < k){
        prec = p;
        p = p -> suiv;
        i++;
    }
    if(k==1){ //insertion en debut de liste (cas de liste vide ET de liste preexistante)
        supprDebut(adr_liste, bool_affiche);
        return;
        }//sinon k>1
    if (p == NULL && k!= i){//k > i (k>longueur de la liste)
            afficherErreur('P');
            return;
    }//sinon insertion en milieu de liste OU en fin de liste (p == NULL);
    supprDebut(&prec -> suiv, bool_affiche);
}

////////////////////////////////////////////////

void accesVal(TPtr *adr_liste, int val, TPtr *adr_ptrCell){

    //variables
    TPtr p = *adr_liste;

    while(p != NULL){
        if(p -> info == val){//cas du match
        printf("%d\n", p->info);
        adr_ptrCell = p; return;
        }
        p = p -> suiv; //sinon incrementation
    }afficherErreur('V');
    *adr_ptrCell = NULL; // si on ne trouve pas
}

////////////////////////////////////////////////

void inserListeTriee(TPtr *adr_liste, int val, char bool_affiche){

    //verification d'existence de liste
    if (adr_liste == NULL)
    {
        afficherErreur('L');
        return;
    }

    //variables
    TPtr p = *adr_liste; TPtr prec = NULL;

    //placement a la bonne position
    while(p != NULL && val > p-> info){
        prec = p;
        p = p -> suiv;
    }//si liste vide, insertion en tete
    if (prec == NULL){
        insDebut(adr_liste, val, bool_affiche);
        return;
    }//sinon insertion au milieu OU en fin de liste
    insDebut(&prec -> suiv, val, bool_affiche);
}

////////////////////////////////////////////////

void lireFichier(char nomDuFichier[], char modeOuverture[]){

    FILE* fichier = NULL;
    fichier = fopen(nomDuFichier, modeOuverture);

    if (fichier == NULL)
    {
        afficherErreur('F');;
    }//sinon
    char chaine[50] = "";

    while (fgets(chaine, 50, fichier) != NULL)
    {
        printf("%s", chaine);
    }

        fclose(fichier);
}

////////////////////////////////////////////////
/*void tri_rapide(int vect[],int taille){
     triRapide2(vect,0,taille-1);
}

void triRapide2(int vect[], int debut, int fin){

    if(debut < fin){
       int pos_pivot = partitionner(vect, debut, fin);
        triRapide2(vect, debut, pos_pivot - 1);
        triRapide2(vect, pos_pivot + 1, fin);
    }//sinon vecteur vide
}

int partitionner(int vect[], int debut, int fin){

    //variables locales
    int pivot, i, j;

    //affectation
    pivot = vect[debut];
    i = debut + 1;
    j = fin;

    while(i <= j){
        if(vect[i] <= pivot){
            i++;
        }//sinon
        while(vect[j] > pivot){
            j--;
        }
        if(i < j){
        //echanger(v, i, j);
        i++; j--;
    }
    echanger(vect, debut, j);
    return j;
}*/

void echanger(int v[], int i, int j){
    int save = v[i];
    v[i] = v[j];
    v[j] = save;
}

void afficherVect(int v[], int taille){
    int i;

    for (i = 0 ; i < taille ; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void tri_bulles(int v[], int taille){

    //variable globale
    int i, en_desordre;

    //affectation
    i = taille-1;

    while (en_desordre){
        en_desordre = echanger_jusqua_pos(v, i, en_desordre);
        i--; //le maximum est placé correctement, au n-1 passage on a une comparaison de moins a faire
    }
}

int echanger_jusqua_pos(int v[], int i, int en_desordre){

    //variable locale
    int j;

    //affectation
    j = 1;

    while(j < i){
        if(v[j] > v [j+1]){
            echanger(v, j , j+1);
            en_desordre = 1;
        j++;
    }
    return en_desordre;
}

/****************************************CORPS****************************************/

int main()
{
    int vect[8]= {13,1,23,7,4,14,15,2};
    afficherVect(vect, 8);
    tri_bulles(vect, 8);
    afficherVect(vect, 8);
    return 0;
}
