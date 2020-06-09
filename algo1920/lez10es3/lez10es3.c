/*
    Liste: cancellazione
    Inserimento in coda in una lista e cancellazione degli elementi
    di valore minore o uguale alla media dei valori degli elementi della lista stessa
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int val;
    struct nodo * next;
} Nodo;
typedef Nodo *NodoPtr;

NodoPtr insertInCoda(NodoPtr *lPtr, NodoPtr lastNodo, int value){
    NodoPtr newNodo = (NodoPtr) malloc(sizeof(Nodo));
    if(newNodo==NULL) exit(1);
    newNodo->val = value;
    newNodo->next = NULL;
    if(*lPtr == NULL){
        *lPtr = newNodo;
    }else{
        lastNodo->next = newNodo;
    }
    return newNodo;
}

void getValues(NodoPtr *lPtr, int *n, int *sum){
    scanf("%d", n);
    int i, value;
    NodoPtr next = NULL;
    for(i=0; i<*n; ++i){
        scanf("%d", &value);
        next = insertInCoda(lPtr, next, value);
        *sum += value;
    }
}

void deleteItems(NodoPtr *lPtr, int avg){
    if(*lPtr != NULL){
        if((*lPtr)->val <= avg){
            NodoPtr temp = (*lPtr);
            (*lPtr) = (*lPtr)->next;
            free(temp);
            deleteItems(lPtr, avg);
        }else{
            deleteItems(&((*lPtr)->next), avg);
        }
    }
}

void printList(NodoPtr nodo){
    if(nodo != NULL){
        printf("%d ", nodo->val);
        printList(nodo->next);
    }
}

int main(){
    NodoPtr lPtr = NULL;
    int n, sum = 0;
    getValues(&lPtr, &n, &sum);
    int avg = sum/n;
    printf("%d\n", avg);
    printList(lPtr);
    puts("");
    deleteItems(&lPtr, avg);
    printList(lPtr);
    puts("");
    return 0;
}