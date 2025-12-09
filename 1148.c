#include <stdio.h>
#include <stdlib.h>

#define MAXN 501
#define MAXE 250001   /* máximo E ~ N^2 (500*500 = 250000) */
#define INF 1000000000

/* armazenamento de arestas (lista com next) */
int head[MAXN];
int to[MAXE], w[MAXE], nxt[MAXE];
int edge_cnt;

/* entrada de arestas originais (para percorrer depois) */
int in_u[MAXE], in_v[MAXE], in_w[MAXE];

/* --- Tarjan (SCC) --- */
int N, E;

int disc[MAXN], low[MAXN], tempo;
int pilha[MAXN], pilha_top;
int in_stack[MAXN];
int comp_id[MAXN], comp_cnt;

/* Dijkstra no grafo condensado */
int head_c[MAXN];
int to_c[MAXE], w_c[MAXE], nxt_c[MAXE];
int edge_cnt_c;

/* heap para Dijkstra */
typedef struct {
    int v;
    int d;
} Node;

Node heap[500000];
int hsz;

void heap_push(int v, int d) {
    heap[++hsz].v = v;
    heap[hsz].d = d;
    int i = hsz;
    while (i > 1 && heap[i].d < heap[i/2].d) {
        Node tmp = heap[i]; heap[i] = heap[i/2]; heap[i/2] = tmp;
        i /= 2;
    }
}

Node heap_pop() {
    Node r = heap[1];
    heap[1] = heap[hsz--];
    int i = 1;
    while (1) {
        int l = 2*i, rgt = l+1, small = i;
        if (l <= hsz && heap[l].d < heap[small].d) small = l;
        if (rgt <= hsz && heap[rgt].d < heap[small].d) small = rgt;
        if (small == i) break;
        Node tmp = heap[i]; heap[i] = heap[small]; heap[small] = tmp;
        i = small;
    }
    return r;
}

/* adiciona aresta no grafo original */
void add_edge(int u, int v, int ww, int store_input_index) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = ww;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;

    if (store_input_index) {
        /* também guardamos a aresta original para reconstrução do condensado */
        in_u[edge_cnt] = u;
        in_v[edge_cnt] = v;
        in_w[edge_cnt] = ww;
    }
}

/* Tarjan recursion */
void tarjan(int u) {
    disc[u] = low[u] = ++tempo;
    pilha[++pilha_top] = u;
    in_stack[u] = 1;

    for (int e = head[u]; e != 0; e = nxt[e]) {
        int v = to[e];
        if (disc[v] == 0) {
            tarjan(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (in_stack[v]) {
            if (disc[v] < low[u]) low[u] = disc[v];
        }
    }

    if (low[u] == disc[u]) {
        comp_cnt++;
        while (1) {
            int v = pilha[pilha_top--];
            in_stack[v] = 0;
            comp_id[v] = comp_cnt;
            if (v == u) break;
        }
    }
}

/* adiciona aresta no grafo condensado */
void add_edge_c(int u, int v, int ww) {
    edge_cnt_c++;
    to_c[edge_cnt_c] = v;
    w_c[edge_cnt_c] = ww;
    nxt_c[edge_cnt_c] = head_c[u];
    head_c[u] = edge_cnt_c;
}

/* Dijkstra no grafo condensado (componentes indexados de 1..comp_cnt) */
int dijkstra_condensed(int orig_c, int dest_c) {
    if (orig_c == dest_c) return 0;

    static int dist[MAXN];
    for (int i = 1; i <= comp_cnt; i++) dist[i] = INF;

    hsz = 0;
    dist[orig_c] = 0;
    heap_push(orig_c, 0);

    while (hsz > 0) {
        Node no = heap_pop();
        int u = no.v;
        int du = no.d;
        if (du > dist[u]) continue;
        if (u == dest_c) return du;

        for (int e = head_c[u]; e != 0; e = nxt_c[e]) {
            int v = to_c[e];
            int nd = du + w_c[e];
            if (nd < dist[v]) {
                dist[v] = nd;
                heap_push(v, nd);
            }
        }
    }
    return INF;
}

int main(void) {
    while (1) {
        if (scanf("%d %d", &N, &E) != 2) return 0;
        if (N == 0 && E == 0) break;

        /* limpar estruturas */
        for (int i = 1; i <= N; i++) {
            head[i] = 0;
            disc[i] = low[i] = 0;
            in_stack[i] = 0;
            comp_id[i] = 0;
        }
        edge_cnt = 0;
        tempo = 0;
        pilha_top = 0;
        comp_cnt = 0;

        /* ler arestas e construir grafo */
        for (int i = 0; i < E; i++) {
            int x, y, h;
            scanf("%d %d %d", &x, &y, &h);
            /* armazenamos a aresta com índice incremental */
            add_edge(x, y, h, 1);
        }

        /* tarjan para todas nodes */
        for (int i = 1; i <= N; i++) {
            if (disc[i] == 0) tarjan(i);
        }

        /* construir grafo condensado: componentes 1..comp_cnt */
        for (int i = 1; i <= comp_cnt; i++) {
            head_c[i] = 0;
        }
        edge_cnt_c = 0;

        /* percorre todas as arestas originais (1..edge_cnt) */
        for (int e = 1; e <= edge_cnt; e++) {
            int u = in_u[e];
            int v = in_v[e];
            int ww = in_w[e];
            int cu = comp_id[u];
            int cv = comp_id[v];
            if (cu != cv) {
                add_edge_c(cu, cv, ww);
            }
            /* se cu == cv, ignora: custo zero interno é tratado por comp_id check */
        }

        int K;
        scanf("%d", &K);
        for (int q = 0; q < K; q++) {
            int O, D;
            scanf("%d %d", &O, &D);
            int co = comp_id[O];
            int cd = comp_id[D];
            int ans = dijkstra_condensed(co, cd);
            if (ans == INF) printf("Nao e possivel entregar a carta\n");
            else printf("%d\n", ans);
        }
        printf("\n");
    }
    return 0;
}
