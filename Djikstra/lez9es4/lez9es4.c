/**
 * Confronta alberi
 * inizializza DUE alberi binari di ricerca NON bilanciati coi valori forniti da input.
 * Poi ottiene una chiave K da input e verifica che le sequenze di chiavi 
 * incontrate nel cammino che dalla radice porta al nodo di chiave K nei due alberi coincidano
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

void getABR(int n, NodoPtr *lPtr){
    int i = 0;
    int newKey;
    NodoPtr nodo;
    for(i = 0; i<n; i++){
        scanf("%d", &newKey);
        nodo = getNewNodo(newKey);
        insertInABR(lPtr, nodo);
    }
}

int max(int a, int b){
    return a<b ? b : a ;
}

int camminiCoincidenti(NodoPtr lPtr1, NodoPtr lPtr2, int K){
    while(lPtr1!=NULL && lPtr2 != NULL){
        if(lPtr1->k != lPtr2->k)
            return 0;
        if(lPtr1->k > K){
            // scendo a sx
            lPtr1 = lPtr1->left;
            lPtr2 = lPtr2->left;
        }else if(lPtr1->k < K){
            // scendo a dx
            lPtr1 = lPtr1->right;
            lPtr2 = lPtr2->right;
        }else{
            // trovato
            return 1;
        }
    }
    return 0;
}

int main(){
    int N, K;
    NodoPtr lPtr1 = NULL;
    NodoPtr lPtr2 = NULL;
    scanf("%d %d", &N, &K);
    getABR(N, &lPtr1);
    getABR(N, &lPtr2);
    printf("%d\n", camminiCoincidenti(lPtr1, lPtr2, K));
    return 0;
}