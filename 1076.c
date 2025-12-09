#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000
#define MAXV 60
#define MAXODD 20

int distm[MAXV][MAXV];
int grau[MAXV];
int impares[MAXODD];
int qtdImp;

int *dp;

int min(int a, int b) { return a < b ? a : b; }

/* DP para emparelhar todos os vértices ímpares */
int solve(int mask) {
    if (mask == (1 << qtdImp) - 1) return 0;
    if (dp[mask] != -1) return dp[mask];

    int i;
    for (i = 0; i < qtdImp; i++)
        if (!(mask & (1 << i))) break;

    int melhor = INF;

    for (int j = i + 1; j < qtdImp; j++) {
        if (!(mask & (1 << j))) {
            int novo = mask | (1 << i) | (1 << j);
            int custo = distm[impares[i]][impares[j]] + solve(novo);
            melhor = min(melhor, custo);
        }
    }

    return dp[mask] = melhor;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int start;
        scanf("%d", &start);

        int V, A;
        scanf("%d %d", &V, &A);

        for (int i = 0; i < V; i++) {
            grau[i] = 0;
            for (int j = 0; j < V; j++)
                distm[i][j] = (i == j ? 0 : INF);
        }

        int x, y;
        int somaArestas = 0;

        for (int i = 0; i < A; i++) {
            scanf("%d %d", &x, &y);
            distm[x][y] = distm[y][x] = 1;
            grau[x]++; grau[y]++;
            somaArestas++;
        }

        for (int k = 0; k < V; k++)
            for (int i = 0; i < V; i++)
                for (int j = 0; j < V; j++)
                    if (distm[i][k] + distm[k][j] < distm[i][j])
                        distm[i][j] = distm[i][k] + distm[k][j];

        qtdImp = 0;
        for (int i = 0; i < V; i++)
            if (grau[i] % 2 == 1)
                impares[qtdImp++] = i;

        int total = somaArestas;

        if (qtdImp > 0) {
            int tam = 1 << qtdImp;
            dp = malloc(sizeof(int) * tam);
            for (int i = 0; i < tam; i++) dp[i] = -1;

            total += solve(0);
            free(dp);
        }

        printf("%d\n", total);
    }

    return 0;
}
