#include<stdio.h>
#include<ctype.h>
//definizione stati (come interi, saranno poi gli indici dell'array di puntatori a funzione)
#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define S7 7
#define S8 8
#define S9 9
#define S10 10
#define SE 11
#define N_STATI 11

// ogni funzione t_sn è la funzione di transizione da sn ad uno stato successivo sx con c in input
int t_s0(char c);
int t_s1(char c);
int t_s2(char c);
int t_s3(char c);
int t_s4(char c);
int t_s5(char c);
int t_s6(char c);
int t_s7(char c);
int t_s8(char c);
int t_s9(char c);
int t_s10(char c);
int isFinal(int s);

int main(){
	int s = S0; // stato iniziale
	int (*move[N_STATI])(char) = {t_s0, t_s1, t_s2, t_s3, t_s4, t_s5, t_s6, t_s7, t_s8, t_s9, t_s10}; // array di puntatori a funzione
	char c = getchar(); // primo carattere
	while(s!=SE && c!='\n'){ // se s==SE allora sono in uno stato di errore, quindi esco
		s = (*move[s])(c); // s sarà lo stato in cui ci si sposta se da s si riceve c in input
		c = getchar(); // prossimo carattere
	}
	printf("stringa%sappartenente al linguaggio\n", isFinal(s)?" ":" non ");
	return 0;
}

int t_s0(char c){ // t([A-Z]) -> S0; t(0) -> S1
	if(c>='A' && c<='Z'){
		return S0;
	}else if(c=='0'){
		return S1;
	}else{
		return SE;
	}
}

int t_s1(char c){ // t(0|[2-9]) -> S5; t(1) -> S2
	if(!isdigit(c)){
		return SE; 
	}else if(c=='1'){
		return S2;
	}else{
		return S5;
	}
}

int t_s2(char c){ // t(0|[2-9]) -> S6; t(1) -> S3
	if(!isdigit(c)){
		return SE; 
	}else if(c=='1'){
		return S3;
	}else{
		return S6;
	}
}

int t_s3(char c){ // t(0|[2-9]) -> S7; t(1) -> S4
	if(!isdigit(c)){
		return SE; 
	}else if(c=='1'){
		return S4;
	}else{
		return S7;
	}
}

int t_s4(char c){ // t(0|[2-9]) -> S7; t(1) -> S4
	if(!isdigit(c)){
		return SE; 
	}else if(c=='1'){
		return S4;
	}else{
		return S7;
	}
}

int t_s5(char c){ // t([0-9]) -> S8
	if(!isdigit(c)){
		return SE;
	}else{
		return S8;
	}
}

int t_s6(char c){ // t([0-9]) -> S9
	if(!isdigit(c)){
		return SE;
	}else{
		return S9;
	}
}

int t_s7(char c){  // t([0-9]) -> S9
	if(!isdigit(c)){
		return SE; 
	}else{
		return S9;
	}
}

int t_s8(char c){  // t([0-9]) -> S10
	if(!isdigit(c)){
		return SE; 
	}else{
		return S10;
	}
}

int t_s9(char c){  // t([0-9]) -> S10
	return t_s8(c);
}

int t_s10(char c){
	return SE;
}

// ritorna vero se s è uno stato finale, falso altrimenti
int isFinal(int s){
	return s==S4 || s==S7 || s==S9 || s==S10;
}