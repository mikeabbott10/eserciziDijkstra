#include<stdio.h>
#include<string.h>

int my_strcmp(char* s1, char* s2);

int main(){
    char s1[1000], s2[1000];
    scanf("%s",s1);
    scanf("%s",s2);
    int cmp = my_strcmp(s1,s2);
    printf("%s%d\n", cmp==1?"+":"", cmp);
    return 0;
}

int my_strcmp(char* s1, char* s2){
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);
    int i = 0;
    int min_len = (s1_len>s2_len)? s2_len : s1_len;
    while(i< min_len){
        if(s1[i]<s2[i])
            return -1;
        else if(s1[i]>s2[i])
            return 1;
        else
            i++;
    }
    if(s2_len==s1_len)
        return 0;
    else if(s2_len > s1_len)
        return -1;
    else
        return 1;
}