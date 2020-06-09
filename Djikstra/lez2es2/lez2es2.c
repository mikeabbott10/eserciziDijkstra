/*
	Contatore
	data una sequenza di interi tiene traccia delle frequenze 
	degli  interi  compresi  tra  0  e  9  (estremi  inclusi)
*/

#include<stdio.h>
#define LEN 10

void reset(int a[], int len);
void add(int a[], int len, int val);

int main(){
	int a[LEN];
	reset(a, LEN);
	int val;
	while(scanf("%d", &val) && val != -1){
		add(a, LEN, val);
	}
	int i = 0;
	for(i=0; i<LEN; i++){
		printf("%d\n", a[i]);
	}
	return 0;
}

void reset(int a[], int len){
	int i=0;
	for(i=0; i<LEN; i++){
		a[i] = 0;
	}
}

void add(int a[], int len, int val){
	if(val>=0 && val<=len-1){
		a[val]++;
	}
}
