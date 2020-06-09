// (*) C standard: Paragraph 2.2.1 
//"In both the source and execution basic character sets, 
// the value of each character after 0 in the above list of decimal 
// digits shall be one greater than the value of the previous."

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#define END_STR "fine"
#define C2_BITS 4*8 // il numero di bit per la rappresentazione in C2
#define BUF_SIZE 10
#define INT_MIN -2147483648 // INT_MIN e INT_MAX sono gli interi più piccolo e più grande rappresentabili in questo programma
#define INT_MAX 2147483647 // non useremo limits.h in quanto la rappresentazione in C2 di un intero verrà ottenuta tramite operatore & (più info nella funzione get2C)

typedef struct nodo{ // serve per implementare le pile necessarie nello svolgimento del programma
    int val; // valore intero
    struct nodo *nextPtr; // puntatore al prossimo nodo
} Nodo; // definizione del tipo Nodo
typedef Nodo *NodoPtr; // e del puntatore a Nodo

int getResultFromInput(NodoPtr *lPtr);
int doMath(NodoPtr *lPtr, char op);
void get2C(char *bin_str, int32_t n);
void freeStack(NodoPtr *lPtr);
int push(NodoPtr *lPtr, const int val);
int pop(NodoPtr *lPtr);

int main(void){
	NodoPtr lPtr = NULL; // inizializzo la pila
	char bin_str[C2_BITS+7+1]; // C2_BITS sono i bit, 7 sono gli spazi, 1 è \0. Conterrà la stringa in C2 del risultato finale
	int npiResult; // risultato dell'espressione
	while(getResultFromInput(&lPtr)){ // finchè ci sono input validi
		if(lPtr!=NULL){ // se lPtr non è NULL, print result
			npiResult = pop(&lPtr); // nella pila a questo punto è rimasto il risultato di tutta l'espressione. Lo ottengo con l'ultima pop
			get2C(bin_str, (int32_t)npiResult); // la stringa bin_str diventa la rappresentazione in C2 di npiResult
			printf("%d in C2: %s \n",npiResult, bin_str); // stampo il risultato e la sua rappresentazione in C2
		}else{ // altrimenti, overflow detected
			printf("Overflow!\n");
		}
	}
    return 0;
}

// funzione per ottenere il risultato di una espressione npi da stdin. Il risultato è inserito in lPtr
// ritorna 0 se l'utente vuole terminare il programma o se sono stati riscontrati errori fatali (overflow non è un errore fatale), 0 altrimenti
int getResultFromInput(NodoPtr *lPtr){
	char c = getchar(); // ottengo il primo
	char nextC = getchar(); // e il successivo carattere
	NodoPtr valPtr = NULL, tempPtr = NULL; // valPtr è la pila usata per ottenere il valore di ogni intero passato in input, tempPtr è temporanea per la liberazione della memoria
	long currentLong = 0; // numero (long) ottenuto da input
	int overflow = 0, signFactor = 1, i = 0, mathRes; // flag per l'overflow; segno del numero; contatore delle cifre di un numero; appoggio per controllo dell'overflow
	int eop = 0; // end of process
	while(c!='\n' && !overflow && !eop){ // finchè non sono a fine linea, non c'è overflow e non vale eop
		if(isalnum(c)){ // c è un carattere alfanumerico
			if(isalpha(c)){ // c è una lettera
				if(c == 'f' && nextC == 'i' && getchar() == 'n' && getchar() == 'e'){ // se è stato inserito "fine"
					eop = 1; // esco
				}// non è gestito altro (potrei uscire alla prima lettera trovata in ingresso)
			}else{ // c è una cifra
				eop = !push(&valPtr, c - '0'); // (*)
			}
		}else{ // c non è un carattere alfanumerico
			if(c==' '){ // se c è uno spazio
				if(valPtr!=NULL){ // se la lista valPtr non è nulla (ovvero questo spazio viene dopo l'inserimento di un numero)
					while(valPtr!=NULL){ // scorro la lista e ottengo il valore del numero
						tempPtr = valPtr->nextPtr;
						currentLong += pop(&valPtr) * pow(10,i); // salvo in currentLong il valore del numero inserito
						++i; 
						valPtr = tempPtr;
					}
					currentLong *= signFactor; // moltiplico il fattore del segno per il numero corrente
					if(currentLong<INT_MIN || currentLong>INT_MAX){ // overflow detected se sono oltre INT_MIN o oltre INT_MAX
						freeStack(lPtr); // libero la pila lPtr
						overflow = 1;
						if(nextC!='\n') // se non sono già arrivato a fine riga
							while((c = getchar())!='\n'); // scorro l'input fino alla riga successiva
					}else{
						push(lPtr, (int)currentLong); // inserisco il numero nella pila che contiene tutti i numeri inseriti dall'utente
					}
					i = 0; // azzero il contatore di cifre
					currentLong = 0; // azzero il numero correntemente letto
					signFactor = 1; // resetto il fattore segno
				}
			}else{ // c è un operatore
				if(c=='-'){ // '-' potrebbe essere il segno del numero o l'operatore di differenza
					if(isdigit(nextC)){ // c='-' è il segno del numero
						signFactor = -1; // porto il fattore segno a negativo
					}
				}
				if(signFactor!=-1){ // se non ho cambiato il fattore segno (ovvero, se c rappresenta un operatore tra +,- e *)
					mathRes = doMath(lPtr, c); // faccio i calcoli 
					if(mathRes == 0){ // overflow
						freeStack(lPtr); // libero la pila lPtr
						overflow = 1;
						if(nextC!='\n') // se non sono già arrivato a fine riga
							while((c = getchar())!='\n'); // scorro l'input fino alla riga successiva
					}else if(mathRes < 0){ // errore fatale
						eop = 1; // esco
					}
				}
			}
		}
		c = nextC; // scorro di un carattere l'input
		if(c!='\n' && !overflow && !eop){ // se posso continuare
			nextC = getchar(); // ottengo il carattere successivo
		}
	}
	return !eop; 
}

