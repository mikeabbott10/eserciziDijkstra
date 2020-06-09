/*
	MinMax
	scandisce l’array e salva in min_index la posizione in cui si trova 
	l’elemento minimo e in max_index la posizione in cui si trova l’elemento massimo
*/

#include<stdio.h>
#include<limits.h>
#define N 10


void minmax(int *A, int n, int *min, int *max);

int main(){
	int min_index, max_index;
	int A[N];
	int i;
	for(i = 0; i<N; ++i){
		scanf("%d", A+i);
	}
	minmax(A, N, &min_index, &max_index);
	printf("%d\n%d\n%d\n%d\n", min_index, A[min_index], max_index, A[max_index]);
	return 0;
}

void minmax(int *A, int n, int *min_index, int *max_index){
	int i;
	int max_val = INT_MIN;
	int min_val = INT_MAX;
	for(i = 0; i<n; ++i){
		if(max_val < A[i]){
			*max_index = i;
			max_val = A[i];
		}else if(min_val > A[i]){
			*min_index = i;
			min_val = A[i];
		}
	}
}
