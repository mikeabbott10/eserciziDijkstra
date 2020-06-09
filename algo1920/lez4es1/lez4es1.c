#include<stdio.h>
#include<stdlib.h>

void selectionSort(int *A, int len);
void swap(int *A, int i, int j);

int main(){
    int A_len;
    scanf("%d", &A_len);
    int i;
    int *A = malloc(A_len*sizeof(int));
    for(i=0;i<A_len;++i){
        scanf("%d", A+i);
    }
    selectionSort(A,A_len);
    for(i=0;i<A_len;++i){
        printf("%d\n", A[i]);
    }
    return 0;
}

void selectionSort(int *A, int len){
    int i, j, min_index;
    for(j=0; j<len-1; ++j){
        min_index = j;
        for(i=j+1;i<len;++i){
            if(A[i] < A[min_index]){
                min_index = i;
            }
        }
        swap(A, min_index, j);
    }
}

void swap(int *A, int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}