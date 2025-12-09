#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v;
    int w;
} Aresta;

int cmp_arestas(const void *a, const void *b) {
    Aresta *x = (Aresta*)a;
    Aresta *y = (Aresta*)b;
    if (x->w < y->w) return -1;
    if (x->w > y->w) return 1;
    return 0;
}

/* Disjoint Set Union (Union-Find) */
int pai[200000 + 5];
int rankUF[200000 + 5];

void inicializa_uf(int n) {
    for (int i = 0; i < n; i++) {
        pai[i] = i;
        rankUF[i] = 0;
    }
}

int encontra(int x) {
    if (pai[x] != x)
        pai[x] = encontra(pai[x]);
    return pai[x];
}

void une(int x, int y) {
    x = encontra(x);
    y = encontra(y);
    if (x == y) return;
    if (rankUF[x] < rankUF[y]) {
        pai[x] = y;
    } else if (rankUF[x] > rankUF[y]) {
        pai[y] = x;
    } else {
        pai[y] = x;
        rankUF[x]++;
    }
}

int main(void) {
    int m, n;

    while (1) {
        if (scanf("%d %d", &m, &n) != 2) return 0;
        if (m == 0 && n == 0) break;

        Aresta *arestas = (Aresta*) malloc(n * sizeof(Aresta));
        long long soma_total = 0;

        for (int i = 0; i < n; i++) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            arestas[i].u = x;
            arestas[i].v = y;
            arestas[i].w = z;
            soma_total += z;
        }

        qsort(arestas, n, sizeof(Aresta), cmp_arestas);

        inicializa_uf(m);

        long long custo_mst = 0;
        int arestas_escolhidas = 0;

        for (int i = 0; i < n && arestas_escolhidas < m - 1; i++) {
            int u = arestas[i].u;
            int v = arestas[i].v;
            int w = arestas[i].w;

            if (encontra(u) != encontra(v)) {
                une(u, v);
                custo_mst += w;
                arestas_escolhidas++;
            }
        }

        long long economia = soma_total - custo_mst;
        printf("%lld\n", economia);

        free(arestas);
    }

    return 0;
}
