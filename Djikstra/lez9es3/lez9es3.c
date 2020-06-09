/*
 * Albero binario di ricerca: ordinamento
 * inizializza un albero binario di ricerca (senza ribilanciamento) coi valori forniti da input.
 * Poi stampa i valori nell'albero in ordine non decrescente
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

// Visita simmetrica => lista crescente
void stampaListaCrescente(NodoPtr lPtr){
    if(lPtr!=NULL){
        stampaListaCrescente(lPtr->left);
        printf("%d\n", lPtr->k);
        stampaListaCrescente(lPtr->right);
    }
}

int main(){
    int n;
    NodoPtr lPtr = NULL;
    getABR(&n, &lPtr);
    stampaListaCrescente(lPtr);
    return 0;
}