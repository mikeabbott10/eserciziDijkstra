/*
	Somma dispari
	somma i primi n numeri dispari
*/

#include<stdio.h>

int f(int n);

int main(){
	int n;
	scanf("%d", &n);
	printf("%d\n", f(n));
	return 0;
}

// somma dei primi n numeri dispari
int f(int n){
	if(n<=0)
		return 0;
	return 2*n-1 + f(n-1); // 2*n-1 è l'n-esimo numero dispari
}
