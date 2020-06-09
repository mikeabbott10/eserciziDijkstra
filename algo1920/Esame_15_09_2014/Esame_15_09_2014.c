/*
 * Albero binario di ricerca
 * stampa in ordine crescente le chiavi dei nodi che soddisfano la condizione L(u) > R(u)
 */

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct nodo{
    int k;
    int visSx;
    int visDx;
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
    newNodo->visDx = 0;
    newNodo->visSx = 0;
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

void visitaSx(NodoPtr nodo){
    if(nodo != NULL && nodo->left != NULL)
        nodo->visSx += (1 + (nodo->left)->visSx);
}

void visitaDx(NodoPtr nodo){
    if(nodo != NULL && nodo->right != NULL)
        nodo->visDx += (1 + (nodo->right)->visDx);
}

void getVisite(NodoPtr nodo){
    if(nodo!=NULL){
        getVisite(nodo->left);
        getVisite(nodo->right);
        visitaSx(nodo);
        visitaDx(nodo);
    }
}

void stampaNodi(NodoPtr nodo){
    // visita simmetrica => ordine crescente
    if(nodo!=NULL){
        stampaNodi(nodo->left);
        if(nodo->visSx > nodo->visDx){
            // stampa chiave se L(u) > R(u)
            printf("%d\n", nodo->k);
        }
        stampaNodi(nodo->right);
    }
}

int main(){
    int n, max_sum = 0, min_k = INT_MAX;
    NodoPtr lPtr = NULL;
    getABR(&n, &lPtr);
    getVisite(lPtr);
    stampaNodi(lPtr);
    return 0;
}