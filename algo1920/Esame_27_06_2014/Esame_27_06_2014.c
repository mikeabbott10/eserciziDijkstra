/*
    Rubrica telefonica con tabelle hash.
    Stampa la K-esima lista, con K passato da input
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct nodo{
    char nome[100];
    char numero[20];
    struct nodo * next;
} Nodo;
typedef Nodo *NodoPtr;

int h(char* str, int n){
    int i;
    int sum = 0;
    for(i=0; i<strlen(str); ++i){
        sum += str[i];
    }
    return sum % (2*n);
}

void insertNodo(NodoPtr * table, char* nome, char* numero, int n){
    int index = h(nome, n);
    NodoPtr newNodo = malloc(sizeof(Nodo));
    if(newNodo == NULL) exit(1);
    strcpy(newNodo->nome, nome);
    strcpy(newNodo->numero, numero);

    NodoPtr currentNodo = table[index];
    NodoPtr precNodo = NULL;
    while(currentNodo != NULL && strcmp(currentNodo->nome, nome) <= 0){
        precNodo = currentNodo;
        currentNodo = currentNodo->next;
    }
    if(precNodo == NULL){
        // inserimento in testa
        newNodo->next = currentNodo;
        table[index] = newNodo;
    }else{
        newNodo->next = currentNodo;
        precNodo->next = newNodo;
    }
}

NodoPtr * initTable(int * n){
    scanf("%d", n);
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

void printList(NodoPtr nodo){
    if(nodo != NULL){
        printf("%s %s\n", nodo->nome, nodo->numero);
        printList(nodo->next);
    }
}

void getTable(NodoPtr *table, int n){
    int i;
    char nome[100], num_tel[20];
    for(i=0;i<n;i++){
        scanf("%s", nome);
        scanf("%s", num_tel);
        insertNodo(table, nome, num_tel, n);
    }
    /*for(i=0; i<2*n; i++){
        printf("\n%d: \t", i);
        printList(table[i]);
    }
    puts("");*/
}

int main(){
    int n;
    NodoPtr * table = initTable(&n);
    getTable(table, n);
    int K;
    scanf("%d", &K);
    printList(table[K]);
    return 0;
}