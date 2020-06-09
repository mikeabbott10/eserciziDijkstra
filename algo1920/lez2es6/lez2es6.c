#include<stdio.h>
#include<stdlib.h>

char *my_strcat1(int s1_len, char *s1, int s2_len, char *s2);

int main(){
    int s1_len;
    scanf("%d", &s1_len);
    char *s1 = malloc(sizeof(char)*(s1_len+1));
    if(s1==NULL) return 0;
    scanf("%s", s1);

    int s2_len;
    scanf("%d", &s2_len);
    char *s2 = malloc(sizeof(char)*(s2_len+1));
    if(s2==NULL) return 0;
    scanf("%s", s2);

    printf("%s\n", my_strcat1(s1_len, s1, s2_len, s2));
    return 0;
}

char *my_strcat1(int s1_len, char *s1, int s2_len, char *s2){
    char *s = malloc((s1_len + s2_len + 1) * sizeof(char));
    if(s==NULL)
        exit(1);
    int i;
    for(i=0;i<s1_len;i++){
        s[i] = s1[i];
    }
    for(i=0;i<s2_len;i++){
        s[s1_len+i] = s2[i];
    }
    s[s1_len+i] = '\0';
    return s;
}