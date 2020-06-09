#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *my_strcat(char *s1, char *s2);

int main(){
    char s1[2000], s2[1000];
    scanf("%s", s1);
    scanf("%s", s2);
    printf("%s\n", my_strcat(s1,s2));
    return 0;
}

char *my_strcat(char *s1, char *s2){
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);
    int i;
    for(i=0;i<s2_len;i++){
        s1[s1_len+i] = s2[i];
    }
    s1[s1_len+i] = '\0';
    return s1;
}