#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int x;
    int y;
} Punto;

int getArray(Punto **A, int *len){
    scanf("%d", len);
    if(*len<=0) return 1;

    *A = (Punto *) malloc(*len * sizeof(Punto));
    if(A==NULL) return 1;

    int i;
    for(i = 0; i < *len; ++i){
        scanf("%d %d", &((*A)[i].x), &((*A)[i].y));
    }
    
    return 0;
}

int confronta(const void *a, const void *b){
    Punto A = *(Punto *) a;
    Punto B = *(Punto *) b;
    if(A.x == B.x){
        return B.y - A.y;
    }else{
        return A.x - B.x;
    }
}

int main(){
    Punto *A; // array A di Punto
    int n, i;
    if(getArray(&A, &n)) return 1;
    qsort(A, n, sizeof(Punto), confronta);
    for(i = 0; i < n; ++i){
        printf("%d %d\n", A[i].x, A[i].y);
    }
    return 0;
}