#include <stdlib.h>
#include <time.h>

/**************************************DEFINITION******************************************/

typedef enum bool bool;
/*void tri_rapide(int *adr_vect,int taille);
void triRapide2(int *adr_vect, int debut, int fin);
int partitionner(int *adr_vect, int debut, int fin);*/
void echanger(int *adr_vect, int pos1, int pos2);
void tri_bulles(int *adr_vect, int taille_vect);
void echanger_jusqua_pos(int *adr_vect, int *adr_taille_a_parcourir, bool aTrier);
void afficherVect(int *adr_vect, int taille_vect);
void initialiserVect(int *adr_vect, int taille_vect);


enum bool{
    FALSE, TRUE
 };

/**************************************FONCTIONS**************************************/

/*--------------------------------------------------------------------
PROCEDURE afficherVect:
-Entrée/Sortie: Pointeur sur vecteur adr_vect, l'adresse du vecteur à modifier
-Entrée: Entier taille_vect, la taille du vecteur

Précondition:
-Le vecteur ne doit pas être nul

Postcondition:
-Affichage de l'ensemble des éléments d'une vecteur
--------------------------------------------------------------------*/
void afficherVect(int *adr_vect, int taille_vect){

    //Variable
    int posVect;//indice de position dans le vecteur

    for (posVect = 0 ; posVect < taille_vect ; posVect++){
        printf("%d ", adr_vect[posVect]);
    }
    printf("\n");
}

/*--------------------------------------------------------------------
PROCEDURE initialiserVect:
-Entrée/Sortie: Pointeur sur vecteur adr_vect, l'adresse du vecteur à modifier
-Entrée: Entier taille_vect, la taille du vecteur

Précondition:
-Le vecteur ne doit pas être nul

Postcondition:
-Initialise à 0 l'ensemble des éléments d'une vecteur
--------------------------------------------------------------------*/
void initialiserVect(int *adr_vect, int taille_vect){
    //Variable
    int posVect;//indice de position dans le vecteur

    for (posVect = 0 ; posVect < taille_vect ; posVect++)
    {
        adr_vect[posVect] = 0;
    }
}

void tri_rapide(int *adr_vect,int taille_vect){
     triRapide2(adr_vect, 0, taille_vect-1);
}
/*--------------------------------------------------------------------
PROCEDURE triRapide:
-Entrée/Sortie: Pointeur sur vecteur adr_vect, l'adresse du vecteur à modifier
-Entrée: Entier debut, début du vecteur
-Entrée: Entier fin, fin du vecteur

Précondition:
-Le vecteur ne doit pas être nul

Postcondition:
-Trie par ordre croissant un vecteur contenant des entiers
--------------------------------------------------------------------*/
void triRapide2(int *adr_vect, int debut, int fin){

    int pos_pivot = 0;

    if(debut < fin){
        pos_pivot = partitionner(adr_vect, debut, fin);
        triRapide2(adr_vect, debut, pos_pivot - 1);
        triRapide2(adr_vect, pos_pivot + 1, fin);
    }//sinon le vecteur est vide (et inchangé)
}

/*--------------------------------------------------------------------
FONCTION partitionner:
-Entrée/Sortie: Pointeur sur vecteur adr_vect, l'adresse du vecteur à modifier
-Entrée: Entier debut, début du vecteur
-Entrée: Entier fin, fin du vecteur
-Sortie: Entier pos2, position du nouveau pivot

Précondition:
-Le vecteur ne doit pas être nul

Postcondition:
-Tant que le vecteur ne devient pas nul (début > fin), échange les positions inférieures à la valeur d'un pivot avec celles qui lui sont supérieures, sinon renvoi la position d'un nouveau pivot
--------------------------------------------------------------------*/

int partitionner(int *adr_vect, int debut, int fin){

    //variables locales
    int pivot, pos1, pos2;

    //affectation
    pivot = adr_vect[debut];
    pos1 = debut + 1;
    pos2 = fin;

    while(pos1 <= pos2){
        if(adr_vect[pos1] <= pivot){// la valeur en cours est bien placée (= inf au pivot)
            pos1++; //on avance depuis le début du vecteur pour tenter à la prochaine itération d'en trouver une mal placée
        }else{//sinon l'élément est mal placé (= sup au pivot) et attend son transfert vers la fin du vecteur
            while(adr_vect[pos2] > pivot){//tant que la valeur en cours est bien placée (= sup au pivot)
                pos2--; //on recule depuis la fin du vecteur
            }//on sort de boucle si finalement on trouve un élément mal placée en fin de vecteur (=inf au pivot)
            if(pos1 < pos2){//on vérifie que les deux éléments mal placés sont échangeables
                echanger(adr_vect, pos1, pos2);
                pos1++; pos2--; //les deux sont bien placés, donc on décrémentd pour pour tenter à la prochaine itération d'en trouver un mal placé
            }
        }
    }
    echanger(adr_vect, debut, pos2);
    return pos2;
}

