#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int val;
    struct nodo *next;
    struct nodo *prec;
} Nodo;
typedef Nodo *NodoPtr;

void createList(NodoPtr *lPtr, int value){
    NodoPtr newNodo = (NodoPtr) malloc(sizeof(Nodo));
    if(newNodo==NULL) exit(1);
    newNodo->val = value;
    newNodo->prec = NULL;
    newNodo->next = NULL;
    *lPtr = newNodo;
}

NodoPtr insertInCoda(NodoPtr lastNodo, int value){
    NodoPtr newNodo = malloc(sizeof(Nodo));
    if(newNodo==NULL) exit(1);
    newNodo->val = value;
    newNodo->next = NULL;
    newNodo->prec = lastNodo;
    lastNodo->next = newNodo;
    return newNodo;
}

NodoPtr getValues(NodoPtr *lPtr, int *n){
    scanf("%d", n);
    int i, value;
    scanf("%d", &value);
    createList(lPtr, value);
    NodoPtr next = *lPtr;
    for(i=0; i<*n -1; ++i){
        scanf("%d", &value);
        next = insertInCoda(next, value);
    }
    return next;
}

void reversePrint(NodoPtr nodo){
    if(nodo != NULL){
        printf("%d\n", nodo->val);
        reversePrint(nodo->prec);
    }
}

int main(){
    NodoPtr lPtr = NULL;
    int n;
    NodoPtr lastNodo = getValues(&lPtr, &n);
    reversePrint(lastNodo);
    return 0;
}