#include <stdio.h>
#include <stdlib.h>
#include<limits.h>

#define WHITE -1
#define GRAY 0
#define BLACK 1

typedef struct _edges {
	size_t num_edges; // numero di nodi adiacenti (out-degree in questo caso)
	size_t *edges;  // array di vertici adiacenti
    int color;  // colore del vertice per visita
    int d; // distanza dalla sorgente in bfs
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

/*int bfs_min_distance(edges *E, int n, int from, int to) {
    if (from == to) {
        return 0;
    }
    int * dist = (int *) malloc(sizeof(int) * n);
    queue q;
    int src, dest, i;
    // inizializzo le distanze
    for (i=0; i < n; ++i){
        dist[i] = -1;
    }
    dist[from] = 0;
    // inizializzo la coda
    init_queue(&q, n); enqueue(&q, from);
    // loop fino a terminazione della coda
    while (q.head != q.tail) {
        src = dequeue(&q);
        for (i=0; i < E[src].num; ++i) {
            dest = E[src].edges[i];
            if (dist[dest] == -1) {
                dist[dest] = dist[src] + 1;
                if (dest == to) {
                    int result = dist[dest];
                    deinit_queue(&q);
                    free(dist);
                    return result;
                }
            enqueue(&q, dest);
            }
        }
    }
	// libero la memoria
	deinit_queue(&q);
	free(dist);
	return -1;
}*/

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
        E[i].d = -1; // distanza inizialmente non valida
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
    edges * g = read_graph(n);
    int m, from, to;
    scanf("%d", &m);
    int a[m];
    // m query
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &from, &to);
        a[i] = bfs_min_distance(g, n, from, to);
    }
    for(int h = 0; h < m;h++){
        printf("%d\n", a[h]);
    }
	return 0;
}
