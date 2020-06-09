#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *my_strcpy(char *dest, char *src);

int main(){
    char s[1000];
    scanf("%s",s);
    char *str = malloc((strlen(s)+1) * sizeof(char));
    if(str==NULL)
        return 0;
    str = my_strcpy(str, s);
    printf("%s\n", str);
    return 0;
}

char *my_strcpy(char *dest, char *src){
    int i;
    for(i=0; i<strlen(src); i++){
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}