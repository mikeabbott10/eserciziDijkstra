#include<stdio.h>
#include<stdlib.h>

void print_union(int A_len, int *A, int B_len, int *B);

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
    print_union(A_len, A, B_len, B);
    return 0;
}

void print_union(int A_len, int *A, int B_len, int *B){
    int i = 0;
    if(A[A_len-1] < B[0]){
        for(i=0;i<A_len;++i){
            printf("%d\n", A[i]);
        }
        for(i=0;i<B_len;++i){
            printf("%d\n", B[i]);
        }
    }else if(A[0] > B[B_len-1]){
        for(i=0;i<B_len;++i){
            printf("%d\n", B[i]);
        }
        for(i=0;i<A_len;++i){
            printf("%d\n", A[i]);
        }
    }

    i = 0;
    int j = 0;
    while(i < A_len && j < B_len){
        if(A[i] < B[j]){
            printf("%d\n", A[i++]);
        }else if(A[i] > B[j]){
            printf("%d\n", B[j++]);
        } // non sono uguali per hp
    }

    while(i < A_len){
        printf("%d\n", A[i++]);
    }

    while(j < B_len){
        printf("%d\n", B[j++]);
    }
}