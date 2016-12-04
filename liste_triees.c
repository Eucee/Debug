#include <stdio.h>
#include <stdlib.h>

/**************************************DEFINITION******************************************/

//Alias
typedef struct TypeChaine80 TypeChaine80;
typedef struct TCell* TPtr;
typedef struct TCell TCell;
typedef enum bool bool;

//Fonction
void affiche_erreur(char typeErreur);
TPtr creation_cell(int val);
void affiche_liste(const TPtr adr_tete);
void ajout_en_tete(TPtr *adr_tete, int val);
void ajout_pos_k(TPtr *adr_tete, int val, int pos);
void suppr_en_tete(TPtr *adr_tete);
void suppr_pos_k(TPtr *adr_tete, int k);
void acces_val(const TPtr adr_tete, int val, TPtr *adr_ptrCell, bool *adr_trouve);
void ajout_liste_triee(TPtr *adr_tete, int val);


/**************************************FONCTIONS**************************************/

/*-----------------------------
            Alias
 -----------------------------*/

struct TypeChaine80{
    char chaineCaratere[80];
};

/*-----------------------------*/

struct TCell{
    int info;
    TPtr suiv;
};

/*-----------------------------*/

enum bool{
    FALSE, TRUE
 };



/*-----------------------------
            Fonction
 -----------------------------*/


/*--------------------------------------------------------------------
PROCEDURE affiche_erreur:
-Entrée: charactère typeErreur, type d'erreur commise par le programme

Postcondition:
-Affichage du type d'erreur commise par le programme
--------------------------------------------------------------------*/

void affiche_erreur(char typeErreur){

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
    }
}


/*--------------------------------------------------------------------
PROCEDURE affiche_liste:
-Entrée: Liste adr_tete, adresse du début d'une liste

Précondition:
-Liste non vide

Postcondition:
-Affichage de toute les cellules chainees d'une liste (en commencant par le début de liste)
--------------------------------------------------------------------*/

void affiche_liste(const TPtr adr_tete){

    if (adr_tete == NULL){ //si la précondition n'est pas vérifiée, renvoie une erreur
        affiche_erreur('L'); return;
    }

    //Variables
    TPtr p; //création de notre espion que l'on va faire courir le long de la liste
    p = adr_tete; //initialisation sur l'adresse du premier element de la liste

    while (p != NULL){ //tant que l'on n'est pas au bout de la liste
        printf("%d -> ", p->info); //affichage de l'information de la cellule
        p = p -> suiv; //on avance à la cellule suivante
    }
    printf("NULL\n"); //on marque la fin de liste
}

/*--------------------------------------------------------------------
FONCTION creation_cell:
-Entrée: entier val, valeur désirée et contenue dans la cellule
-Sortie: Cellule cell, adresse d'une cellule crée au sein de la fonction

Postcondition:
-Renvoie l'adresse d'une cellule nouvellement créée et dont sa valeur a été fixée
--------------------------------------------------------------------*/

TPtr creation_cell(int val){

    //Variables
    TPtr cell;
    cell = (TPtr) malloc(sizeof(TCell)); //allocation dynamique d'une nouvelle cellule
    cell -> info = val; //attribution de valeur

    //verification de reussite de l'allocation mémoire
    if(cell == NULL) exit(1); //sinon la mémoire est saturée et on doit quitter le programme

    return cell;
}

/*--------------------------------------------------------------------
PROCEDURE ajout_en_tete:
-Entrée/Sortie: Liste adr_tete, adresse du début d'une liste
-Entrée: entier val, valeur désirée et contenue dans la cellule

Postcondition:
-Ajoute une cellule nouvellement créée (et dont sa valeur a été fixée) au DEBUT d'une liste prééxistante
--------------------------------------------------------------------*/

void ajout_en_tete(TPtr *adr_tete, int val){

    //Variables
    TPtr p_nouv;
    p_nouv = creation_cell(val);// creation du nouvel element

    p_nouv -> suiv = *adr_tete; //attribue l'adresse adresse du début d'une liste au pointeur de la cellule suivant la cellule créée
    *adr_tete = p_nouv; // liaison avec la adr_tete de liste
}

