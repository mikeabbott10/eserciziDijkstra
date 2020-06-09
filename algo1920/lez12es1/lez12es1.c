/**
 * Grafo bipartito
 * legge da tastiera un grafo indiretto e restituisce 1 se è bipartito, 0 altrimenti
 * Il grafo viene salvato in memoria tramite liste di adiacenza:
 * (In realtà si ha un array di vertici, ogni vertice non ha una 
 * lista dei vertici adiacenti ma un array di vertici adiacenti)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _edges{
    size_t num_edges;//  numero di nodi adiacenti (out-degree in questo caso)
	size_t size; // Necessaria solo se dovete aggiungere archi dinamicamente
    size_t *edges; // array dei nodi adiacenti
} edges;

/*--Funzioni base per allocazione (dinamica) e deallocazione grafo--*/
// dealloca il grafo g di dimensione n
void free_graph(edges *g, int n){
    int i;
    for (i = 0; i < n; ++i){
        free(g[i].edges);
    }
    free(g);
}

// Rialloca l'array di vertici, raddoppiandone lo spazio disponibile. Necessaria solo se devo aggiungere archi dinamicamente
void edges_double(edges *es) {
	if (es->size == 0)
		es->size = 1;
	es->edges = realloc(es->edges, sizeof(edges) * es->size * 2);
	es->size *= 2;
}
// Aggiunge un arco dal vertice from al vertice to
void graph_add_edge(edges* g, size_t from, size_t to) {
	// Parte non necessaria per l'esercizio
	// In questa implementazione compatta se volete aggiungere dinamicamente
	// archi senza conoscere a priori il numero, dovete utilizzare una politica
	// dimezza-raddoppia per ridimensionare l'array.
	// In questo caso verifichiamo che ci sia uno spazio libero, altrimenti raddoppiamo
	if (g[from].num_edges + 1 > g[from].size) {
		edges_double(g + from);
	}

	g[from].edges[g[from].num_edges] = to;
	g[from].num_edges++;
}

// funzione che legge il grafo da input.
// n : numero di nodi
edges *read_graph(int n){
    edges *G;
	int i, j;
    size_t ne, to;
    G = (edges *)malloc(sizeof(edges) * n);
    for (i = 0; i < n; ++i){
        scanf("%ld", &ne);
        G[i].num_edges = 0; // inizializza a 0 il numero di vertici adiacenti per aggiungerli dinamicamente con graph_add_edge
        G[i].edges = (size_t *) malloc(sizeof(size_t) * ne);  // alloca spazio per ne nuovi vertici (g[i].edges è un array)
		G[i].size = ne; // ne = lunghezza array edges
        for (j = 0; j < ne; ++j){
            scanf("%ld", &to);
			graph_add_edge(G, i, to); // aggiunge al vertice i, del grafo g, l'arco dal vertice i al vertice to
        }
    }
    return G;
}
/*----*/

// Colorazione ricorsiva con visita di tipo DFS:
// Cerca di colorare il vertice pos, del grafo g di dimensione n, col colore c
// (il vertice viene colorato tramite l'array colors -> colors[pos] è il colore del vertice pos)
int graph_color(edges *g, size_t n, int *colors, size_t pos, int c) {
	// Se il vertice è già stato colorato con un colore diverso allora errore
	if (colors[pos] != -1 && colors[pos] != c)
		return 0;
	colors[pos] = c;
	// per ognuno dei vertici adiacenti al vertice pos:
	for (size_t i = 0; i < g[pos].num_edges; i++) {
		size_t to = g[pos].edges[i];
		// Se il vertice che abbiamo raggiunto non era colorato, proviamo a
		// colorarlo con il colore opposto
		if (colors[to] == -1 && !graph_color(g, n, colors, to, !c))
			return 0;
		// Se invece era già colorato, verifichiamo che sia colorato correttamente
		if (colors[to] != -1 && colors[to] != !c)
			return 0;
	}
	return 1;
}

// Verifica che il grafo g, di dimensione n, sia bipartito, restituisce un booleano
// Un grafo è bipartito sse è possibile colorarlo tutto con soli 2 colori.
// Colorare il grafo corrisponde ad assegnare a ciascun vertice
// un colore diverso da quello dei suoi vertici adiacenti.
int graph_is_bipartite(edges* g, size_t n) {
	// Non è necessaria la malloc perché in questo caso non ritorniamo la colorazione
	int colors[n];
	// -1 indica che il vertice non è stato ancora visitato, 
	// inizializzo i colori di tutti gli n vertici
	for (size_t i = 0; i < n; i++)
		colors[i] = -1;
	// La visita è di tipo DFS quindi dobbiamo ripetere la procedura su ogni
	// vertice per assicurarci di visitare ogni vertice, anche quelli isolati
	for (size_t i = 0; i < n; i++) {
		// Se il vertice non è già stato colorato, verifichiamo che
		// la colorazione ricorsiva abbia successo
		// Se non ha successo, allora il grafo ha bisogno di più di 2 colori 
		// per essere colorato tutto e allora non è bipartito -> esco con esito negativo
		if (colors[i] == -1 && !graph_color(g, n, colors, i, 0))
			return 0;
	}
	return 1;
}

int main(int argc, const char* argv[]) {
	size_t n;
	scanf("%lu", &n);
	edges* g = read_graph(n);
	printf("%d\n", graph_is_bipartite(g, n));
	free_graph(g, n);
 	return 0;
}