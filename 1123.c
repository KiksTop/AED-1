#include <stdio.h>
#include <limits.h>

#define MAXN 250
#define INF  1000000000

int N, M, C, K;
int adj[MAXN][MAXN];
int dist[MAXN];
int visit[MAXN];

void dijkstra(int src) {
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        visit[i] = 0;
    }
    dist[src] = 0;

    for (int it = 0; it < N; it++) {
        int u = -1, best = INF;
        for (int i = 0; i < N; i++) {
            if (!visit[i] && dist[i] < best) {
                best = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        visit[u] = 1;

        for (int v = 0; v < N; v++) {
            if (adj[u][v] >= 0 && !visit[v]) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }
}

int main(void) {
    while (1) {
        if (scanf("%d %d %d %d", &N, &M, &C, &K) != 4) return 0;
        if (N == 0 && M == 0 && C == 0 && K == 0) break;

        /* inicializa matriz de adjacência */
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                adj[i][j] = -1;

        for (int i = 0; i < M; i++) {
            int U, V, P;
            scanf("%d %d %d", &U, &V, &P);

            /* grafo não direcionado: guarda menor peso se houver múltiplas arestas */
            if (adj[U][V] == -1 || P < adj[U][V]) {
                adj[U][V] = adj[V][U] = P;
            }
        }

        /* aplica regra da rota de serviço:
           - entre cidades 0..C-1 só pode ter aresta (i, i+1) e (i+1, i)
           - de cidades >= C, arestas livres. */
        for (int i = 0; i < C; i++) {
            for (int j = 0; j < N; j++) {
                if (adj[i][j] == -1) continue;
                if (i < C - 1) {
                    if (j != i + 1) {
                        /* não pode sair de i para j (j != i+1) */
                        adj[i][j] = -1;
                    }
                } else { /* i == C-1: destino, não precisa sair dele */
                    adj[i][j] = -1;
                }
            }
        }
        /* também garantir que só se entra na rota pelo sentido correto */
        for (int j = 0; j < C; j++) {
            for (int i = C; i < N; i++) {
                /* pode entrar em qualquer cidade da rota vindo de fora,
                   mas já restringimos as saídas da rota acima */
                /* adj[i][j] permanece como está */
            }
        }

        dijkstra(K);

        printf("%d\n", dist[C - 1]);
    }

    return 0;
}
