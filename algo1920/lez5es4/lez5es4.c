
#include <stdlib.h>
#include <stdio.h>
#include<time.h>

void swap(int *a, int i, int j){
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

/* 
  !!!!!!!!!!!! D A  F A R E !!!!!!!!!!!!
  sx e dx sono le posizioni del primo e dell'ultimo elemento dell'array mentre 
  px è la posizione dell'elemento perno.
  La funzione deve restituire la posizione del perno dopo che gli elementi sono 
  stati partizionati.
*/
int distribuzione(int a[], int sx, int px, int dx){
    int j;
    int i = sx - 1;
    int m = 0;
    swap(a, dx, px); // porto il pivot in ultima posizione
    int pivot = a[dx];
    for(j = sx; j<dx; ++j){
        if(a[j] < pivot){
            if(m>0)
                swap(a, j, j-m);
            i++;
            swap(a, i, j-m);
        }else if(a[j] == pivot){
            if(m>0)
                swap(a, j-m, j);
        }else{
            m++;
        }
    }
    swap(a, j-m, dx);
    return j-m;
}

void quicksort( int a[], int sx, int dx ) {
  
    int perno, pivot;
    if( sx < dx ) {
        // DA IMPLEMENTARE: scelta del pivot. Scegliere una posizione a caso tra sx e dx inclusi.
        pivot = rand() % (dx-sx);
        pivot += sx;
        
        perno = distribuzione(a, sx, dx, dx); // separa gli elementi minori di a[pivot] 
                            // da quelli maggiori o uguali 
        /* Ordina ricorsivamente le due metà */
        quicksort(a, sx, perno-1);
        quicksort(a, perno+1, dx);
        
    }

}

/* Lettura di un array di interi da input. 
Il primo elemento è la lunghezza dell'array */
int legge(int **a, int *len) {

    int i;
    scanf("%d", len);
    if(*len <= 0) return 1;

    *a = (int *) malloc(*len * sizeof(int));
    if(*a == NULL) return 1;

    for( i = 0; i < *len; i++ ) 
        scanf("%d", (*a)+i);
    
    return 0;

}

int main() {
    
    int i, n, *A;

    if( legge(&A, &n)) return 1;

    srand(time(NULL));
    quicksort(A, 0, n-1);
    
    /* Stampa l'array ordinato */
    for( i = 0; i < n; i++ ) 
        printf("%d ", A[i]);
    return 0;
}