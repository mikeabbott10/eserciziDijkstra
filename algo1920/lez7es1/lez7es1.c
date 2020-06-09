/**
 * K stringhe più frequenti
 * Legge da tastiera due numeri N e K e N stringhe
 * Stampa le K stringhe più frequenti tra quelle in input
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 100

typedef struct{
    char *str;
    int times;
} Entry;

int getValues(char ***S, int *N, int *K){
    //get N
    scanf("%d", N);
    if(*N <= 0) return 1;
    //get K
    scanf("%d", K);
    // get string array
    (*S) = (char **) malloc(*N * sizeof(char *));
    int i;
    for(i=0; i<*N; ++i){
        (*S)[i] = (char *) malloc(MAX_LEN * sizeof(char));
        if((*S)[i] == NULL) return 1;
        scanf("%s", (*S)[i]);
    }
    return 0;
}

int getEntriesCount(Entry **A, char **S, const int N){
    int i, j = 0;
    (*A)[0].str = S[0];
    (*A)[0].times = 1;
    for(i=0; i<N; ++i){
        if(strcmp(S[i], (*A)[j].str) == 0){
            (*A)[j].times ++;
        }else{
            j++;
            (*A)[j].str = S[i];
            (*A)[j].times = 1;
        }
    }
    return j;
}

int alphaCmp(const void *a, const void *b){
    char *A = *(char **) a;
    char *B = *(char **) b;
    return strcmp(A, B);
}

int timesCmp(const void *a, const void *b){
    Entry A = *(Entry *) a;
    Entry B = *(Entry *) b;
    return B.times - A.times;
}

int entryAlphaCmp(const void *a, const void *b){
    Entry A = *(Entry *) a;
    Entry B = *(Entry *) b;
    return strcmp(A.str, B.str);
}

int main(){
    int N, K;
    char **S; // string array
    Entry *A; // entry array
    if(getValues(&S, &N, &K)) return 1;
    A = (Entry *) malloc(N * sizeof(Entry));
    if(A==NULL) return 1;
    // ordina lessicograficamente gli elementi di S
    qsort(S, N, sizeof(char *), alphaCmp);
    // conta stringhe presenti. Avremo M stringhe, con M<=N
    int M = getEntriesCount(&A, S, N);
    // ordina per numero di ripetizioni gli elementi di A
    qsort(A, M, sizeof(Entry), timesCmp);
    // ordina lessicograficamente i primi K elementi di A
    qsort(A, K, sizeof(Entry), entryAlphaCmp);
    // stampa i primi K elementi
    int i;
    for(i=0; i<K; ++i){
        printf("%s\n", A[i].str);
    }
    return 0;
}