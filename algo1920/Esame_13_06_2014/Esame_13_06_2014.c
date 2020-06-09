/*
 * Studente organizza esami,
 * Uso lista monodirezionale e qsort per ordinamento array
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct esame{
    char sigla[100];
    int crediti;
    int difficolta;
    struct esame* next;
} Esame;
typedef Esame* EsamePtr;

void printList(EsamePtr nodo){
    if(nodo != NULL){
        printf("C: %d, D: %d, S: %s\n", nodo->crediti, nodo->difficolta, nodo->sigla);
        printList(nodo->next);
    }
}

void insertEsame(EsamePtr* ePtr, char* sigla, int cred, int diff){
    EsamePtr newEsame = malloc(sizeof(Esame));
    strcpy(newEsame->sigla, sigla);
    newEsame->crediti = cred;
    newEsame->difficolta = diff;

    EsamePtr precEs = NULL;
    EsamePtr currEs = *ePtr;
    while(currEs != NULL && currEs->crediti > cred){
        precEs = currEs;
        currEs = currEs->next;
    }
    if(currEs!=NULL){
        // parità di crediti
        while(currEs != NULL && currEs->crediti == cred && currEs->difficolta < diff){
            precEs = currEs;
            currEs = currEs->next;
        }
        if(currEs != NULL){
            // parità di difficoltà
            while(currEs != NULL && currEs->crediti == cred && currEs->difficolta == diff && strcmp(currEs->sigla, sigla) < 0){
                precEs = currEs;
                currEs = currEs->next;
            }
        }
    }
    if(precEs == NULL){
        // inserimento in testa
        newEsame->next = currEs;
        *ePtr = newEsame;
    }else{
        newEsame->next = currEs;
        precEs->next = newEsame;
    }
}


void getValues(EsamePtr* ePtr, int* K, int* N){
    scanf("%d %d", K, N);
    int i, cred, diff;
    char sigla[100];
    for(i=0; i<*N; i++){
        scanf("%s", sigla);
        scanf("%d %d", &cred, &diff);
        insertEsame(ePtr, sigla, cred, diff);
    }
    //printList(*ePtr);
}

int getEsamiDaDare(char** sigleEsamiDaDare, EsamePtr nodo, int creditiRimanenti){
    if(nodo != NULL && creditiRimanenti != 0){
        if(nodo->crediti <= creditiRimanenti){
            *sigleEsamiDaDare = nodo->sigla;
            return 1 + getEsamiDaDare( sigleEsamiDaDare + 1, nodo->next, creditiRimanenti - nodo->crediti);
        }else{
            return getEsamiDaDare(sigleEsamiDaDare, nodo->next, creditiRimanenti);
        }
    }else{
        return 0;
    }
    
}

int confronta(const void *a, const void *b){
    char* A = *(char **) a;
    char* B = *(char **) b;
    return strcmp(A, B);
}

int main(){
    EsamePtr ePtr = NULL;
    int K, N;
    getValues(&ePtr, &K, &N);
    char* sigleEsamiDaDare[100];
    int nEsamiDaDare = getEsamiDaDare(sigleEsamiDaDare, ePtr, K);
    qsort(sigleEsamiDaDare, nEsamiDaDare, sizeof(char *), confronta);
    int i;
    for(i=0; i< nEsamiDaDare; ++i){
        printf("%s\n", sigleEsamiDaDare[i]);
    }
    return 0;
}