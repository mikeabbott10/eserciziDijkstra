#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void mergeSort(int *A, int r, int p);
void merge(int*A, int r, int q, int p);
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

    // ordino gli array
    mergeSort(A, 0, A_len-1);
    mergeSort(B, 0, B_len-1);

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

void mergeSort(int *A, int r, int p){
    int q;
    if(r < p){
        q = (r+p)/2;
        mergeSort(A,r,q);
        mergeSort(A,q+1,p);
        merge(A,r,q,p);
    }
}

void merge(int*A, int r, int q, int p){
    int l1 = r;
    int l2 = q + 1;
    int i = 0;
    int *b = malloc((p-r+1) * sizeof(int));
    if(b==NULL)
        exit(1);
    while(l1 <= q && l2 <= p){
        if(A[l1] <= A[l2])
            b[i] = A[l1++];
        else
            b[i] = A[l2++];
        i++;
    }
   
    while(l1 <= q)    
        b[i++] = A[l1++];

    while(l2 <= p)   
        b[i++] = A[l2++];

    for(i = r; i <= p; i++)
        A[i] = b[i-r];
}