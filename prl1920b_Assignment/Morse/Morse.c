#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>
#define TRAD_DIM 10 // sappiamo che le traduzioni morse di ogni carattere alfanumerico non superano i 10 caratteri

typedef struct rowtranslation{ // struttura che contiene le traduzioni dei caratteri di una riga di testo da tradurre e un puntatore ad una struttura dello stesso tipo (vedi liste)
	char c_translation[TRAD_DIM]; // traduzione morse di un carattere
	struct rowtranslation *nextPtr; // punta al nodo successivo
} RowCharTranslation; // definizione del tipo RowCharTranslation
typedef RowCharTranslation *RowCharTranslationPtr; // e del suo puntatore

typedef struct traduzione{ // ogni carattere e la relativa traduzione sono salvati in questa struttura (la lista generata da questa struttura verrà chiamata traduttore)
    char carattere; // carattere da tradurre
    char translation[TRAD_DIM]; // traduzione in morse di carattere
    struct traduzione *nextPtr; // punta al nodo successivo
} Traduzione; // definizione del tipo Traduzione
typedef Traduzione *TradPtr; // e del suo puntatore

int pushTranslationAtTail(TradPtr *lPtr, const char carattere, const char trad[]);
int pushRowCharTranslationAtTail(RowCharTranslationPtr *rtPtr, const char translation[]);

int getTranslator(FILE * const fp, TradPtr *lPtr);
int getRowCharTranslation(FILE * const fp, const TradPtr lPtr, RowCharTranslationPtr *rtPtr);
void getAndPrintTranslations(FILE * const fp, const TradPtr lPtr);

int main(){
	TradPtr lPtr = NULL; // traduttore
	FILE *fp; // puntatore a FILE
	fp = fopen("input.txt" , "r"); // apro il file (posiziono fp sul primo carattere del file)
	if(fp != NULL) { // se non ci sono errori nell'apertura del file
		if(getTranslator(fp, &lPtr)){ // ottengo la lista di traduzioni, ovvero il nostro traduttore
			// qui ho la lista di traduzioni (traduttore) pronta per essere usata
			getAndPrintTranslations(fp, lPtr); // ottengo e stampo le traduzioni
			/*// libero la memoria allocata per il salvataggio del traduttore (decommentare in caso di necessità)
			TradPtr tempPtr = NULL; 
			while(lPtr!=NULL){
				tempPtr = lPtr->nextPtr;
				free(lPtr);
				lPtr = tempPtr;
			}*/
		}
		fclose(fp); // chiudo il file
	}
	return 0;
}

// funzione per ottenere la lista di traduzioni (traduttore) dalle prime righe del file (prima della riga "****")
// ritorna 0 se sono stati riscontrati errori, 1 altrimenti
int getTranslator(FILE * const fp, TradPtr *lPtr){
	char c = fgetc(fp); //ottengo il carattere del file puntato da fp
	char cs[2]; // serve per effettuare un trick per appendere un char ad una stringa
	char current_c;
	int error = 0;
	char trad[TRAD_DIM] = ""; // stringa temporanea per il salvataggio dei caratteri dell'alfabeto morse che formano la traduzione di un carattere alfanumerico
	while(c!='*' && !error){ // finchè ho delle traduzioni da salvare nel traduttore e non ci sono errori
		if(c!=':'){ // qua c è il carattere di cui si avrà il corrispondente morse
			current_c = c; // lo salvo in current_c
		}else{ // i caratteri successivi a ':' fino al newline formano la traduzione morse del carattere salvato in current_c,
			c = fgetc(fp); // prendo il primo
			while(c!='\n' && !error){ // finchè non arrivo a fine linea e non ci sono errori
				cs[0] = c;
				cs[1] = '\0';
				strcat(trad, cs); // appendo il carattere alla stringa temporanea
				c = fgetc(fp); // continuo a ottenere caratteri
			}
			error = !pushTranslationAtTail(lPtr, current_c, trad); // push del carattere e della relativa traduzione morse nel traduttore
			strcpy(trad,""); // reset della stringa temporanea
		}
		c = fgetc(fp); // continuo a ottenere caratteri
	}
	if(!error){ // se non ci sono stati errori fatali
		while(fgetc(fp)!='\n'); // scorro i rimanenti caratteri fino a new line
	}
	return !error; // ritorno 0 in caso di errore, 1 altrimenti 
}

// funzione che ottiene e stampa la traduzione di ogni riga del file da fp fino in fondo
void getAndPrintTranslations(FILE * const fp, const TradPtr lPtr){
	RowCharTranslationPtr rtPtr = NULL, tempPtr = NULL; // rtPtr è la lista delle traduzioni relative ai caratteri presenti nella riga di testo che stiamo traducendo
	int keepTranslating = 1;
	while(keepTranslating){ // 0 quando avviene un errore fatale o è raggiunta la fine del file
		rtPtr = NULL;
		keepTranslating = getRowCharTranslation(fp, lPtr, &rtPtr); // dopo questa funzione, rtPtr punterà alla lista che forma la traduzione (o NULL)
		if(rtPtr==NULL && keepTranslating){ // se NULL allora c'è stato un errore di traduzione (non fatale)
			printf("Errore nell\'input\n");
		}else if(keepTranslating){ // se punta alla lista che forma la traduzione
			while(rtPtr!=NULL){ // la si scorre stampando ogni traduzione nella lista puntatata da rtPtr
				tempPtr = rtPtr->nextPtr;
				printf("%s", rtPtr->c_translation);
				free(rtPtr); // nel frattempo libero la memoria allocata per l'operazione di traduzione
				rtPtr = tempPtr;
			}
			printf("\n");
		}
	}
}

