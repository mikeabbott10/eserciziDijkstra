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

void MTF_cycle(NodoPtr *lPtr, int n){
    int valore, index = 0;
    NodoPtr precPtr;
    NodoPtr currPtr;
    while(index < n){
        scanf("%d", &valore);
        precPtr = NULL;
        currPtr = *lPtr;
        index = 0;
        while(currPtr != NULL){
            if(valore == currPtr->val){
                // trovato. Eseguire MTF
                printf("%d\n", index);
                if(precPtr != NULL){
                    precPtr->next = currPtr->next;
                    currPtr->next = *lPtr;
                    *lPtr = currPtr;
                }
                break;
            }
            precPtr = currPtr;
            currPtr = currPtr->next;
            index++;
        }
        currPtr = *lPtr;
    }
}

int main(){
    NodoPtr lPtr = NULL;
    int n;
    getValues(&lPtr, &n);
    MTF_cycle(&lPtr, n);
    printf("-1\n");
    return 0;
}