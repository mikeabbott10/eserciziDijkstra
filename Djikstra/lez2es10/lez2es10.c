#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *product(char *str, int k);

int main(){
    char str[1000];
    scanf("%s", str);
    int k;
    scanf("%d", &k);
    printf("%s\n", product(str,k));
    return 0;
}

char *product(char *str, int k){
    int src_len = strlen(str);
    int new_len = k * src_len;
    char *s = malloc((new_len + 1) * sizeof(char));
    if(s==NULL)
        exit(1);
    int i;
    for(i=0;i<new_len;i++){
        s[i] = str[i%src_len];
    }
    s[new_len] = '\0';
    return s;
}