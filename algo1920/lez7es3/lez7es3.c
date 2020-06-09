/**
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 20

typedef struct string{
    char c;
    struct string *next;
} String;
typedef String * StringPtr;

typedef struct nodo{
    char stringa[20];
    struct nodo * next;
} Nodo;
typedef Nodo * NodoPtr;

typedef struct group{
    char ang[20]; // anagramma principale
    NodoPtr stringhe;
    struct group * next;
} Group;
typedef Group * GroupPtr;

void insertChar(StringPtr *lPtr, char c){
    StringPtr newChar = (StringPtr) malloc(sizeof(String));
    if(newChar==NULL) exit(1);
    newChar->c = c;
    StringPtr currentNodo = *lPtr;
    StringPtr precNodo = NULL;
    while(currentNodo != NULL && currentNodo->c <= c){
        precNodo = currentNodo;
        currentNodo = currentNodo->next;
    }
    if(precNodo == NULL){
        // inserimento in testa
        newChar->next = currentNodo;
        *lPtr = newChar;
    }else{
        newChar->next = currentNodo;
        precNodo->next = newChar;
    }
}

char * getAnagrammaPrincipale(char *str){
    int str_len = strlen(str);
    char * mainAng = (char *) malloc(str_len * sizeof(char));
    StringPtr angPrincipaleList = NULL;
    // ottenere anagramma principale e memorizzarlo in mainAng
    int i;
    for(i=0; i<str_len; ++i){
        insertChar(&angPrincipaleList, str[i]);
    }
    for(i=0; i<str_len; ++i){
        mainAng[i] = angPrincipaleList->c;
        angPrincipaleList = angPrincipaleList->next;
    }
    free(angPrincipaleList);
    return mainAng;
}

NodoPtr getNewNodo(char *stringa){
    NodoPtr newNodo = (NodoPtr) malloc(sizeof(Nodo));
    if(newNodo==NULL) exit(1);
    strcpy(newNodo->stringa,stringa);
    newNodo->next = NULL;
    return newNodo;
}

GroupPtr getNewGroup(char *anagrammaPrincipale, char *stringa){
    GroupPtr newGroup = (GroupPtr) malloc(sizeof(Group));
    if(newGroup==NULL) exit(1);
    strcpy(newGroup->ang, anagrammaPrincipale);
    //printf("%s\n", newGroup->ang);
    newGroup->stringhe = getNewNodo(stringa);
    newGroup->next = NULL;
    return newGroup;
}

void insertNodo(NodoPtr *lPtr, NodoPtr newNodo){
    NodoPtr currentNodo = *lPtr;
    NodoPtr precNodo = NULL;
    while(currentNodo != NULL && strcmp(currentNodo->stringa, newNodo->stringa) <= 0){
        precNodo = currentNodo;
        currentNodo = currentNodo->next;
    }
    if(precNodo == NULL){
        // inserimento in testa
        newNodo->next = currentNodo;
        *lPtr = newNodo;
    }else{
        newNodo->next = currentNodo;
        precNodo->next = newNodo;
    }
}

void insertString(GroupPtr *aPtr, char* stringa){
    char *anagrammaPrincipale = getAnagrammaPrincipale(stringa);
    if(*aPtr == NULL){
        GroupPtr newGroup = getNewGroup(anagrammaPrincipale, stringa);
        *aPtr = newGroup;
    }else{
        // scorro i gruppi (aPtr) fino a che non trovo un aPtr->ang maggiore lessicograficamente di anagrammaPrincipale (creo nuovo gruppo e lo inserisco)
        // se trovo aPtr->ang uguale lessicograficamente ad anagrammaPrincipale (NON creo nuovo gruppo e inserisco nuova stringa in aPtr->stringhe)
        GroupPtr currentNodo = *aPtr;
        GroupPtr precNodo = NULL;
        while(currentNodo != NULL && strcmp(currentNodo->ang, anagrammaPrincipale) <= 0){
            precNodo = currentNodo;
            currentNodo = currentNodo->next;
        }
        if(precNodo == NULL){
            // inserimento di un nuovo GroupPtr in testa
            GroupPtr newGroup = getNewGroup(anagrammaPrincipale, stringa);
            newGroup->next = currentNodo;
            *aPtr = newGroup;
        }else{
            if(strcmp(precNodo->ang, anagrammaPrincipale)==0){
                // inserisco nuova stringa nella lista precNodo->stringhe
                NodoPtr newNodo = getNewNodo(stringa);
                insertNodo(&(precNodo->stringhe), newNodo);
            }else{
                // inserisco nuovo gruppo dopo precNodo e prima di currentNodo
                GroupPtr newGroup = getNewGroup(anagrammaPrincipale, stringa);
                newGroup->next = currentNodo;
                precNodo->next = newGroup;
            }
        }
    }
}

int getValues(GroupPtr * aPtr, int *N){
    //get N
    scanf("%d", N);
    if(*N <= 0) return 1;
    char *tempStr;
    int i;
    for(i=0; i<*N; ++i){
        tempStr = (char *) malloc(MAX_LEN * sizeof(char));
        if(tempStr == NULL) return 1;
        scanf("%s", tempStr);
        insertString(aPtr, tempStr);
    }
    return 0;
}

void printVisit(NodoPtr nodo){
    if(nodo!=NULL){
        printf("%s", nodo->stringa);
        if(nodo->next != NULL){
            printf(" ");
        }
        printVisit(nodo->next);
    }
}

void groupsVisit(GroupPtr aPtr){
    if(aPtr!=NULL){
        printVisit(aPtr->stringhe);
        puts("");
        groupsVisit(aPtr->next);
    }
}

int main(){
    int N;
    GroupPtr aPtr = NULL; // lista di anagrammi principali trovati (ogni nodo contiene la lista di stringhe con anagramma principale aPtr->ang)
    if(getValues(&aPtr, &N)) return 1;
    groupsVisit(aPtr);
    return 0;
}