/*--------------------------------------------------------------------
PROCEDURE tri_bulles:
-Entrée/Sortie: Pointeur sur vecteur adr_vect, l'adresse du vecteur à modifier
-Entrée: Entier pos1, un élément du vecteur à la position x (x!=y)
-Entrée: Entier pos2, un élément du vecteur à la position y (y!=x)

Précondition:
-Le vecteur ne doit pas être nul

Postcondition:
-Echange de position deux valeurs d'un vecteur
--------------------------------------------------------------------*/
void echanger(int *adr_vect, int pos1, int pos2){
    int save; //déclaration d'une variable de sauvegarde
    save = adr_vect[pos1]; //sauvegarde de l'élément à la pos1
    adr_vect[pos1] = adr_vect[pos2]; //on écrase la valeur de l'élement à la pos1 par celle à la pos2
    adr_vect[pos2] = save; //on attribue la valeur sauvegardee (i.e., à l'ancienne pos1) à la pos 2
}

/*--------------------------------------------------------------------
PROCEDURE tri_bulles:
-Entrée/Sortie: Pointeur sur vecteur adr_vect, l'adresse du vecteur à modifier
-Entrée: Entier taille_vect, la taille du vecteur

Précondition:
-Le vecteur ne doit pas être nul

Postcondition:
-Trie par ordre croissant un vecteur contenant des entiers
--------------------------------------------------------------------*/
void tri_bulles(int *adr_vect, int taille_vect){

    //Variables
    int taille_a_parcourir; //déclaration d'un indice temporaire de la longueur du vecteur restant à parcourir
    bool aTrier; //et d'un booléen pour marquer la fin du tri (= au moins un échange a été réalisé lors du dernier passage)

    //affectation
    taille_a_parcourir = taille_vect-1; //le vecteur commence à 0 et finit à taille-1
    aTrier = TRUE; // initialisation du booléen à FAUX

    while (aTrier && taille_a_parcourir >= 1){//tant qu'une derniere modification a été éffectué ET tant qu'il y a plus d'un élément (sinon le tri est trivial), le tableau n'a pas fini son tri
        echanger_jusqua_pos(adr_vect, &taille_a_parcourir, aTrier); //Cf. fonction ad hoc
        //le maximum est placé correctement, au n-1 passage on a une comparaison de moins a faire
    }
}

/*--------------------------------------------------------------------
PROCEDURE echanger_jusqua_pos:
-Entrée/Sortie: Pointeur sur vecteur adr_vect, l'adresse du vecteur à modifier
-Entrée/Sortie: Entier taille_vect, la taille du vecteur
-Entrée: Booléen aTrier, indicatif de fin de tri

Précondition:
-Le vecteur ne doit pas être nul

Postcondition:
-Echange un nombre à une position donnée jusqu'à la fin du vecteur
--------------------------------------------------------------------*/
void echanger_jusqua_pos(int *adr_vect, int *adr_taille_a_parcourir, bool aTrier){

     //Variables
    int j, k, posVect; //déclaration
    j = 0; //affectation de la position temporaire dans le vecteur
    k = 0;
    aTrier = FALSE; //valeur par défaut si le programme ne rentre pas dans la condition while

    while(j < *adr_taille_a_parcourir){
        if(adr_vect[j] > adr_vect[j+1]){//si l'élement suivant du vecteur est supérieur
            echanger(adr_vect, j , j+1);  //on échange leurs positions (Cf. fonction ad hoc)
            aTrier = FALSE; //il y a eu une dernière modification effectuée lors de cette itération
            k = j; //mémorisation de la dernière position d'échange
            afficherVect(adr_vect, *adr_taille_a_parcourir);
        }
        j++;
    }
    *adr_taille_a_parcourir = k; //actualisation de la longueur du vecteur à parcourir
    //printf("%d\n",j);
}

int main()
{
    int vect[8] = {13,1,23,7,4,14,15,2};

    afficherVect(vect, 8);
    //initialiserVect(vect, 8);
    //afficherVect(vect, 8);
    tri_rapide(vect, 8);
    afficherVect(vect, 8);

    return 0;
}
