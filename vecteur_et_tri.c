#include <stdlib.h>
#include <time.h>

/**************************************DEFINITION******************************************/

typedef enum bool bool;
/*void tri_rapide(int vect[],int taille);
void triRapide2(int vect[], int debut, int fin);
int partitionner(int vect[], int debut, int fin);*/
void echanger(int *adr_vect, int pos1, int pos2);
void tri_bulles(int *adr_vect, int taille_vect);
void echanger_jusqua_pos(int *adr_vect, int *adr_taille_a_parcourir, bool aTrier);
void afficherVect(int *adr_vect, int taille_vect);
void initialiserVect(int *adr_vect, int taille_vect);


enum bool{
    FALSE, TRUE
 };

/**************************************FONCTIONS**************************************/

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

/*--------------------------------------------------------------------
PROCEDURE afficherVect:
-Entr�e/Sortie: Pointeur sur vecteur adr_vect, l'adresse du vecteur � modifier
-Entr�e: Entier taille_vect, la taille du vecteur

Pr�condition:
-Le vecteur ne doit pas �tre nul

Postcondition:
-Affichage de l'ensemble des �l�ments d'une vecteurs
--------------------------------------------------------------------*/
void afficherVect(int *adr_vect, int taille_vect){

    //Variable
    int posVect;//indice de position dans le vecteur

    for (posVect = 0 ; posVect < taille_vect ; posVect++){
        printf("%d ", adr_vect[posVect]);
    }
    printf("\n");
}

void initialiserVect(int *adr_vect, int taille_vect){
    //Variable
    int posVect;//indice de position dans le vecteur

    for (posVect = 0 ; posVect < taille_vect ; posVect++)
    {
        adr_vect[posVect] = 0;
    }
}
/*--------------------------------------------------------------------
PROCEDURE tri_bulles:
-Entr�e/Sortie: Pointeur sur vecteur adr_vect, l'adresse du vecteur � modifier
-Entr�e: Entier pos1, un �l�ment du vecteur � la position x (x!=y)
-Entr�e: Entier pos2, un �l�ment du vecteur � la position y (y!=x)

Pr�condition:
-Le vecteur ne doit pas �tre nul

Postcondition:
-Echange de position deux valeurs d'un vecteur
--------------------------------------------------------------------*/
void echanger(int *adr_vect, int pos1, int pos2){
    int save; //d�claration d'une variable de sauvegarde
    save = adr_vect[pos1]; //sauvegarde de l'�l�ment � la pos1
    adr_vect[pos1] = adr_vect[pos2]; //on �crase la valeur de l'�lement � la pos1 par celle � la pos2
    adr_vect[pos2] = save; //on attribue la valeur sauvegardee (i.e., � l'ancienne pos1) � la pos 2
}

/*--------------------------------------------------------------------
PROCEDURE tri_bulles:
-Entr�e/Sortie: Pointeur sur vecteur adr_vect, l'adresse du vecteur � modifier
-Entr�e: Entier taille_vect, la taille du vecteur

Pr�condition:
-Le vecteur ne doit pas �tre nul

Postcondition:
-Tri� par ordre croissant un vecteur contenant des entiers
--------------------------------------------------------------------*/
void tri_bulles(int *adr_vect, int taille_vect){

    //Variables
    int taille_a_parcourir; //d�claration d'un indice temporaire de la longueur du vecteur restant � parcourir
    bool aTrier; //et d'un bool�en pour marquer la fin du tri (= au moins un �change a �t� r�alis� lors du dernier passage)

    //affectation
    taille_a_parcourir = taille_vect-1; //le vecteur commence � 0 et finit � taille-1
    aTrier = TRUE; // initialisation du bool�en � FAUX

    while (aTrier && taille_a_parcourir >= 1){//tant qu'une derniere modification a �t� �ffectu� ET tant qu'il y a plus d'un �l�ment (sinon le tri est trivial), le tableau n'a pas fini son tri
        echanger_jusqua_pos(adr_vect, &taille_a_parcourir, aTrier); //Cf. fonction ad hoc
        //le maximum est plac� correctement, au n-1 passage on a une comparaison de moins a faire
    }
}

/*--------------------------------------------------------------------
PROCEDURE echanger_jusqua_pos:
-Entr�e/Sortie: Pointeur sur vecteur adr_vect, l'adresse du vecteur � modifier
-Entr�e/Sortie: Entier taille_vect, la taille du vecteur
-Entr�e: Bool�en aTrier, indicatif de fin de tri

Pr�condition:
-Le vecteur ne doit pas �tre nul

Postcondition:
-Echange un nombre � une position donn�e jusqu'� la fin du vecteur
--------------------------------------------------------------------*/
void echanger_jusqua_pos(int *adr_vect, int *adr_taille_a_parcourir, bool aTrier){

     //Variables
    int j, k, posVect; //d�claration
    j = 0; //affectation de la position temporaire dans le vecteur
    k = 0;
    aTrier = FALSE; //valeur par d�faut si le programme ne rentre pas dans la condition while

    while(j < *adr_taille_a_parcourir){
        if(adr_vect[j] > adr_vect[j+1]){//si l'�lement suivant du vecteur est sup�rieur
            echanger(adr_vect, j , j+1);  //on �change leurs positions (Cf. fonction ad hoc)
            aTrier = FALSE; //il y a eu une derni�re modification effectu�e lors de cette it�ration
            k = j; //m�morisation de la derni�re position d'�change
            afficherVect(adr_vect, *adr_taille_a_parcourir);
        }
        j++;
    }
    *adr_taille_a_parcourir = k; //actualisation de la longueur du vecteur � parcourir
    //printf("%d\n",j);
}

int main()
{
    int vect[8] = {13,1,23,7,4,14,15,2};

    afficherVect(vect, 8);
    //initialiserVect(vect, 8);
    //afficherVect(vect, 8);
    tri_bulles(vect, 8);
    afficherVect(vect, 8);

    return 0;
}
