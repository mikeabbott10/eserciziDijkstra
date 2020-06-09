/*
 * Albero binario di ricerca: Visita
 * inizializza un albero binario di ricerca (senza ribilanciamento) coi valori forniti da input.
 * Poi visita l'albero e restituisce l'altezza
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int k;
    struct nodo *p;
    struct nodo *left;
    struct nodo *right;
} Nodo;
typedef Nodo * NodoPtr;

void insertInABR(NodoPtr *lPtr, NodoPtr newNodo){
    NodoPtr padre = NULL;
    NodoPtr currentNodo = *lPtr;
    while(currentNodo!=NULL){
        padre = currentNodo;
        if(currentNodo->k > newNodo->k){
            // scendo a sx
            currentNodo = currentNodo->left;
        }else{
            // scendo a dx
            currentNodo = currentNodo->right;
        }
    }
    if(padre == NULL){
        // inserimento della radice dell'albero
        *lPtr = newNodo;
    }else{
        // inserimento di una nuova foglia
        if(padre->k < newNodo->k){
            padre->right = newNodo;
        }else{
            padre->left = newNodo;
        }
    }
}

NodoPtr getNewNodo(int key){
    NodoPtr newNodo = malloc(sizeof(Nodo));
    newNodo->k = key;
    newNodo->p = NULL;
    newNodo->left = NULL;
    newNodo->right = NULL;
    return newNodo;
}

void getABR(int *n, NodoPtr *lPtr){
    scanf("%d", n);
    int i = 0;
    int newKey;
    NodoPtr nodo;
    for(i = 0; i<*n; i++){
        scanf("%d", &newKey);
        nodo = getNewNodo(newKey);
        insertInABR(lPtr, nodo);
    }
}

int max(int a, int b){
    return a<b ? b : a ;
}

int getAltezza(NodoPtr lPtr){
    if(lPtr==NULL) return 0;
    int altSx = getAltezza(lPtr->left);
    int altDx = getAltezza(lPtr->right);
    return 1 + max(altSx, altDx);
}

int main(){
    int n;
    NodoPtr lPtr = NULL;
    getABR(&n, &lPtr);
    printf("%d\n", getAltezza(lPtr));
    return 0;
}