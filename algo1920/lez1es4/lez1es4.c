/*
	Invertire array
	inverte un array di dimensione N, passato da tastiera
*/

#include<stdio.h>
#include<stdlib.h>

int main(){
	// inizializzo array
	int N, i;
	scanf("%d", &N);
	int *A = malloc(N * sizeof(int));
	if(A==NULL)
		return 0;
	for(i=0; i<N; ++i){
		scanf("%d", A+i);
	}
	
	// inverto array
	int temp;
	for(i=0; i< N/2; ++i){
		temp = A[i];
		A[i] = A[N-1-i];
		A[N-1-i] = temp;
	}
	
	// printo array
	for(i=0; i<N; ++i){
		printf("%d\n", *(A+i));
	}
	return 0;
}
