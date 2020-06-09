/*
	Triplo swap
	scambia il contenuto di 3 variabili
	x=z - y=x - z=y
*/

#include<stdio.h>

void tswap(int *x, int *y, int *z);

int main(){
	int x, y, z;
	scanf("%d %d %d", &x, &y, &z);
	tswap(&x, &y, &z);
	printf("%d\n%d\n%d\n", x, y, z);
	return 0;
}

void tswap(int *x, int *y, int *z){
	int temp_x = *x;
	int temp_y = *y;
	*x = *z;
	*y = temp_x;
	*z = temp_y;	
}
