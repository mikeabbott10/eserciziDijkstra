
#include <stdlib.h>
#include <stdio.h>
#include<time.h>
#include<string.h>
#define MAX_LEN 100

void swap(char **a, int i, int j){
    char *temp = a[i];
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
int distribuzione(char **a, int sx, int px, int dx){
    int j;
    int i = sx - 1;
    swap(a, dx, px); // porto il perno in ultima posizione
    char *perno = a[dx];
    for(j = sx; j<dx; ++j){
        if(strcmp(a[j], perno) <= 0){
            i++;
            swap(a, i, j);
        }
    }
    swap(a, i+1, dx);
    return i+1;
}

void quicksort(char **a, int sx, int dx ) {
  
    int perno, pivot;
    if( sx < dx ) {
        // DA IMPLEMENTARE: scelta del pivot. Scegliere una posizione a caso tra sx e dx inclusi.
        pivot = rand() % (dx-sx);
        pivot += sx;
        
        perno = distribuzione(a, sx, pivot, dx); // separa gli elementi minori di a[pivot] 
                            // da quelli maggiori o uguali 
        /* Ordina ricorsivamente le due metà */
        quicksort(a, sx, perno-1);
        quicksort(a, perno+1, dx);
        
    }

}

/* Lettura di un array di stringhe da input. 
Il primo elemento inserito da utente è la lunghezza dell'array */
int legge(char ***a, int *len) {

    int i;
    scanf("%d", len);
    if(*len <= 0) return 1;

    *a = (char **) malloc(*len * sizeof(char *));
    if(*a == NULL) return 1;

    for(i = 0; i < *len; i++ ){
        (*a)[i] = (char *) malloc(MAX_LEN * sizeof(char));
        if((*a)[i] == NULL) return 1;
        scanf("%s", (*a)[i]);
    }

    return 0;

}

int main() {
    
    int i, n;
    char **A;

    if( legge(&A, &n)) return 1;

    srand(time(NULL));
    quicksort(A, 0, n-1);
    
    /* Stampa l'array ordinato */
    for( i = 0; i < n; i++ ) 
        printf("%s\n", A[i]);
    return 0;
}