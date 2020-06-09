/*
    Tabelle hash: Inserimento con eliminazione dei duplicati
    Ottieni dati da input e memorizza in liste di trabocco. Stampa numero di conflitti, 
    lunghezza delle liste massima e numero totale di elementi distinti
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

int insertNodo(NodoPtr * table, int val, int n, int a, int b){
    int elemento_inserito = 0;
    int index = h(val, a, b, n);
    NodoPtr newNodo = malloc(sizeof(NodoPtr));
    if(newNodo == NULL){
        exit(1);
    }
    newNodo->val = val;
    // inserisco ordinatamente invece che in testa: è più efficente per trovare il numero di elementi distinti
    NodoPtr currentNodo = table[index];
    NodoPtr precNodo = NULL;
    while(currentNodo != NULL && currentNodo->val <= val){
        precNodo = currentNodo;
        currentNodo = currentNodo->next;
    }
    if(precNodo == NULL){
        // inserimento in testa
        elemento_inserito = 1;
        newNodo->next = currentNodo;
        table[index] = newNodo;
    }else{
        if(precNodo->val == val){
            elemento_inserito = 0;
            free(newNodo);
        }else{
            elemento_inserito = 1;
            newNodo->next = currentNodo;
            precNodo->next = newNodo;
        }
    }
    return elemento_inserito;
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

/*void printList(NodoPtr nodo){
    if(nodo != NULL){
        printf("%d ", nodo->val);
        printList(nodo->next);
    }
}*/

void getTable(NodoPtr *table, int n, int a, int b, int *elementi_distinti){
    int i, val, index;
    for(i=0;i<n;i++){
        scanf("%d", &val);
        *elementi_distinti += insertNodo(table, val, n, a, b);
    }
    /*for(i=0; i<2*n; i++){
        printf("\n%d: \t", i);
        printList(table[i]);
    }
    puts("");*/
}

int getLen(NodoPtr nodo){
    if(nodo==NULL) return 0;
    return 1 + getLen(nodo->next);
}

void printCollisionsAndMaxLen(NodoPtr *table, int n){
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
    printf("%d\n%d\n", collisions, max_len);
}

int main(){
    int n, a, b, elementi_distinti = 0;
    NodoPtr * table = initTable(&n, &a, &b);
    getTable(table, n, a ,b, &elementi_distinti);
    printCollisionsAndMaxLen(table, n);
    printf("%d\n", elementi_distinti);
    return 0;
}