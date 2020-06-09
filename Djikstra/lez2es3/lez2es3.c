#include<stdio.h>

int my_strlen(char *s);

int main(){
	char s[1000];
	scanf("%s", s);
	printf("%d\n", my_strlen(s));
	return 0;
}

int my_strlen(char *s){
	int len = 0;
	while(s[len] != '\0'){
		len ++;
	}
	return len;
}
