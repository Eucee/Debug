#include <stdlib.h>
#include <time.h>

/**************************************DEFINITION******************************************/

/*void tri_rapide(int vect[],int taille);
void triRapide2(int vect[], int debut, int fin);
int partitionner(int vect[], int debut, int fin);*/
void echanger(int v[], int i, int j);
void tri_bulles(int v[], int n);
void echanger_jusqua_pos(int v[], int dm, int echange);
void afficherVect(int v[], int taille);

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

void echanger(int v[], int i, int j){
    int save = v[i];
    v[i] = v[j];
    v[j] = save;
}

////////////////////////////////////////////////

void afficherVect(int v[], int taille){
    int i;

    for (i = 0 ; i < taille ; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

////////////////////////////////////////////////

void tri_bulles(int v[], int taille){

    //variable globale
    int dm, echange;

    //affectation
    dm = taille-1;
    echange = 1;

    while (echange && dm >= 1){
        echanger_jusqua_pos(v, dm, echange);
        //le maximum est placé correctement, au n-1 passage on a une comparaison de moins a faire
    }
}

void echanger_jusqua_pos(int v[], int dm, int echange){

    //variable locale
    int j, k;

    //affectation
    j = 0, echange = 0;

    while(j < dm){
        if(v[j] > v [j+1]){
            echanger(v, j , j+1);
            echange = 1 ;
            k = j;
            afficherVect(v, 8);
        }
        j++;
    }
    dm = k;
    //printf("%d\n",j);
}

int main()
{
    int vect[8]= {13,1,23,7,4,14,15,2};
    //afficherVect(vect, 8);
    tri_bulles(vect, 8);
    //afficherVect(vect, 8);

    return 0;
}
