#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int get_subArray_max_sum(int A_len, int *A);

int main(){
    int A_len, i;
    scanf("%d", &A_len);
    int *A = malloc(A_len*sizeof(int));
    if(A==NULL)
        return 0;
    for(i=0;i<A_len;++i){
        scanf("%d", A+i);
    }
    
    printf("%d\n", get_subArray_max_sum(A_len, A));
    return 0;
}

int get_subArray_max_sum(int A_len, int *A){
    int max = 0, sum = 0, i = 0;
    for(i=0; i< A_len; ++i){
        if(sum > 0){
            sum += A[i];
        }else{
            sum = A[i];
        }

        if(sum > max){
            max = sum;
        }
    }
    return max;
}