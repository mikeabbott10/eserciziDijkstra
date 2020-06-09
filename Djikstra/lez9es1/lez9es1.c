/**
 * Albero binario di ricerca:  Ricerca
 * inizializza un albero binario di ricerca (senza ribilanciamento) coi valori forniti da input.
 * Poi cerca nell'albero un intero inserito da tastiera
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

int getDepth(NodoPtr lPtr, int i){
    int d = -1;
    while(lPtr!=NULL){
        d++;
        if(lPtr->k > i){
            // scendo a sx
            lPtr = lPtr->left;
        }else if(lPtr->k < i){
            // scendo a dx
            lPtr = lPtr->right;
        }else{
            return d;
        }
    }
    return -1;
}

int main(){
    int n;
    int i;
    int depth;
    NodoPtr lPtr = NULL;
    getABR(&n, &lPtr);
    while(scanf("%d", &i) && i >= 0){
        depth = getDepth(lPtr, i);
        if(depth>=0){
            printf("%d\n", depth);
        }else{
            puts("NO");
        }
    }
    return 0;
}