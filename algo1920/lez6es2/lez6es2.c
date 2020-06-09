#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 100

void swap(int *a, int i, int j){
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}


int getArray(char ***a, int *len){
    int i;
    scanf("%d", len);
    if(*len <= 0) return 1;

    *a = (char **) malloc(*len * sizeof(char *));
    if(*a == NULL) return 1;

    for(i = 0; i < *len; i++ ){
        (*a)[i] = (char *) malloc(MAX_LEN * sizeof(char));
        if((*a)[i] == NULL) return 1;
        scanf("%s", (*a)[i]);
    }

    return 0;
}

int confronta(const void *a, const void *b){
    char *A = *(char **) a;
    char *B = *(char **) b;
    return -strcmp(A, B);
}

int main(){
    char **A;
    int n, i;
    if(getArray(&A, &n)) return 1;
    qsort(A, n, sizeof(char *), confronta);
    
    /* Stampa l'array ordinato */
    for( i = 0; i < n; i++ ) 
        printf("%s\n", A[i]);
    return 0;
}