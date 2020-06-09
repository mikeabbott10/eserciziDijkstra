/**
 * Punti colorati
 * 
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int x;
    int y;
    int c;
} Punto;

typedef struct{
    // (x1,y1) downsx
    int x1;
    int y1;
    // (x2,y2) updx
    int x2;
    int y2;
} Interrogazione;


int getValues(Punto **A, int *N, Interrogazione **Q, int *M){
    scanf("%d", N);
    scanf("%d", M);
    *A = (Punto *) malloc(*N *sizeof(Punto));
    *Q = (Interrogazione *) malloc(*M *sizeof(Interrogazione));
    if(A==NULL || Q==NULL) return 1;
    int i;
    // get punti colorati
    for(i=0; i<*N; ++i){
        scanf("%d %d %d", &((*A)[i].x), &((*A)[i].y), &((*A)[i].c));
        // printf("%d %d %d\n", (*A)[i].x, (*A)[i].y, (*A)[i].c);
    }
    // get interrogazioni
    for(i=0; i<*M; ++i){
        scanf("%d %d %d %d", &((*Q)[i].x1), &((*Q)[i].y1), &((*Q)[i].x2), &((*Q)[i].y2));
        // printf("%d %d %d %d\n", (*Q)[i].x1, (*Q)[i].y1, (*Q)[i].x2, (*Q)[i].y2);
    }
    return 0;
}

/*
    A parità di coordinata x si ordina per coordinata y    
*/
int coordCmp(const void *A, const void *B){
    Punto p1 = *(Punto *) A;
    Punto p2 = *(Punto *) B;
    if(p1.x == p2.x){
        return p1.y - p2.y;
    }
    return p1.x - p2.x;
}

int colorCmp(const void *A, const void *B){
    Punto p1 = *(Punto *) A;
    Punto p2 = *(Punto *) B;
    return p1.c - p2.c;
}

int getNumberOfColors(Punto *A, int N, Interrogazione I){
    int count = 0;
    int i = 0;
    int downSxIndex = -1;
    int upDxIndex = -1;
    // cerco il primo indice in A che appartiene al rettangolo di interrogazione
    while(i<N && downSxIndex == -1){
        if( A[i].x >= I.x1 && A[i].x <= I.x2){
            if( A[i].y >= I.y1 && A[i].y <= I.y2){
                downSxIndex = i;
            }
        }
        ++i;
    }
    if(downSxIndex == -1) return 0; // non ci sono punti all'interno del rettangolo di interrogazione
    // cerco l'ultimo indice in A che appartiene al rettangolo di interrogazione
    while(i<N && upDxIndex == -1){
        if( A[i].x == I.x2){
            if( A[i].y >= I.y2){
                upDxIndex = i;
            }
        }else if(A[i].x > I.x2){
            upDxIndex = i;
        }
        ++i;
    }
    // in input vengono passati punti con colori multipli...
    if(upDxIndex != -1){
        while(i<N && upDxIndex){
            if(A[i].x == A[i-1].x && A[i].y == A[i-1].y){
                ++upDxIndex;
                ++i;
            }else
                break;
        }
    }else{
        upDxIndex = N-1;
    }
    // inizializzo B
    int B_len = upDxIndex - downSxIndex +1;
    Punto *B = (Punto *) malloc(B_len* sizeof(Punto));
    for(i = downSxIndex; i<=upDxIndex; ++i){
        B[i - downSxIndex] = A[i];
        if(A[i].y < I.y1 || A[i].y > I.y2 || A[i].x < I.x1 || A[i].x > I.x2){
            B[i-downSxIndex].c = -1;
        }
    }
    // ordino B per colore
    qsort(B, B_len, sizeof(Punto), colorCmp); // B_len * log(B_len)
    // conto i colori diversi nell'array B ordinato per colori
    int precCol = -2;
    for(i=0; i<B_len; ++i){
        if(B[i].c != -1 && B[i].c != precCol){
            //printf("%d - ", B[i].c);
            precCol = B[i].c;
            count++;
        }
    }
    free(B);
    return count;
}

int main(){
    Punto *A;
    int N; // numero punti colorati
    Interrogazione *Q;
    int M; // numero interrogazioni
    if(getValues(&A, &N, &Q, &M)) return 1;
    // ordino A per coordinate
    qsort(A, N, sizeof(Punto), coordCmp); // NlogN
    int i;
    /*puts("A ORDINATO:");
    puts("----------------------------------");
    for(i=0; i<N; ++i){
        printf("%d %d %d\n", A[i].x, A[i].y, A[i].c);
    }
    puts("----------------------------------");*/
    for(i=0; i<M; ++i){
        printf("%d\n", getNumberOfColors(A, N, Q[i]));
    }
    return 0;
}