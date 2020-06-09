/*
 * Albero binario di ricerca
 * stampa chiave minima del/dei cammino/i di somma massima
 */

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct nodo{
    int k;
    int color; // usato per colorare il nodo, individua quindi il cammino di somma max
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
    newNodo->color = 0;
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

int getMaxSumPath(NodoPtr lPtr){
    if(lPtr == NULL)
        return 0;
    int STsx = getMaxSumPath(lPtr->left);
    int STdx = getMaxSumPath(lPtr->right);
    int STmax;
    if(STsx >= STdx){
        STmax = STsx + lPtr->k;
        // colora figlio sx
        if(lPtr->left != NULL){
            (lPtr->left)->color = 1;
        }
    }else{
        STmax = STdx + lPtr->k;
        // colora figlio dx
        if(lPtr->right != NULL){
            (lPtr->right)->color = 1;
        }
    }
    return STmax;
}

int get_min_k(NodoPtr lPtr, int *k_min){
    if(lPtr->left != NULL && (lPtr->left)->color == 1){
        // max_sum_path scende a sx quindi finchè scendo a sx aggiorno la chiave minima
        *k_min = (lPtr->left)->k;
        get_min_k(lPtr->left, k_min);
    }
    // se scendo a dx ho già trovato la chiave minima
}

int getMinK(NodoPtr root){
    int k_min;
    if(root!=NULL){
        k_min = root->k;
        get_min_k(root, &k_min);
    }else{
        k_min = 0;
    }
    return k_min;
}

int main(){
    int n, max_sum = 0, min_k = INT_MAX;
    NodoPtr lPtr = NULL;
    getABR(&n, &lPtr);
    getMaxSumPath(lPtr);
    min_k = getMinK(lPtr);
    printf("%d\n", min_k);
    return 0;
}