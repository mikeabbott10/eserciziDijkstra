#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_AUTHOR_NAME_CHARS 70 // caratteri massimi del nome dell'autore
#define MAX_BOOK_TITLE_CHARS 150 // caratteri massimi del titolo del libro
#define MAX_ISBN_DIGITS 6 // numero massimo di cifre del codice isbn

typedef struct book{ // struttura Book, rappresenta un libro e ne contiene le proprietà
	int isbn;
	char title[MAX_BOOK_TITLE_CHARS];
	int n_tot; // numero totale di copie
	int n_disponibili; // numero disponibili di copie
	struct book *next; // prossimo libro
} Book; // definizione del tipo Book
typedef Book *BookPtr; // e del puntatore ad esso

typedef struct author{ // author contiene il nome di un autore e una lista di libri da lui scritti
	char name[MAX_AUTHOR_NAME_CHARS];
	BookPtr bookPtr; // lista di libri dell'autore
	struct author *sxPtr; // puntatore sx
	struct author *dxPtr; // puntatore dx (aggiungendo autori si crea un albero binario, per facilitare la ricerca)
} Author; // definizione del tipo Author
typedef Author *AuthorPtr; // e del puntatore ad esso

int get_choice();
int get_int();
void getCatalogue(AuthorPtr *aPtr);
void insertBook(AuthorPtr *aPtr, char authName[], char bookTitle[], int isbn);
void insertBookInAuthor(BookPtr *bPtr, char title[], int isbn);

void stampaCatalogo(AuthorPtr aPtr);
void cerca(AuthorPtr aPtr);
void searchBookFromTitle(AuthorPtr aPtr, char authName[], char bookTitle[]);
void prestito(AuthorPtr aPtr);
void restituzione(AuthorPtr aPtr);
void searchBookFromIsbn(AuthorPtr aPtr, int isbn, BookPtr *bkPtr);

int main(){
	AuthorPtr aPtr = NULL; // lista di autori (inizialmente NULL)
	void (*f[4])(AuthorPtr) = {stampaCatalogo, cerca, prestito, restituzione}; // array di puntatori a funzione per le scelte del menù
	int eop = 0; // end of program
	int choice; // la scelta dell'utente
	getCatalogue(&aPtr); // ottengo il catalogo
	while(!eop){ // finchè il programma non è terminato
		printf("Scegli un opzione:\n1) Stampa catalogo.\n2) Cerca.\n3) Prestito.\n4) Restituzione.\n5) Esci.\nScelta:  ");
		choice = get_choice(); // ottengo la scelta dell'utente
		if(choice>=1 && choice<=4){
			(*f[choice-1])(aPtr); // richiamo la funzione corrispondente alla scelta tramite l'array
		}else{ // choice qua è 5
			printf("Bye\n");
			eop = 1; // termina programma
		}
	}
	return 0;
}

// funzione che ritorna un intero tra 1 e 5 corrispondente alla scelta dell'utente
int get_choice(){
	int n;
	int firstTime = 1; // per non stampare l'errore la prima volta che si entra 
	do{
		if(!firstTime){
			printf("Errore. Scelta non valida.\n");
		}else{ // la prima volta non vogliamo stampare il messaggio di errore
			firstTime = 0;
		}
		n = get_int(); // ottengo il numero da stdin
	}while(n<1 || n>5);
	return n;
}

// ritorna 0 se non si è inserito un intero, altrimenti l'intero
int get_int(){
	int n;
	if(scanf("%d",&n)!=1){
		n = 0;
	}
	while(getchar()!='\n'); // clean del buffer (scanf non consuma '\n')
	return n;
}

