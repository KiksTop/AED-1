#include <stdio.h>
#include <stdlib.h>

#define MAXN 501
#define MAXE 250001   /* máximo E ~ N^2 (500*500 = 250000) */
#define INF 1000000000

/* armazenamento de arestas (lista com proximo) */
int cabeca[MAXN];
int destino[MAXE], custo[MAXE], proximo[MAXE];
int total_arestas;

/* entrada de arestas originais (para percorrer depois) */
int orig_u[MAXE], orig_v[MAXE], orig_custo[MAXE];

/* --- Tarjan (SCC) --- */
int N, E;

int descoberta[MAXN], menor[MAXN], tempo;
int pilha[MAXN], topo_pilha;
int na_pilha[MAXN];
int id_componente[MAXN], total_componentes;

/* Dijkstra no grafo condensado */
int cabeca_c[MAXN];
int destino_c[MAXE], custo_c[MAXE], proximo_c[MAXE];
int total_arestas_c;

/* heap para Dijkstra */
typedef struct {
    int vertice;
    int distancia;
} No;

No heap[500000];
int tamanho_heap;

void empilha(int v, int d) {
    heap[++tamanho_heap].vertice = v;
    heap[tamanho_heap].distancia = d;
    int i = tamanho_heap;
    while (i > 1 && heap[i].distancia < heap[i/2].distancia) {
        No tmp = heap[i]; heap[i] = heap[i/2]; heap[i/2] = tmp;
        i /= 2;
    }
}

No desempilha() {
    No r = heap[1];
    heap[1] = heap[tamanho_heap--];
    int i = 1;
    while (1) {
        int esq = 2*i, dir = esq+1, menor_idx = i;
        if (esq <= tamanho_heap && heap[esq].distancia < heap[menor_idx].distancia) menor_idx = esq;
        if (dir <= tamanho_heap && heap[dir].distancia < heap[menor_idx].distancia) menor_idx = dir;
        if (menor_idx == i) break;
        No tmp = heap[i]; heap[i] = heap[menor_idx]; heap[menor_idx] = tmp;
        i = menor_idx;
    }
    return r;
}

/* adiciona aresta no grafo original */
void adiciona_aresta(int u, int v, int ww, int armazena_entrada) {
    total_arestas++;
    destino[total_arestas] = v;
    custo[total_arestas] = ww;
    proximo[total_arestas] = cabeca[u];
    cabeca[u] = total_arestas;

    if (armazena_entrada) {
        /* também guardamos a aresta original para reconstrução do condensado */
        orig_u[total_arestas] = u;
        orig_v[total_arestas] = v;
        orig_custo[total_arestas] = ww;
    }
}

/* Tarjan recursion */
void tarjan(int u) {
    descoberta[u] = menor[u] = ++tempo;
    pilha[++topo_pilha] = u;
    na_pilha[u] = 1;

    for (int e = cabeca[u]; e != 0; e = proximo[e]) {
        int v = destino[e];
        if (descoberta[v] == 0) {
            tarjan(v);
            if (menor[v] < menor[u]) menor[u] = menor[v];
        } else if (na_pilha[v]) {
            if (descoberta[v] < menor[u]) menor[u] = descoberta[v];
        }
    }

    if (menor[u] == descoberta[u]) {
        total_componentes++;
        while (1) {
            int v = pilha[topo_pilha--];
            na_pilha[v] = 0;
            id_componente[v] = total_componentes;
            if (v == u) break;
        }
    }
}

/* adiciona aresta no grafo condensado */
void adiciona_aresta_c(int u, int v, int ww) {
    total_arestas_c++;
    destino_c[total_arestas_c] = v;
    custo_c[total_arestas_c] = ww;
    proximo_c[total_arestas_c] = cabeca_c[u];
    cabeca_c[u] = total_arestas_c;
}

/* Dijkstra no grafo condensado (componentes indexados de 1..total_componentes) */
int dijkstra_condensado(int orig_c, int dest_c) {
    if (orig_c == dest_c) return 0;

    static int dist[MAXN];
    for (int i = 1; i <= total_componentes; i++) dist[i] = INF;

    tamanho_heap = 0;
    dist[orig_c] = 0;
    empilha(orig_c, 0);

    while (tamanho_heap > 0) {
        No no = desempilha();
        int u = no.vertice;
        int du = no.distancia;
        if (du > dist[u]) continue;
        if (u == dest_c) return du;

        for (int e = cabeca_c[u]; e != 0; e = proximo_c[e]) {
            int v = destino_c[e];
            int nd = du + custo_c[e];
            if (nd < dist[v]) {
                dist[v] = nd;
                empilha(v, nd);
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
            cabeca[i] = 0;
            descoberta[i] = menor[i] = 0;
            na_pilha[i] = 0;
            id_componente[i] = 0;
        }
        total_arestas = 0;
        tempo = 0;
        topo_pilha = 0;
        total_componentes = 0;

        /* ler arestas e construir grafo */
        for (int i = 0; i < E; i++) {
            int x, y, h;
            scanf("%d %d %d", &x, &y, &h);
            /* armazenamos a aresta com índice incremental */
            adiciona_aresta(x, y, h, 1);
        }

        /* tarjan para todas nos */
        for (int i = 1; i <= N; i++) {
            if (descoberta[i] == 0) tarjan(i);
        }

        /* construir grafo condensado: componentes 1..total_componentes */
        for (int i = 1; i <= total_componentes; i++) {
            cabeca_c[i] = 0;
        }
        total_arestas_c = 0;

        /* percorre todas as arestas originais (1..total_arestas) */
        for (int e = 1; e <= total_arestas; e++) {
            int u = orig_u[e];
            int v = orig_v[e];
            int ww = orig_custo[e];
            int cu = id_componente[u];
            int cv = id_componente[v];
            if (cu != cv) {
                adiciona_aresta_c(cu, cv, ww);
            }
            /* se cu == cv, ignora: custo zero interno é tratado por id_componente check */
        }

        int K;
        scanf("%d", &K);
        for (int q = 0; q < K; q++) {
            int O, D;
            scanf("%d %d", &O, &D);
            int co = id_componente[O];
            int cd = id_componente[D];
            int ans = dijkstra_condensado(co, cd);
            if (ans == INF) printf("Nao e possivel entregar a carta\n");
            else printf("%d\n", ans);
        }
        printf("\n");
    }
    return 0;
}
