#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct nodo{
    int k;
    int color;
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

NodoPtr getNewNodo(int key, int color){
    NodoPtr newNodo = malloc(sizeof(Nodo));
    newNodo->k = key;
    newNodo->color = color;
    newNodo->left = NULL;
    newNodo->right = NULL;
    return newNodo;
}

void getABR(int *n, NodoPtr *lPtr){
    scanf("%d", n);
    int i = 0;
    int newKey, color;
    NodoPtr nodo;
    for(i = 0; i<*n; i++){
        scanf("%d", &newKey);
        scanf("%d",&color);
        nodo = getNewNodo(newKey, color);
        insertInABR(lPtr, nodo);
    }
}

int max(int a, int b){
    return a<b ? b : a ;
}

int getAR(NodoPtr lPtr){
    if(lPtr==NULL) return 0;
    int ARsx = getAR(lPtr->left);
    int ARdx = getAR(lPtr->right);
    if(ARsx >= 0 && ARdx >= 0 && abs(ARsx - ARdx) <= 1){
        // condizione verificata
        return (lPtr->color == 0) ? 1 + max(ARsx, ARdx) : max(ARsx, ARdx);
    }
    // condizione non piu verificata
    return -1;
}

int main(){
    int n;
    NodoPtr lPtr = NULL;
    getABR(&n, &lPtr);
    if(getAR(lPtr) >= 0){
        puts("TRUE");
    }else{
        puts("FALSE");
    }
    return 0;
}