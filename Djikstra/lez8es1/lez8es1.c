#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int val;
    struct nodo * next;
} Nodo;
typedef Nodo *NodoPtr;

void createList(NodoPtr *lPtr, int value){
    NodoPtr newNodo = (NodoPtr) malloc(sizeof(Nodo));
    if(newNodo==NULL) exit(1);
    newNodo->val = value;
    newNodo->next = NULL;
    *lPtr = newNodo;
}

NodoPtr insertInCoda(NodoPtr lastNodo, int value){
    NodoPtr newNodo = malloc(sizeof(Nodo));
    if(newNodo==NULL) exit(1);
    newNodo->val = value;
    newNodo->next = NULL;
    lastNodo->next = newNodo;
    return newNodo;
}

void getValues(NodoPtr *lPtr, int *n){
    scanf("%d", n);
    int i, value;
    scanf("%d", &value);
    createList(lPtr, value);
    NodoPtr next = *lPtr;
    for(i=0; i<*n -1; ++i){
        scanf("%d", &value);
        next = insertInCoda(next, value);
    }
}

void reversePrint(NodoPtr lPtr){
    if(lPtr != NULL){
        reversePrint(lPtr->next);
        printf("%d\n", lPtr->val);
    }
}

int main(){
    NodoPtr lPtr = NULL;
    int n;
    getValues(&lPtr, &n);
    reversePrint(lPtr);
    return 0;
}