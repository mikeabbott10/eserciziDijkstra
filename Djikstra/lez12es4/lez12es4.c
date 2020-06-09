#include <stdio.h>
#include <stdlib.h>
#define WHITE -1
#define GRAY 0
#define BLACK 1

typedef struct _edges {
	size_t num_edges; // numero di nodi adiacenti (out-degree in questo caso)
	size_t *edges;  // array di vertici adiacenti
    int color;  // colore del vertice per visita
    int d; // distanza dalla sorgente
    size_t pi;  // predecessore nell'albero BF
} edges;

typedef struct _queue {
    int * elements;
    int size;
    int head;
    int tail;
} queue;

void init_queue(queue * Q, int size) {
    Q->elements = (int *) malloc(sizeof(int) * size);
    Q->size = size;
    Q->head = Q->tail = 0;
}

void deinit_queue(queue * Q) {
    free(Q->elements);
    Q->size = 0;
    Q->head = Q->tail = 0;
}

void enqueue(queue * Q, int element) {
    Q->elements[Q->tail++] = element;
}

int dequeue(queue * Q) {
    return Q->elements[Q->head++];
}

void bfs(edges* g, int n, int s){
    int i;
    for(i=0;i<n;++i){
        if(i!=s){
            g[i].color = WHITE;
            g[i].pi = -1;
            g[i].d = -1;
        }
    }
    g[s].color = GRAY;
    g[s].pi = -1;
    g[s].d = 0;
    queue q;
    init_queue(&q, n);
    enqueue(&q, s); // inserisce s in q
    int u_index, v_index;
    while(q.head != q.tail){ // mentre la coda non è vuota
        u_index = dequeue(&q); // estrae da q
        //printf("u -> %d\n", u_index);
        for(i=0;i<g[u_index].num_edges;++i){
            v_index = g[u_index].edges[i];
            if(g[v_index].color == WHITE){ // v non ancora visitato
                g[v_index].color = GRAY;
                g[v_index].pi = u_index;
                g[v_index].d = g[u_index].d + 1;
                enqueue(&q, v_index);
                //printf("\tACCODATO v -> %d\n", v_index);
            }
        }
        g[u_index].color = BLACK;
    }
    deinit_queue(&q);
}

int bfs_min_distance(edges* g, int n, int from, int to){
    bfs(g, n, from);
    return g[to].d;
}

edges *read_graph(int n){
    edges *E;
    int ne;
    int i = 0;
    int j = 0;
    E = (edges *) malloc(sizeof(edges) * n);
    for (i = 0; i < n;++i){
        scanf("%d", &(ne));
        E[i].num_edges = ne;
        E[i].color = WHITE; // vertice inizialmente non visitato
        E[i].pi = -1; // predecessore inizialmente nullo
        E[i].edges = (size_t *) malloc(sizeof(size_t) * ne);
        for (j = 0; j < ne;++j){
            scanf("%ld", E[i].edges + j);
        }
    }
	return E;
}

int main() {
    int n;
    scanf("%d", &n);
    edges * E = read_graph(n);
    int max_min_path = 0, path;
    int i, j;
    for (i = 0; i < n && max_min_path!=-1; ++i) {
        for(j=0; j<n;++j){
            if(i!=j){
                path = bfs_min_distance(E, n, i, j);
                if(path == -1){
                    max_min_path = -1;
                    break;
                }
                if(path > max_min_path){
                    max_min_path = path;
                }
            }
        }
    }
    printf("%d\n", max_min_path);
	return 0;
}
