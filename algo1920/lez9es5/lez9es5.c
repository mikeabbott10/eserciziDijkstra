/**
 * Albero ternario
 * inizializza un albero ternario di ricerca NON bilanciato coi valori forniti da input.
 * L'ordine di inserimento dei valori nell'albero coincide con quello della sequenza fornita.
 * Il valore da inserire viene confrontato con la chiave del nodo corrente.
 * Ci sono tre possibili casi in base al risultato del confronto:
 *      1.  se il valore è minore della chiave del nodo corrente, esso viene inserito
 *          ricorsivamente nel sottoalbero radicato nel figlio sinistro;
 *      2.  se  il valore è divisibile per la  chiave del nodo corrente, esso viene inserito 
 *          ricorsivamente nel sottoalbero radicato nel figlio centrale;
 *      3.  in ogni altro caso il valore viene inserito ricorsivamente nel sottoalbero 
 *          radicato nel figlio destro.
 * Restituisce il numero di nodi dell’albero che hanno tre figli.
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int k;
    struct nodo *left;
    struct nodo *center;
    struct nodo *right;
} Nodo;
typedef Nodo *NodoPtr;

NodoPtr getNewNodo(int newKey){
    NodoPtr newNodo = malloc(sizeof(Nodo));
    newNodo->k = newKey;
    newNodo->left = NULL;
    newNodo->center = NULL;
    newNodo->right = NULL;
    return newNodo;
}

int isFull(NodoPtr nodoPtr){
    return nodoPtr->center != NULL && nodoPtr->left != NULL && nodoPtr->right != NULL;
}

int isDivisible(int a, int b){
    // a is divisible by b
    return a%b==0;
}

void insertInABR(NodoPtr lPtr, NodoPtr newNodo){
    if(newNodo->k < lPtr->k){
        if(lPtr->left == NULL) 
            lPtr->left = newNodo;
        else
            insertInABR(lPtr->left, newNodo);
    }else if(isDivisible(newNodo->k, lPtr->k)){
        if(lPtr->center == NULL) 
            lPtr->center = newNodo;
        else
            insertInABR(lPtr->center, newNodo);
    }else{
        if(lPtr->right == NULL) 
            lPtr->right = newNodo;
        else
            insertInABR(lPtr->right, newNodo);
    }
}

void getABR(int *n, NodoPtr *lPtr){
    scanf("%d", n);
    int i, newKey;
    scanf("%d", &newKey);
    *lPtr = getNewNodo(newKey);
    for(i=1;i<*n;i++){
        scanf("%d", &newKey);
        insertInABR(*lPtr, getNewNodo(newKey));
    }
}

void treFigli(NodoPtr lPtr, int *fullNodes){
    if(lPtr != NULL){
        if(isFull(lPtr)){
            (*fullNodes)++;
        }
        treFigli(lPtr->left, fullNodes);
        treFigli(lPtr->center, fullNodes);
        treFigli(lPtr->right, fullNodes);
    }
}

int main(){
    int n;
    int fullNodes = 0;
    NodoPtr lPtr = NULL;
    getABR(&n, &lPtr);
    treFigli(lPtr, &fullNodes);
    printf("%d\n", fullNodes);
    return 0;
}