// funzione per il popolamento del catalogo di autori (riempiamo la lista di strutture autore mediante le info sui nuovi libri passati da stdin)
void getCatalogue(AuthorPtr * aPtr){
	int eoc = 0; // end of catalogue
	char temp[MAX_ISBN_DIGITS+MAX_AUTHOR_NAME_CHARS+MAX_BOOK_TITLE_CHARS + 3] = ""; // per ottenere ogni riga da stdin
	char tempIsbn[MAX_ISBN_DIGITS+1], author[MAX_AUTHOR_NAME_CHARS+1], book_title[MAX_BOOK_TITLE_CHARS+1]; // stringhe ricavate tramite strtok
	int isbn; // valore intero di isbn
	char *ptr; // ci permette di usare strtol e di controllare eventuali errori
	while(!eoc){ // finchè il catalogo non è terminato
		fgets(temp, sizeof(temp), stdin); // ottengo la riga fino a '\n' compreso
		temp[strlen(temp)-1] = '\0'; // scarto '\n'
		strcpy(tempIsbn, strtok(temp, ",")); 
		if(strcmp(tempIsbn,"0") != 0){ // se non ho trovato UNO 0 come isbn
			isbn = (int) strtol(tempIsbn, &ptr, 10); // isbn da stringa a long, poi castato ad int
			if(*ptr == '\0'){ // errore durante la conversione
				strcpy(book_title, strtok(NULL,",")); // estraggo il titolo del libro
				strcpy(author, strtok(NULL,",")); // estraggo il nome dell'autore
				insertBook(aPtr, author, book_title, isbn); // inserisci il libro nel catalogo
			}
		}else{
			eoc = 1; // catalogo terminato
		}
	}
}

// funzione ricorsiva per l'inserimento di un libro nel catalogo (albero binario). Se l'autore del libro non esiste viene aggiunto.
// Il libro dal titolo bookTitle e isbn isbn viene aggiunto alla lista di libri scritti dall'autore authName
void insertBook(AuthorPtr *aPtr, char authName[], char bookTitle[], int isbn){
	if(*aPtr == NULL){ // ho scorso tutta la lista senza trovare l'autore desiderato
		*aPtr = malloc(sizeof(Author)); // alloco memoria per il nuovo autore, che viene aggiunto al catalogo come foglia dell'albero
		if(*aPtr != NULL){ // se non ci sono errori
			strcpy((*aPtr)->name, authName); // salvo nome autore nella nuova struttura
			(*aPtr)->bookPtr = NULL; // la lista di libri del nuovo autore è inizialmente vuota
			insertBookInAuthor(&((*aPtr)->bookPtr), bookTitle, isbn); // inserisco il primo libro dell'autore nella lista
			(*aPtr)->sxPtr = NULL; // autore aggiunto come foglia dell'albero
			(*aPtr)->dxPtr = NULL; // non ha quindi nodi figli nè a dx nè a sx
		}else{ // errore in mallocazione
			puts("Memoria esaurita\n");
		}
	}else{ // ci sono ancora nodi da percorrere nell'albero, continuo a cercare l'autore
		if(strcmp(authName, (*aPtr)->name) < 0){ // se il nome dell'autore relativo al nodo corrente è minore lessicogrficamente di quello cercato
			insertBook(&((*aPtr)->sxPtr), authName, bookTitle, isbn); // cerco nei sottonodi di sx
		}else if(strcmp(authName, (*aPtr)->name) > 0){ // se il nome dell'autore relativo al nodo corrente è maggiore lessicogrficamente di quello cercato
			insertBook(&((*aPtr)->dxPtr), authName, bookTitle, isbn); // cerco nei sottonodi di dx
		}else{ // stesso autore
			// cerca libro scorrendo la lista di libri da (*aPtr)->book in poi, 
			// se non c'è inseriscilo, se c'è aumenta le copie disponibili e le copie totali
			BookPtr currBook = (*aPtr)->bookPtr; // lista di libri dell'autore
			int found = 0; // flag per ricerca del libro desiderato
			while(currBook!=NULL && !found){ // finchè non ho scorso tutta la lista e non ho trovato il libro desiderato
				if(isbn == currBook->isbn){ // qua ho trovato il libro desiderato nella lista 
					found = 1; // aggiorno il flag
					currBook->n_tot++; // aggiungo uno alle copie totali
					currBook->n_disponibili++; // e a quelle disponibili
				}else{ // non ho trovato il libro
					currBook = currBook->next; // scorro la lista
				}
			}
			if(currBook==NULL){ // libro non ancora inserito
				insertBookInAuthor(&((*aPtr)->bookPtr), bookTitle, isbn); // inserisco il libro nella lista di libri dell'autore
			}
		}
	}
}

