#include <stdio.h>
#include <stdlib.h>

typedef struct _edges{
    size_t num_edges; //  numero di nodi adiacenti (out-degree in questo caso)
	size_t size; // Necessaria solo se dovete aggiungere archi dinamicamente
    size_t *edges; // array dei nodi adiacenti
    int color; // colore del vertice per le visite
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
        G[i].color = 0; // 0 indica che il nodo non è stato visitato
        for (j = 0; j < ne; ++j){
            scanf("%ld", &to);
			graph_add_edge(G, i, to); // aggiunge al vertice i, del grafo g, l'arco dal vertice i al vertice to
        }
    }
    return G;
}
/*----*/


void dfs_visit(edges* g, int i, int *num_visited_nodes){
    g[i].color = 1;
    ++(*num_visited_nodes);
    int j = 0, index;
    edges v;
    for(j=0; j<g[i].num_edges; ++j){
        index = g[i].edges[j]; // indice in g del j-esimo vertice adiacente
        v = g[index]; // j-esimo vertice adiacente a g[i]
        if(v.color == 0){ // il vertice v non è ancora stato visitato, lo visito
            dfs_visit(g, index, num_visited_nodes);
        }
    }
}

int dfs_num_visited_nodes(edges* g, int src){
    int num_visited_nodes = 0;
    dfs_visit(g, src, &num_visited_nodes);
    return num_visited_nodes;
}

int main(){
    int num_nodes;
    scanf("%d", &(num_nodes));// leggo il numero di nodi da input
    edges *g = read_graph(num_nodes);//  leggo il grafo da input
    int starting_node = 0; // nodo casuale da cui partire
    int num_visited_nodes = dfs_num_visited_nodes(g, starting_node); // far partire una dfs per ottenere il numero di nodi "colorati"
    if (num_visited_nodes < num_nodes){  // numero di nodi "colorati" < numero di nodi effettivi del grafo
        puts("0");  // non ho "colorato" tutti i nodi, ovvero il grafo non è connesso
    }else{
        puts("1");  // ho "colorato" tutti i nodi, num_visited_nodes == num_nodes
    }
    free_graph(g, num_nodes);
    return 0;
}