/*
	Primo
	legge da tastiera un intero e stabilisce se è primo
*/

#include<stdio.h>
#include<math.h>

int is_primo(int x);

int main(){
	int x;
	scanf("%d",&x);
	printf("%d\n", is_primo(x));
	return 0;
}

int is_primo(int x){
	int limite = (int) sqrt(x); // oltre a questo valore limite, i numeri saranno sicuramente coprimi con x
	int fattore = 3, primo = 1;
	if(x!= 2 && x % 2 == 0) // se è pari e diverso da 2 ho finito
		return 0;
	// check del resto della divisione con tutti i valori dispari minori uguali a limite 
	// (non ha senso considerare i valori pari)
	while(primo && fattore <= limite){
		if(x % fattore == 0) // qui se ho trovato un divisore di x => x non è primo
			primo = 0;
		fattore += 2;
	}
	return primo;
}