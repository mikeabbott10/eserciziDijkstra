#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STR_LEN 100

int bin_research(char str[], char **A, int r, int p);

int main(){
    int A_len;
    scanf("%d", &A_len);
    int i;
    char **A = malloc(A_len * sizeof(char *));
    for(i=0;i<A_len;++i){
        A[i] = malloc(STR_LEN * sizeof(char));
        scanf("%s", A[i]);
    }
    int choice;
    char str[STR_LEN];
    while(scanf("%d", &choice) && choice){
        scanf("%s", str);
        printf("%d\n", bin_research(str, A, 0, A_len - 1));
    }
    return 0;
}

int bin_research(char str[], char **A, int r, int p){
    if(r > p){
        return -1;
    }
    int q = (r+p)/2;
    if(strcmp(str, A[q]) == 0)
        return q;
    if(strcmp(str, A[q]) < 0){
        bin_research(str, A, r, q-1);
    }else{
        bin_research(str, A, q+1, p);
    }
}