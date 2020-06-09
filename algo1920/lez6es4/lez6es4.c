#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 100

typedef struct{
    char str[MAX_LEN];
    int len;
} String;

int getArray(String **A, int *len){
    scanf("%d", len);
    if(*len<=0) return 1;

    *A = (String *) malloc(*len * sizeof(String));
    if(A==NULL) return 1;

    int i;
    for(i = 0; i < *len; ++i){
        scanf("%s", (*A)[i].str);
        (*A)[i].len = strlen((*A)[i].str);
    }
    
    return 0;
}

int confronta(const void *a, const void *b){
    //return <= 0 se a prima di b
    String A = *(String *) a;
    String B = *(String *) b;
    if(A.len == B.len){
        return strcmp(A.str, B.str);
    }else
        return A.len - B.len;
        
    
    
}

int main(){
    String *A; // array A di String
    int n, i;
    if(getArray(&A, &n)) return 1;
    qsort(A, n, sizeof(String), confronta);
    for(i = 0; i < n; ++i){
        printf("%s\n", A[i].str);
    }
    return 0;
}