#include <stdio.h>

#define MAXN 10000

int fila[MAXN];
int dist[MAXN];
int visitado[MAXN];

int inverte(int x) {
    int r = 0;
    while (x > 0) {
        r = r * 10 + (x % 10);
        x /= 10;
    }
    return r;
}

int bfs(int A, int B) {
    int ini = 0, fim = 0;
    for (int i = 0; i < MAXN; i++) {
        visitado[i] = 0;
        dist[i] = -1;
    }

    fila[fim++] = A;
    visitado[A] = 1;
    dist[A] = 0;

    while (ini < fim) {
        int x = fila[ini++];

        if (x == B) return dist[x];

        /* operação 1: x + 1 */
        if (x + 1 < MAXN && !visitado[x + 1]) {
            visitado[x + 1] = 1;
            dist[x + 1] = dist[x] + 1;
            fila[fim++] = x + 1;
        }

        /* operação 2: inverter dígitos */
        int y = inverte(x);
        if (y < MAXN && !visitado[y]) {
            visitado[y] = 1;
            dist[y] = dist[x] + 1;
            fila[fim++] = y;
        }
    }

    return -1; /* não deve acontecer, pois sempre dá para chegar em B via +1 */
}

int main(void) {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    while (T--) {
        int A, B;
        scanf("%d %d", &A, &B);
        int resposta = bfs(A, B);
        printf("%d\n", resposta);
    }

    return 0;
}
