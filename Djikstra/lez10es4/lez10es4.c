/*
    Liste: somme suffisse
    stampa lista letta da input e somme suffisse (somma degli elementi successivi nella lista) di ogni elemento della lista
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

void getValues(NodoPtr *lPtr, int *n){
    scanf("%d", n);
    int i, value;
    NodoPtr next = NULL;
    for(i=0; i<*n; ++i){
        scanf("%d", &value);
        next = insertInCoda(lPtr, next, value);
    }
}

void printList(NodoPtr nodo){
    if(nodo != NULL){
        printf("%d ", nodo->val);
        printList(nodo->next);
    }
}

int getSums(NodoPtr lPtr){
    if(lPtr == NULL) return 0;
    return lPtr->val + getSums(lPtr->next);
}

void printSums(NodoPtr nodo){
    if(nodo!=NULL){
        printf("%d ", getSums(nodo->next));
        printSums(nodo->next);
    }
}

int main(){
    NodoPtr lPtr = NULL;
    int n;
    getValues(&lPtr, &n);
    printList(lPtr);
    puts("");
    printSums(lPtr);
    puts("");
    return 0;
}