// funzione che inserisce un libro di titolo title e isbn isbn nella lista bPtr
void insertBookInAuthor(BookPtr *bPtr, char title[], int isbn){
	BookPtr nuovoPtr = malloc(sizeof(Book)); // alloco memoria per il nuovo libro
	if(nuovoPtr!=NULL){ // se non ci sono errori
		strcpy(nuovoPtr->title, title); // salvo il nome del libro nella nuova struttura
		nuovoPtr->isbn = isbn; // salvo l'isbn
		nuovoPtr->n_tot = 1; // il numero di copie totali è inizialmente 1
		nuovoPtr->n_disponibili = 1; // il numero di copie disponibili è inizialmente 1
		BookPtr precPtr = NULL; // necessario per inserimento ordinato in bPtr
		BookPtr currPtr = *bPtr; // il nodo corrente è quello iniziale
		while(currPtr!=NULL && strcmp(currPtr->title, title) < 0){ // finchè il titolo corrente è minore del titolo del libro da inserire
			precPtr = currPtr;
			currPtr = currPtr->next; // scorro
		}
		if(precPtr!=NULL){ // se non sono nella prima posizione della lista (mi sono mosso verso dx nella lista di libri)
			nuovoPtr->next = currPtr;
			precPtr->next = nuovoPtr; // aggiorno i puntatori
		}else{ // se sono nella prima posizione della lista
			nuovoPtr->next = *bPtr;
			*bPtr = nuovoPtr; // aggiorno i puntatori
		}
	}else{ // ci sono errori di memoria
		puts("Memoria esaurita.\n");
	}
}

// funzione chiamata dalla prima scelta del menu, stampo il catalogo da aPtr
void stampaCatalogo(AuthorPtr aPtr) { // l'albero viene visitato in_order (nome autori in ordine lessicografico)
	BookPtr bPtr = NULL;
	if (aPtr != NULL) {
		stampaCatalogo(aPtr->sxPtr); // visito sotto albero sx
		bPtr = aPtr->bookPtr; // la lista di libri dell'autore
		while(bPtr!=NULL){
			printf("%d - %s - %s (%d/%d)\n",
				bPtr->isbn, aPtr->name, bPtr->title, bPtr->n_disponibili, bPtr->n_tot); // stampo i dati del libro corrente
			bPtr = bPtr->next; // scorro al prossimo libro
		}
		stampaCatalogo(aPtr->dxPtr); // visito sotto albero dx
	}
}

// funzione chiamata dalla seconda scelta del menù (cerco per autore e titolo)
void cerca(AuthorPtr aPtr){
	char author[MAX_AUTHOR_NAME_CHARS+2], title[MAX_BOOK_TITLE_CHARS+2]; // salvo qua i dati scritti dall'utente 
	printf("Inserire nome autore: ");
	fgets(author, sizeof(author), stdin); // ottengo autore da stdin 
	author[strlen(author)-1] = '\0'; // scarto newline
	printf("Inserire titolo: ");
	fgets(title, sizeof(title), stdin); // ottengo titolo libro da stdin 
	title[strlen(title)-1] = '\0'; // scarto newline
	searchBookFromTitle(aPtr, author, title); // chiamo la funzione ricorsiva per la ricerca del libro nel catalogo
}