// richiamata per ogni riga del file puntato da fp, questa funzione effettua la traduzione della riga (fino a newline) e la salva in rtPtr (rtPtr è definito in getAndPrintTranslations)
// ritorna 0 quando si è arrivati alla fine del file o quando si è riscontrato un errore fatale, 1 altrimenti
int getRowCharTranslation(FILE * const fp, const TradPtr lPtr, RowCharTranslationPtr *rtPtr){
	char c = fgetc(fp);
	char precC = ' '; // inizializzato come uno spazio per fare in modo di non aggiungere spazi in fase iniziale di traduzione
	RowCharTranslationPtr tempPtr = NULL; // puntatore temporaneo per liberare la memoria non più utilizzata
	TradPtr currentPtr = NULL; // per scorrere il traduttore
	int tradError = 0, charFound, fatalError = 0;
	while(c!='\n' && !tradError && !feof(fp) && !fatalError){ // finchè non trovo newline e non ci sono errori (di ogni genere) e non sono alla fine del file
		charFound = 0;
		currentPtr = lPtr; // currentPtr diventa il puntatore alla prima lettera del traduttore
		if(isalnum(c)){ // traduco un carattere alfanumerico
			c = tolower(c); // rendo c minuscolo (o il numero stesso in caso sia una cifra)
			while(!charFound && currentPtr!=NULL){ // finchè non ho trovato il carattere necessario e non sono arrivato alla fine del traduttore
				if(currentPtr->carattere == c){ // se ho trovato il carattere da tradurre nel traduttore
					charFound = 1;
					if(isalnum(precC)){ // se il carattere precedente non è uno spazio
						fatalError = !pushRowCharTranslationAtTail(rtPtr, "   "); // inserisco 3 spazi prima della traduzione del carattere corrente
					}
					fatalError = !pushRowCharTranslationAtTail(rtPtr, currentPtr->translation); // push della traduzione in rtPtr
				}
				currentPtr = currentPtr->nextPtr; // scorro alla Traduzione successiva
			}
			if(charFound!=1){ // qua, non può accadere, se accade esco forzatamente
				fatalError = 1;
			}
		}else if(c==' '){ // se c è uno spazio
			fatalError = !pushRowCharTranslationAtTail(rtPtr, "       "); // lo spazio viene tradotto con 7 spazi
		}else{ // se c è un carattere impossibile da tradurre
			tradError = 1; // errore di traduzione
			while(*rtPtr!=NULL){ // libero la memoria allocata per la traduzione corrente
				tempPtr = (*rtPtr)->nextPtr;
				free(*rtPtr);
				*rtPtr = tempPtr;
			}
			*rtPtr = NULL; // annullo il puntatore alla traduzione dopo aver liberato la memoria
			while(fgetc(fp)!='\n'); // scorro i rimanenti caratteri fino a new line
		}
		if(!tradError && !fatalError){ // se non ho trovato errori (di ogni genere) continuo con l'acquisizione del prossimo carattere
			precC = c;
			c = fgetc(fp);
		}
	}
	return !feof(fp) && !fatalError;
}

// inserimento in coda della traduzione translation di un carattere
// ritorna 1 se non ci sono errori durante l'allocazione
int pushRowCharTranslationAtTail(RowCharTranslationPtr *rtPtr, const char translation[]){
	// alloco nuovo nodo
	RowCharTranslationPtr nuovaTrad = malloc(sizeof(RowCharTranslation));
	if(nuovaTrad!=NULL){
		// inizializzo nodo
		strcpy(nuovaTrad->c_translation,translation);
		nuovaTrad->nextPtr = NULL;
		RowCharTranslationPtr precPtr = NULL;
		RowCharTranslationPtr currPtr = *rtPtr;
		while(currPtr != NULL){
			precPtr = currPtr;
			currPtr = currPtr->nextPtr;
		}
		if(precPtr==NULL){
			*rtPtr = nuovaTrad;
		}else{
			precPtr->nextPtr = nuovaTrad;
		}
	}else{
		return 0;
	}
	return 1;
}

// inserisco la traduzione in coda per trovare le lettere prima dei numeri quando scorrerò la lista
// c'è infatti maggior probabilità di dover tradurre lettere piuttosto che numeri)
// ritorna 1 se non ci sono errori durante l'allocazione
int pushTranslationAtTail(TradPtr *lPtr, const char carattere, const char trad[]){
	// alloco nuovo nodo
	TradPtr nuovoPtr = malloc(sizeof(Traduzione));
	if(nuovoPtr!=NULL){ 
		// inizializzo nodo
		nuovoPtr->carattere = carattere;
		strcpy(nuovoPtr->translation,trad);
		nuovoPtr->nextPtr = NULL;
		TradPtr precPtr = NULL;
		TradPtr currPtr = *lPtr;
		while(currPtr != NULL){
			precPtr = currPtr;
			currPtr = currPtr->nextPtr;
		}
		if(precPtr==NULL){
			*lPtr = nuovoPtr;
		}else{
			precPtr->nextPtr = nuovoPtr;
		}
	}else{
		return 0;
	}
	return 1;
}