// funzione per effettuare l'operazione op sugli ultimi due numeri nella pila lPtr
// ritorna -1 se incontra un errore fatale, 0 se incontra overflow, 1 altrimenti
int doMath(NodoPtr *lPtr, char op){
	int currentNum;
	int a, b; // salvo i numeri nello stack in a e b
	if(*lPtr != NULL){
		a = pop(lPtr); // last num in stack
	}else{
		return -1; // errore fatale
	}
	if(*lPtr != NULL){
		b = pop(lPtr); // 2nd last num in stack
	}else{
		return -1; // errore fatale
	}
	switch(op){
		case '*':
			currentNum = a * b; // prodotto tra ultimi 2 elementi della pila
			if(a != 0 && currentNum/a != b){ //overflow detected
				return 0;
			}
			return push(lPtr, currentNum); // aggiungo il risultato alla pila;
		case '+':
			currentNum = a + b; // somma tra ultimi 2 elementi della pila
			if((b>0 && a>0 && currentNum<0) || (b<0 && a<0 && currentNum>0)){ 
				return 0;
			}
			return push(lPtr, currentNum); // aggiungo il risultato alla pila
		case '-':
			currentNum = b - a; // differenza tra ultimi 2 elementi della pila
			if((b>=0 && a<0 && currentNum<0) || (b<=0 && a>0 && currentNum>0)){ //overflow detected
				return 0;
			}
			return push(lPtr, currentNum); // aggiungo il risultato alla pila
	}
	return -1;
}

// inserisce in bin_str la rappresentazione C2 del numero n
void get2C(char *bin_str, int32_t n){
	if(n<0){ // non è garantito che l'int sia rappresentato in 2C
		n = -n;
		// a seconda dell'architettura, un intero positivo potrà essere rappresentato "normalmente" o in 2C
		// se in 2c: il MSB rappresenta il segno -> 0101 == 5 € [-(2^3) ; (2^3 -1)]
		// se non in 2c: il MSB fa parte del numero -> 0101 == 5 € [0 ; (2^4 -1)]
		// in questo programma abbiamo n € [-(2^31) ; (2^31 -1)], 
		// quindi il MSB di n (con n > 0) è sempre zero perchè n è di tipo int32_t (32 bit)
		n = ~(n)+1; // è la rappresentazione in 2C di n (con n positivo)
	}
	// a questo punto, n è rappresentato in C2
	int spaces = 0; // tengo il conto degli spazi già inseriti
	for(unsigned int i=0; i<C2_BITS; i++){
		if(i%4==0 && i!=0){ // inserisco 1 spazio ogni 4 bit (7 volte)
			bin_str[i+spaces] = ' ';
			++spaces;
		}
		unsigned int mask = 1u << (C2_BITS - 1 - i); // questa maschera ha un solo 1 all' indice: (C2_BITS-1-i)
		// compongo la stringa con i bit della rappresentazione 2c di n
		bin_str[i+spaces] = (n & mask) ? '1' : '0'; // and bit a bit con la maschera
	}
	bin_str[C2_BITS+7] = '\0';	// terminatore
}

// libera la pila lPtr passata
void freeStack(NodoPtr *lPtr){
	NodoPtr tempPtr = NULL;
	while(*lPtr!=NULL){
		tempPtr = (*lPtr)->nextPtr;
		free(*lPtr);
		*lPtr = tempPtr;
	}
}

// inserisce in testa a lPtr un nodo con valore val
int push(NodoPtr *lPtr, const int val){
	// alloco nuovo nodo
	NodoPtr nuovoPtr = malloc(sizeof(Nodo));
	if(nuovoPtr!=NULL){
		// inizializza nodo
		nuovoPtr->val = val;
		nuovoPtr->nextPtr = *lPtr;
		*lPtr = nuovoPtr;
	}else{
		return 0;
	}
	return 1;
}

// rimuove dalla testa di lPtr un nodo e ne ritorna il valore intero contenuto in esso
int pop(NodoPtr *lPtr){
	int val = (*lPtr)->val;
	NodoPtr tempPtr;
	tempPtr = *lPtr;
	*lPtr = (*lPtr)->nextPtr;
	free(tempPtr);
	return val;
}