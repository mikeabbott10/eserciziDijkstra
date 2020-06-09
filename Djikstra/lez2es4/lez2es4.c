#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int anagramma(unsigned char *s1, unsigned char *s2);

int main(){
    unsigned char *s1 = malloc(100*sizeof(char));
    unsigned char *s2 = malloc(100*sizeof(char));
    if(s1==NULL || s2==NULL)
        return 0;
    scanf("%s", s1);
    scanf("%s", s2);
    printf("%d\n", anagramma(s1,s2));
    return 0;
}

int anagramma(unsigned char *s1, unsigned char *s2){
    int len = strlen(s1);
    if(len != strlen(s2))
        return 0;
    char aS[256], aZ[256];
    int i;
    for(i=0; i<256; i++){
        aS[i] = aZ[i] = 0;
    }
    for(i = 0; i < len; i++){
        aS[s1[i]]++;
        aZ[s2[i]]++;
    }
    for(i=0; i<256; i++){
        if(aS[i] != aZ[i])
            return 0;
    }
    return 1;
}