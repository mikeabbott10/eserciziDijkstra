#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int i, int j){
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int getArray(int **A, int *len, int *j){
    scanf("%d", len);
    if(*len<=0) return 1;

    *A = (int *) malloc(*len * sizeof(int));
    if(A==NULL) return 1;

    int i;
    for(i = 0; i < *len; ++i){
        scanf("%d", (*A)+i);
        if((*A)[i] % 2 == 0){ // pari
            (*j)++;
            swap(*A, i, *j);
        }
    }
    return 0;
}

int confrontaPari(const void *a, const void *b){
    return *(int *) a - *(int *) b;
}

int confrontaDispari(const void *a, const void *b){
    return *(int *) b - *(int *) a;
}

int main(){
    int *A, n, i, j = -1;
    if(getArray(&A, &n, &j)) return 1;
    qsort(A, j+1, sizeof(int), confrontaPari);
    qsort(A+j+1, n-j-1, sizeof(int), confrontaDispari);
    for(i = 0; i < n; ++i){
        printf("%d\n", A[i]);
    }
    return 0;
}