// cerca il libro dal titolo bookTitle, con autore authName, nel catalogo
void searchBookFromTitle(AuthorPtr aPtr, char authName[], char bookTitle[]){
	if(aPtr == NULL){ // non ho trovato il libro desiderato
		printf("Libro non trovato.\n");
	}else{ // continuo a cercare il libro desiderato
		if(strcmp(authName, (aPtr)->name) < 0){ // se il nome dell'autore relativo al nodo corrente è minore lessicogrficamente di quello cercato
			searchBookFromTitle(aPtr->sxPtr, authName, bookTitle); // cerco nei sottonodi di sx
		}else if(strcmp(authName, aPtr->name) > 0){// se il nome dell'autore relativo al nodo corrente è maggiore lessicogrficamente di quello cercato
			searchBookFromTitle(aPtr->dxPtr, authName, bookTitle); // cerco nei sottonodi di dx
		}else{ // autore trovato
			BookPtr currBook = aPtr->bookPtr; // cerca libro scorrendo la lista di libri da aPtr->book in poi
			int found = 0; // flag per la ricerca del libro desiderato 
			while(currBook!=NULL && !found){ // finchè non ho scorso tutta la lista e non ho trovato il libro desiderato
				if(strcmp(currBook->title, bookTitle) == 0){ // se il titolo è quello ricercato
					found = 1; // aggiorno il flag
					if(currBook->n_disponibili > 0){ // ci sono copie disponibili
						printf("%d copie disponibili.\n", currBook->n_disponibili);
					}else{ // non ci sono copie disponibili
						printf("Non ci sono copie disponibili del libro richiesto.\n");
					}
				}else{
					currBook = currBook->next; // scorro al prossimo libro
				}
			}
			if(currBook==NULL){ // libro non esistente
				printf("Libro non trovato.\n");
			}
		}
	}
}

// funzione per la gestione del prestito di un libro
void prestito(AuthorPtr aPtr){
	printf("ISBN: ");
	int isbn = get_int(); // ottengo isbn del libro
	BookPtr bkPtr = NULL; // salverò qua il puntatore al libro cercato, se esistente
	if(isbn >= 0){ // se isbn valido
		searchBookFromIsbn(aPtr, isbn, &bkPtr); // cerco il libro tramite isbn
		if(bkPtr!=NULL){ // se libro esistente
			if(bkPtr->n_disponibili > 0){ // risultano copie disponibili
				bkPtr->n_disponibili--; // prestito di una copia
				printf("Operazione completata.\n");
			}else{
				printf("Non ci sono copie disponibili del libro richiesto.\n");
			}
		}else{
			printf("Libro non trovato.\n");
		}
	}else{
		printf("Libro non trovato.\n");
	}
}
// funzione per la gestione della restituzione di un libro
void restituzione(AuthorPtr aPtr){
	printf("ISBN: ");
	int isbn = get_int(); // ottengo isbn del libro
	BookPtr bkPtr = NULL; // salverò qua il puntatore al libro cercato, se esistente
	if(isbn >= 0){ // se isbn valido
		searchBookFromIsbn(aPtr, isbn, &bkPtr); // cerco il libro tramite isbn
		if(bkPtr!=NULL){ // se libro esistente
			if(bkPtr->n_disponibili < bkPtr->n_tot){ // risultano copie in prestito
				bkPtr->n_disponibili++; // restituzione di una copia
				printf("Operazione completata.\n");
			}else{
				printf("Non risultano copie in prestito.\n");
			}
		}else{
			printf("Libro non trovato.\n");
		}
	}else{
		printf("Libro non trovato.\n");
	}
}

// 
void searchBookFromIsbn(AuthorPtr aPtr, int isbn, BookPtr *bkPtr){ // l'albero viene visitato pre_order
	BookPtr bPtr = NULL;
	int found = 0;
	if (aPtr != NULL) { // se aPtr punta a una struttura Author
		bPtr = aPtr->bookPtr;
		while(bPtr!=NULL && !found){ // finchè non ho scorso tutta la lista e non ho trovato il libro desiderato
			if(isbn == bPtr->isbn){ // se il libro ha l'isbn cercato
				found = 1; // aggiorno il flag
				*bkPtr = bPtr; // salvo l'indirizzo del libro desiderato in bkPtr
			}else{
				bPtr = bPtr->next; // scorro i libri
			}			
		}
		if(!found){ // se non l'ho ancora trovato
			searchBookFromIsbn(aPtr->sxPtr, isbn, bkPtr);
			if(!found){ // se non l'ho ancora trovato
				searchBookFromIsbn(aPtr->dxPtr, isbn, bkPtr);
			}
		}
	}
}