/*--------------------------------------------------------------------
PROCEDURE ajout_en_queue:
-Entrée/Sortie: Liste adr_tete, adresse du début d'une liste
-Entrée: entier val, valeur désirée et contenue dans la cellule

Postcondition:
-Ajoute  une cellule nouvellement créée (et dont sa valeur a été fixée) à la FIN d'une liste prééxistante
--------------------------------------------------------------------*/

void ajout_en_queue(TPtr *adr_tete, int val)
{
    //Variables
    TPtr p_nouv, p;
    p = *adr_tete; //placement du pointeur temporaire sur l'adresse de la tete de liste
    p_nouv = creation_cell(val); // creation du nouvel element

    //en tant qu'ajout en fin de liste, aucune cellule ne va suivre
    p_nouv -> suiv = NULL;


    while(p -> suiv != NULL){ //le pointeur temporaire parcourt la liste juqu'à se positionner à la fin
        p = p -> suiv;
    }
    p -> suiv = p_nouv; //arrivée en bout de liste la dernier celule est reliée à la nouvelle
}

/*--------------------------------------------------------------------
PROCEDURE ajout_pos_k:
-Entrée/Sortie: Liste adr_tete, adresse du début d'une liste
-Entrée: entier val, valeur désirée et contenue dans la cellule
-Entrée: entier k, position désirée de l'ajout de la cellule dans la liste

Postcondition:
-Ajoute une cellule nouvellement créée (et dont sa valeur a été fixée) à une POSITION déterminée d'une liste prééxistante
--------------------------------------------------------------------*/

void ajout_pos_k(TPtr *adr_tete, int val, int k){

    //Variables
    TPtr p_prec, p;
    p_prec = NULL; //initiallisation d'un pointeur pour sauvegarder l'adresse de la cellule précédente à celle en cours
    p = *adr_tete; //placement du pointeur temporaire sur l'adresse de la tete de liste
    int i = 1; //initialisation d'un indice de la position temporaire en début de liste (ici on choisit 1 et pas 0 pour parler en humain et non en C)

    //placement a la bonne position
    while(p != NULL && i < k){ //le pointeur temporaire parcourt la liste jusqu'à trouver la bonne position k ou arriver en fin de liste
        p_prec = p; //stockage de l'adresse de la cellule précédente
        p = p -> suiv; //le pointeur temporaire avance à la cellule suivante
        i++; //stockage de l'indice de position qui avance avec le pointeur temporaire
    }//en sortie de boucle: p == NULL OU k==i OU k>i
    if(k==1){ //ajout en debut de liste (p == NULL ET k==i [ET k==1] : cas d'une liste vide ou p != NULL ET k==i [ET k==1]: cas d'un début de liste)
        ajout_en_tete(adr_tete, val);
        return;
        }//sinon k>1
    if (p == NULL && k!= i){//k > i (la liste a été parcourue et la position demandée k est supérieure à la longueur de la liste)
            affiche_erreur('P'); return;
    }//sinon ajout en milieu de liste (k==i) OU en fin de liste (p == NULL ET k==i [ET k==longeur_liste ]et par conséquent p_prec -> suiv == NULL);
    ajout_en_tete(&p_prec -> suiv, val);
}

/*--------------------------------------------------------------------
PROCEDURE suppr_en_tete:
-Entrée/Sortie: Liste adr_tete, adresse du début d'une liste

Précondition:
-La liste ne doit pas être vide

Postcondition:
-Supprime une cellule au début d'une liste prééxistante
--------------------------------------------------------------------*/

void suppr_en_tete(TPtr *adr_tete){

     //si la précondition n'est pas vérifiée, renvoie une erreur
    if (*adr_tete == NULL){
        affiche_erreur('L'); return;
    }

    //Variables
    TPtr p;
    p = *adr_tete; //placement du pointeur sur l'adresse de la tete de liste

    *adr_tete = p -> suiv; //raccordement de l'ADRESSE de la tete de liste à l'élément APRES l'élement en tete de liste
    free(p); //supression du contenu du pointeur
}

/*--------------------------------------------------------------------
PROCEDURE suppr_en_queue:
-Entrée/Sortie: Liste adr_tete, adresse du début d'une liste

Précondition:
-La liste ne doit pas être vide

Postcondition:
-Supprime une cellule à la fin d'une liste prééxistante
--------------------------------------------------------------------*/

