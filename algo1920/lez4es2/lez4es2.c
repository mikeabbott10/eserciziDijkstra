#include<stdio.h>
#include<stdlib.h>

void insertionSort(int *A, int len);

int main(){
    int A_len;
    scanf("%d", &A_len);
    int i;
    int *A = malloc(A_len*sizeof(int));
    for(i=0;i<A_len;++i){
        scanf("%d", A+i);
    }
    insertionSort(A, A_len);
    for(i=0;i<A_len;++i){
        printf("%d\n", A[i]);
    }
    return 0;
}

void insertionSort(int *A, int len){
    int i, j, val;
    for(i=1;i<len;++i){
        val = A[i];
        j = i-1;
        while(j >= 0 && val < A[j]){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = val;
    }
}