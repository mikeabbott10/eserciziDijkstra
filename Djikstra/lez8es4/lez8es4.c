#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
    int val;
    int times;
    struct nodo *next;
    struct nodo *prec;
} Nodo;
typedef Nodo *NodoPtr;

void createList(NodoPtr *lPtr, int value){
    NodoPtr newNodo = (NodoPtr) malloc(sizeof(Nodo));
    if(newNodo==NULL) exit(1);
    newNodo->val = value;
    newNodo->times = 0;
    newNodo->prec = NULL;
    newNodo->next = NULL;
    *lPtr = newNodo;
}

NodoPtr insertInCoda(NodoPtr lastNodo, int value){
    NodoPtr newNodo = malloc(sizeof(Nodo));
    if(newNodo==NULL) exit(1);
    newNodo->val = value;
    newNodo->times = 0;
    newNodo->next = NULL;
    newNodo->prec = lastNodo;
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

void shiftBack(NodoPtr nodo){
    int tempVal = nodo->val;
    int tempTimes = nodo->times;

    nodo->val = (nodo->prec)->val;
    (nodo->prec)->val = tempVal;

    nodo->times = (nodo->prec)->times;
    (nodo->prec)->times = tempTimes;
}

void sort(NodoPtr nodo){
    while(nodo != NULL){
        if((nodo->prec) != NULL && (nodo->prec)->times < nodo->times){
            shiftBack(nodo);
        }else{
            break;
        }
        nodo = nodo->prec;
    }
}

void cycle(NodoPtr *lPtr, int n){
    int valore, index;
    NodoPtr currPtr;
    while(index < n){
        scanf("%d", &valore);
        currPtr = *lPtr;
        index = 0;
        while(currPtr != NULL){
            if(valore == currPtr->val){
                // trovato
                printf("%d\n", index);
                ++ currPtr->times;
                sort(currPtr);
                break;
            }
            currPtr = currPtr->next;
            index ++;
        }
        currPtr = *lPtr;
    }
}

int main(){
    NodoPtr lPtr = NULL;
    int n;
    getValues(&lPtr, &n);
    cycle(&lPtr, n);
    printf("-1\n");
    return 0;
}