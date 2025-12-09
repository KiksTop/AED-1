#include <stdio.h>

#define MAX 1024

int N, M;
char img[MAX][MAX + 1];
int visitado[MAX][MAX];

typedef struct {
    int x, y;
} Ponto;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void bfs(int sx, int sy) {
    static Ponto fila[MAX * MAX];
    int ini = 0, fim = 0;

    visitado[sx][sy] = 1;
    fila[fim++] = (Ponto){sx, sy};

    while (ini < fim) {
        Ponto p = fila[ini++];
        for (int k = 0; k < 4; k++) {
            int nx = p.x + dx[k];
            int ny = p.y + dy[k];
            if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                if (!visitado[nx][ny] && img[nx][ny] == '.') {
                    visitado[nx][ny] = 1;
                    fila[fim++] = (Ponto){nx, ny};
                }
            }
        }
    }
}

int main(void) {
    if (scanf("%d %d", &N, &M) != 2) return 0;

    for (int i = 0; i < N; i++)
        scanf("%s", img[i]);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            visitado[i][j] = 0;

    int regioes = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (img[i][j] == '.' && !visitado[i][j]) {
                bfs(i, j);
                regioes++;
            }
        }
    }

    printf("%d\n", regioes);
    return 0;
}