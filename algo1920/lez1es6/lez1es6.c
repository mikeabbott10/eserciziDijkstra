/*
	Swap
	scambia il contenuto di due variabili
*/

#include<stdio.h>

void swap(int *a, int *b);

int main(){
	int a, b;
	scanf("%d", &a);
	scanf("%d", &b);
	swap(&a, &b);
	printf("%d\n%d\n", a, b);
	return 0;
}

void swap(int *a, int *b){
	int temp_val = *a; // dereference di a
	*a = *b; // il valore a cui punta a diventa il valore a cui punta b
	*b = temp_val; // il valore a cui punta b è diventa il valore a cui puntava a, ovvero temp_val
}
