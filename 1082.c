#include <stdio.h>
#include <string.h>

#define MAXV 26

int V, E;
int grafo[MAXV][MAXV];
int grau[MAXV];
int visitado[MAXV];

void dfs(int v, char comp[], int *tam) {
    visitado[v] = 1;
    comp[(*tam)++] = (char)('a' + v);

    for (int i = 0; i < grau[v]; i++) {
        int u = grafo[v][i];
        if (!visitado[u]) {
            dfs(u, comp, tam);
        }
    }
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    for (int caso = 1; caso <= N; caso++) {
        scanf("%d %d", &V, &E);

        /* zera estruturas */
        for (int i = 0; i < V; i++) {
            grau[i] = 0;
            visitado[i] = 0;
        }

        for (int i = 0; i < E; i++) {
            char a, b;
            scanf(" %c %c", &a, &b);
            int u = a - 'a';
            int v = b - 'a';
            grafo[u][grau[u]++] = v;
            grafo[v][grau[v]++] = u;
        }

        printf("Case #%d:\n", caso);

        int componentes = 0;

        for (int i = 0; i < V; i++) {
            if (!visitado[i]) {
                char comp[MAXV];
                int tam = 0;
                dfs(i, comp, &tam);

                /* comp já está em ordem pois visitamos vértices 0..V-1;
                   ainda assim, garantimos ordenando por segurança */
                for (int x = 0; x < tam; x++) {
                    for (int y = x + 1; y < tam; y++) {
                        if (comp[y] < comp[x]) {
                            char tmp = comp[x];
                            comp[x] = comp[y];
                            comp[y] = tmp;
                        }
                    }
                }

                for (int j = 0; j < tam; j++) {
                    printf("%c,", comp[j]);
                }
                printf("\n");
                componentes++;
            }
        }

        printf("%d connected components\n\n", componentes);
    }

    return 0;
}