void suppr_en_queue(TPtr *adr_tete){

    //si la précondition n'est pas vérifiée, renvoie une erreur
    if (*adr_tete == NULL){
        affiche_erreur('L'); return;
    }

    //Variables
    TPtr p_prec, p;
    //p_prec = NULL; //initiallisation d'un pointeur pour sauvegarder l'adresse de la cellule précédente à celle en cours
    p = *adr_tete; //placement du pointeur sur l'adresse de la tete de liste

    //placement a la bonne position
    while(p -> suiv != NULL){ //le pointeur temporaire parcourt la liste jusqu'à arriver en fin de liste
        p_prec = p; //stockage de l'adresse de la cellule précédente
        p = p -> suiv; //le pointeur temporaire avance à la cellule suivante
    }
    /* En sortie de boucle: p pointe sur la cellule précédente à NULL, p_prec pointe sur la cellule précédent à p

    Remarque: Si, comme dans les cas usuels, la boucle "tant que" avait concernée p et non p->suiv, à la sortie de boucle, p pointerait sur NULL et p_prec sur la cellule précédete à NULL
    Alors il aurait fallu desallouer p_prec et sauvegarder la valeur précédente à p_prec dans une autre variable (e.g. p_prec_prec) pour valuer son successeur à NULL*/

    //initialisation de la cellule précédente à NULL
    p_prec -> suiv = NULL;

    free(p); //supression de la cellule en fin de liste

}

/*--------------------------------------------------------------------
PROCEDURE suppr_en_tete:
-Entrée/Sortie: Liste adr_tete, adresse du début d'une liste
-Entrée: entier val, valeur désirée et contenue dans la cellule
-Entrée: entier k, position désirée de l'ajout de la cellule dans la liste

Précondition:
-La liste ne doit pas être vide

Postcondition:
-Supprime une cellule à une position déterminée d'une liste prééxistante
--------------------------------------------------------------------*/

void suppr_pos_k(TPtr *adr_tete, int k){

    //si la précondition n'est pas vérifiée, renvoie une erreur
    if (*adr_tete == NULL){
        affiche_erreur('L'); return;
    }

    //Variables
    TPtr p_prec, p;
    p_prec = NULL; //initiallisation d'un pointeur pour sauvegarder l'adresse de la cellule précédente à celle en cours
    p = *adr_tete; //placement du pointeur temporaire sur l'adresse de la tete de liste
    int i = 1; //initialisation d'un indice de la position temporaire en début de liste (ici on choisit 1 et pas 0 pour parler en humain et non en C)

    //placement a la bonne position
    while(p != NULL && i < k){ //le pointeur temporaire parcourt la liste jusqu'à trouver la bonne position k ou arriver en fin de liste
        p_prec = p; //stockage de l'adresse de la cellule précédente
        p = p -> suiv; //le pointeur temporaire avance à la cellule suivante
        i++; //stockage de l'indice de position qui avance avec le pointeur temporaire
    }//en sortie de boucle: p == NULL OU k==i OU k>i et p_prec pointe sur la dernier cellule
    if(k==1){ //suppr en debut de liste (p == NULL ET k==i [ET k==1] : cas d'une liste vide ou p != NULL ET k==i [ET k==1]: cas d'un début de liste)
        suppr_en_tete(adr_tete); return;
        }//sinon k>1
    if (p == NULL && k!= i){//k > i (la liste a été parcourue et la position demandée k est supérieure à la longueur de la liste)
            affiche_erreur('P'); return;
    }//sinon suppr en milieu de liste (k==i) OU en fin de liste (p == NULL ET k==i [ET k==longeur_liste ]et par conséquent p_prec -> suiv == NULL);
    suppr_en_tete(&p_prec -> suiv);
}

/*--------------------------------------------------------------------
PROCEDURE acces_val:
-Entrée: Liste adr_tete, adresse du début d'une liste
-Entrée: entier val, valeur désirée et contenue dans la cellule
-Entrée: Liste adr_ptrCell, adresse d'un pointeur sur
-Entrée: Booléen adr_trouve, existence de la valeur

Précondition:
-La liste ne doit pas être vide
-La valeur doit exister au sein de la liste
-Le booléen est préalablement valuer à FAUX

Postcondition:
-Renvoie un pointeur sur la valeur à trouver et un pointeur sur l'existence de la valeur
--------------------------------------------------------------------*/

