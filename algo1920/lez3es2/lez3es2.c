#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int get_intersect_count(int A_len, int *A, int B_len, int *B);

int main(){
    int A_len, B_len, i;
    scanf("%d", &A_len);
    int *A = malloc(A_len*sizeof(int));
    if(A==NULL)
        return 0;
    for(i=0;i<A_len;++i){
        scanf("%d", A+i);
    }
    scanf("%d", &B_len);
    int *B = malloc(B_len*sizeof(int));
    if(B==NULL)
        return 0;
    for(i=0;i<B_len;++i){
        scanf("%d", B+i);
    }

    // intersezione tra array
    printf("%d\n", get_intersect_count(A_len, A, B_len, B));
    
    return 0;
}

int get_intersect_count(int A_len, int *A, int B_len, int *B){
    if(A[A_len-1] < B[0] || A[0] > B[B_len-1])
        return 0;
    int i = 0, j = 0, count = 0;
    while(i < A_len && j < B_len){
        if(A[i] < B[j]){
            i++;
        }else if(A[i] > B[j]){
            j++;
        }else{
            // sono uguali
            i++;
            j++;
            count++;
        }
    }
    return count;
}