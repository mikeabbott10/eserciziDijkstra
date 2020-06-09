#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STR_LEN 500
void insertionSort(char **A, int len);

int main(){
    int A_len;
    scanf("%d", &A_len);
    int i;
    char **A = malloc(A_len * sizeof(char *));
    for(i=0;i<A_len;++i){
        A[i] = malloc(STR_LEN * sizeof(char));
        scanf("%s", A[i]);
    }
    insertionSort(A, A_len);
    for(i=0;i<A_len;++i){
        printf("%s\n", A[i]);
    }
    return 0;
}

void insertionSort(char **A, int len){
    int i, j;
    char val[STR_LEN];
    for(i=1;i<len;++i){
        strcpy(val, A[i]);
        j = i-1;
        while(j >= 0 && strcmp(val, A[j]) < 0){
            strcpy(A[j+1],A[j]);
            j--;
        }
        strcpy(A[j+1], val);
    }
}