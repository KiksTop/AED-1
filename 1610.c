#include <stdio.h>

#define NMAX 10000
#define MMAX 30000

int n, m;

/* Lista de adjacência simples com vetores estáticos */
int adj[NMAX + 1][100];   /* cada vértice terá no máximo 100 dependências diretas */
int grau[NMAX + 1];

/* 0 = não visitado, 1 = visitando, 2 = finalizado */
int cor[NMAX + 1];
int existe_ciclo;

void dfs(int v) {
    cor[v] = 1; /* visitando */

    for (int i = 0; i < grau[v]; i++) {
        int u = adj[v][i];

        if (cor[u] == 1) {   /* voltou para um nó em processamento → ciclo */
            existe_ciclo = 1;
            return;
        }
        if (cor[u] == 0) {   /* não visitado */
            dfs(u);
            if (existe_ciclo) return;
        }
    }

    cor[v] = 2; /* finalizado */
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);

        /* zera estruturas */
        for (int i = 1; i <= n; i++) {
            grau[i] = 0;
            cor[i] = 0;
        }

        /* lê arestas (dependências) */
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d %d", &a, &b);

            adj[a][grau[a]++] = b;
        }

        existe_ciclo = 0;

        /* roda DFS em todos os vértices */
        for (int i = 1; i <= n && !existe_ciclo; i++) {
            if (cor[i] == 0)
                dfs(i);
        }

        if (existe_ciclo)
            printf("SIM\n");
        else
            printf("NAO\n");
    }

    return 0;
}
