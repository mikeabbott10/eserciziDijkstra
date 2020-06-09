/*
	FindVal
	cerca valore val all'interno di un array passato da tastiera
*/

#include<stdio.h>

int *findVal(int a[], int len, int val);

int main(){
	int a[10], i=0;
	int val;
	for(i=0;i<10;i++){
		scanf("%d", a+i);
	}
	scanf("%d", &val);
	if(findVal(a, 10, val) != NULL)
		printf("trovato\n");
	else
		printf("non trovato\n");
	return 0;
}

int *findVal(int a[], int len, int val){
	int i = 0;
	while(i<len && a[i] != val){
		i++;
	}
	if(i<len)
		return a+i;
	else return NULL;
}
