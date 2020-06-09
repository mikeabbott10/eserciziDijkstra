/*
    Tabelle hash: Inserimento
    Stampa lunghezza delle liste massima e numero di conflitti
*/

#include<stdlib.h>
#include<stdio.h>
#define p 999149

typedef struct nodo{
    int val;
    struct nodo * next;
} Nodo;
typedef Nodo *NodoPtr;

int h(int x, int a, int b, int n){
    return ((a*x + b) % p) % (2*n);
}

void insertNodo(NodoPtr * table, int val, int n, int a, int b){
    int index = h(val, a, b, n);
    NodoPtr newNodo = malloc(sizeof(NodoPtr));
    if(newNodo == NULL){
        exit(1);
    }
    newNodo->val = val;
    newNodo->next = table[index];
    table[index] = newNodo;
}

NodoPtr * initTable(int * n, int *a, int *b){
    scanf("%d %d %d", n, a, b);
    NodoPtr *table = (NodoPtr *) malloc(2*(*n) * sizeof(NodoPtr *));
    if(table == NULL){
        exit(1);
    }
    // init array of lists
    int i;
    for(i=0;i<2*(*n);i++){
        table[i] = NULL;
    }
    return table;
}
void getTable(NodoPtr *table, int n, int a, int b){
    int i, val, index;
    for(i=0;i<n;i++){
        scanf("%d", &val);
        insertNodo(table, val, n, a, b);
    }
}

int getLen(NodoPtr list){
    if(list==NULL) return 0;
    return 1 + getLen(list->next);
}

void printMaxLenAndCollisions(NodoPtr *table, int n){
    int max_len = 0, collisions = 0;
    int i, local_len;
    for(i=0; i<2*n; i++){
        local_len = getLen(table[i]);
        if(local_len>max_len){
            max_len = local_len;
        }
        if(local_len > 1){
            collisions += local_len-1;
        }
    }
    printf("%d\n%d\n", max_len, collisions);
}

int main(){
    int n, a, b;
    NodoPtr * table = initTable(&n, &a, &b);
    getTable(table, n, a ,b);
    printMaxLenAndCollisions(table, n);
    return 0;
}