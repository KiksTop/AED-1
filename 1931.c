#include <stdio.h>

#define MAXC 10000
#define MAXV 50000
#define INF  1000000000  /* 1e9, maior que qualquer caminho possível */

typedef struct {
    int v;
    int next;
    int w;
} Edge;

Edge edges[2 * MAXV * 2]; /* cada aresta original gera 4 dirigidas no grafo expandido */
int head[2 * MAXC + 5];
int edge_cnt;

void add_edge(int u, int v, int w) {
    edges[edge_cnt].v = v;
    edges[edge_cnt].w = w;
    edges[edge_cnt].next = head[u];
    head[u] = edge_cnt++;
}

/* heap mínimo para Dijkstra */
typedef struct {
    int dist;
    int node;
} HeapNode;

HeapNode heap[2 * MAXC + 5];
int heap_size;
int pos_heap[2 * MAXC + 5];

void swap_heap(int i, int j) {
    HeapNode tmp = heap[i];
    heap[i] = heap[j];
    heap[j] = tmp;
    pos_heap[heap[i].node] = i;
    pos_heap[heap[j].node] = j;
}

void heap_up(int i) {
    while (i > 1) {
        int p = i / 2;
        if (heap[p].dist <= heap[i].dist) break;
        swap_heap(p, i);
        i = p;
    }
}

void heap_down(int i) {
    while (1) {
        int l = 2 * i, r = l + 1, m = i;
        if (l <= heap_size && heap[l].dist < heap[m].dist) m = l;
        if (r <= heap_size && heap[r].dist < heap[m].dist) m = r;
        if (m == i) break;
        swap_heap(i, m);
        i = m;
    }
}

void heap_push(int node, int dist) {
    heap_size++;
    heap[heap_size].node = node;
    heap[heap_size].dist = dist;
    pos_heap[node] = heap_size;
    heap_up(heap_size);
}

HeapNode heap_pop() {
    HeapNode top = heap[1];
    heap[1] = heap[heap_size];
    pos_heap[heap[1].node] = 1;
    heap_size--;
    heap_down(1);
    return top;
}

void heap_decrease_key(int node, int new_dist) {
    int i = pos_heap[node];
    if (i == 0) { /* ainda não está no heap */
        heap_push(node, new_dist);
        return;
    }
    if (heap[i].dist <= new_dist) return;
    heap[i].dist = new_dist;
    heap_up(i);
}

int main(void) {
    int C, V;

    while (scanf("%d %d", &C, &V) == 2) {
        /* grafo expandido: 0..C-1 (chegou com #pedágios par),
           C..2C-1 (chegou com #pedágios ímpar) */
        int total_nodes = 2 * C;

        for (int i = 0; i < total_nodes; i++)
            head[i] = -1;
        edge_cnt = 0;

        for (int i = 0; i < V; i++) {
            int c1, c2, g;
            scanf("%d %d %d", &c1, &c2, &g);
            c1--; c2--; /* 0-based */

            int u_even = c1;
            int u_odd  = c1 + C;
            int v_even = c2;
            int v_odd  = c2 + C;

            /* grafo não direcionado; ao usar uma aresta, a paridade (#pedágios) troca */
            add_edge(u_even, v_odd, g);
            add_edge(v_even, u_odd, g);
            add_edge(u_odd,  v_even, g);
            add_edge(v_odd,  u_even, g);
        }

        static int dist[2 * MAXC + 5];
        static char visited[2 * MAXC + 5];
        static int pos_local[2 * MAXC + 5];

        for (int i = 0; i < total_nodes; i++) {
            dist[i] = INF;
            visited[i] = 0;
            pos_heap[i] = 0;
        }

        int src = 0;        /* cidade 1 com #pedágios par (0) */
        int dst = C - 1;    /* cidade C com #pedágios par (0) */

        dist[src] = 0;
        heap_size = 0;
        heap_push(src, 0);

        while (heap_size > 0) {
            HeapNode hn = heap_pop();
            int u = hn.node;
            if (visited[u]) continue;
            visited[u] = 1;
            if (u == dst) break;

            for (int e = head[u]; e != -1; e = edges[e].next) {
                int v = edges[e].v;
                int w = edges[e].w;
                if (!visited[v] && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    heap_decrease_key(v, dist[v]);
                }
            }
        }

        if (dist[dst] == INF)
            printf("-1\n");
        else
            printf("%d\n", dist[dst]);
    }

    return 0;
}