void acces_val(const TPtr adr_tete, int val, TPtr *adr_ptrCell, bool *adr_trouve){

    //si la précondition1 n'est pas vérifiée, renvoie une erreur
    if (adr_tete == NULL){
        affiche_erreur('L'); return;
    }

    //Variables
    TPtr p;
    p = adr_tete; //placement du pointeur temporaire sur l'adresse de la tete de liste

    while(p != NULL){//le pointeur temporaire parcourt la liste jusqu'à arriver en fin de liste
        if(p -> info == val){//cas du match
        *adr_trouve = TRUE; //mise à jour des adresses du booléen et du pointeur ET sortie de fonction
        *adr_ptrCell = p; return;
        }
        p = p -> suiv;  //le pointeur temporaire avance à la cellule suivante
    }affiche_erreur('V'); //si la liste a été parcourue entièrement sans renvoyer de solution alors la précondition2 n'est pas vérifiée, renvoie une erreur
    *adr_ptrCell = NULL; //par conséquent le pointeur doit retourner une valeur nulle
}

/*--------------------------------------------------------------------
PROCEDURE ajout_liste_triee:
-Entrée/Sortie: Liste adr_tete, adresse du début d'une liste
-Entrée: entier val, valeur désirée et contenue dans la cellule

Précondition:
-Si elle n'est pas vide, la liste doit etre préalablement triée

Postcondition:
-Ajoute une cellule au sein d'une liste préalablement triée selon une position déterminée par sa valeur
--------------------------------------------------------------------*/

void ajout_liste_triee(TPtr *adr_tete, int val){

    //Variables
    TPtr p_prec, p;
    p_prec = NULL; //initiallisation d'un pointeur pour sauvegarder l'adresse de la cellule précédente à celle en cours
    p = *adr_tete; //placement du pointeur temporaire sur l'adresse de la tete de liste

    //placement a la bonne position
    while(p != NULL & val > p-> info){//le pointeur temporaire parcourt la liste jusqu'à arriver en fin de liste ou qu'il match avec la solution
        p_prec = p; //stockage de l'adresse de la cellule précédente
        p = p -> suiv; //le pointeur temporaire avance à la cellule suivante
    }//en sortie de boucle: p pointe sur NULL et p_prec pointe sur la dernier cellule
    if (p_prec == NULL){ //si la liste est vide (= jamais rentré dans la boucle while)
        ajout_en_tete(adr_tete, val); return;
    }//sinon (déjà rentrée dans le while et p == NULL OU val == p -> info) ajout au milieu (va l== p->info) OU en fin de liste (p == NULL ET val == p->info [ET p_prec -> suiv == NULL])
    ajout_en_tete(&p_prec -> suiv, val);
}


/****************************************CORPS****************************************/

int main()
{
    TPtr liste = NULL;
    /*liste = (TPtr) malloc(sizeof(TCell));
    if(liste == NULL) exit(1);*/

    int i;
    i=0;

    for(i=10; i>1; i-=2){
        ajout_en_tete(&liste, i);
        affiche_liste(liste);
    }

    //affiche_liste(liste);
    printf("\n");

    ajout_liste_triee(&liste, 5); affiche_liste(liste);
    ajout_pos_k(&liste, 7, 3); affiche_liste(liste);
    suppr_en_tete(&liste); affiche_liste(liste);
    suppr_pos_k(&liste, 3); affiche_liste(liste);
    ajout_en_queue(&liste, 88); affiche_liste(liste);
    suppr_en_queue(&liste); affiche_liste(liste);

    TPtr ptr = NULL;
    bool bool_trouver=FALSE;
    acces_val(liste, 10, &ptr, &bool_trouver);
    printf("%d\n", bool_trouver);
    printf("%d\n", ptr);




printf("\n\nTester si renvoie erreur personnalisé avec k > long_vect\n\n");

    suppr_pos_k(&liste, 18);
    ajout_pos_k(&liste, 7, 18);

printf("\n\nTester si renvoie erreur personnalisé avec pointeur null\n\n");

    TPtr liste2 = NULL;

    affiche_liste(liste2);
    printf("\n");

    suppr_en_tete(&liste2);
    suppr_pos_k(&liste2, 1);
    suppr_en_queue(&liste);

    bool_trouver=FALSE;
    acces_val(liste, 11, &ptr, &bool_trouver);
    printf("%d\n", bool_trouver);
    printf("%d\n", ptr);

    return 0;

}
