/*
 * Alice e Bob hanno massimo 15 oggetti a testa. Ne devono scegliere 15 in totale, come coppia.
 * Uso tabella hash con liste di trabocco ordinate lessicograficamente
 * Copio tabella su array e uso qsort per ordinare per valore
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define maxStrLen 100

typedef struct nodo{
    char oggetto[maxStrLen];
    int val;
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

void insertNodo(NodoPtr * table, char* str, int val, int n){
    int index = h(str, n);
    NodoPtr newNodo = malloc(sizeof(Nodo));
    if(newNodo == NULL){
        exit(1);
    }
    newNodo->val = val;
    strcpy(newNodo->oggetto, str);
    NodoPtr currentNodo = table[index];

    while(currentNodo != NULL){
        if(strcmp(currentNodo->oggetto, str) != 0){
            currentNodo = currentNodo->next;
        }else{
            if(currentNodo->val < val){
                currentNodo->val = val;
            }
            free(newNodo);
            return;
        }
    }
    // inserimento in testa
    newNodo->next = table[index];
    table[index] = newNodo;
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

void getTable(NodoPtr *table, int n){
    int i, val, index;
    char str[maxStrLen];
    for(i=0;i<n;i++){
        scanf("%s", str);
        scanf("%d", &val);
        insertNodo(table, str, val, n);
    }
    /*
    for(int j=0; j<2*n; j++){
        printf("\n%d: \t", j);
        printList(table[j]);
    }
    puts("");
    */
}

int getLen(NodoPtr nodo){
    if(nodo==NULL) return 0;
    return 1 + getLen(nodo->next);
}

void putListInArray(NodoPtr nodo, NodoPtr oggetti, int* index){
    if(nodo != NULL){
        strcpy(oggetti[*index].oggetto, nodo->oggetto);
        oggetti[*index].val = nodo->val;
        oggetti[*index].next = NULL;
        //printf("%s, %d ", nodo->oggetto, nodo->val);
        //printf(" in: oggetti[%d]\n", *index);
        *index += 1;
        putListInArray(nodo->next, oggetti, index);
    }
}

int confronta(const void *a, const void *b){
    Nodo A = *(Nodo *) a;
    Nodo B = *(Nodo *) b;
    if(A.val == B.val){
        return strcmp(A.oggetto, B.oggetto);
    }else{
        return B.val - A.val;
    }
}

void printMaxValObjects(NodoPtr* table, int n){
    int j;
    NodoPtr oggetti = malloc(n * sizeof(Nodo));
    if(oggetti==NULL) exit(1);
    int i = 0;
    for(j=0; j<2*n; j++){
        //printf("\n%d: \t", j);
        putListInArray(table[j], oggetti, &i);
        //puts("---------------");
    }
    //puts("");
    qsort(oggetti, n, sizeof(Nodo), confronta);
    for(j=0; j < n && j < 15; j++){
        printf("%s\n", oggetti[j].oggetto);
    }
}

int main(){
    int n;
    NodoPtr * table = initTable(&n);
    getTable(table, n);
    printMaxValObjects(table, n);
    return 0;
}