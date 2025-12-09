#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

int bfs(int sx, int sy, int tx, int ty) {
    int i;

    // Aloca matriz dist dinamicamente (8x8)
    int **dist = (int **)malloc(8 * sizeof(int *));
    for (i = 0; i < 8; i++) {
        dist[i] = (int *)malloc(8 * sizeof(int));
        memset(dist[i], -1, 8 * sizeof(int));
    }

    // Fila dinâmica (no máximo 64 posições)
    int *qx = (int *)malloc(64 * sizeof(int));
    int *qy = (int *)malloc(64 * sizeof(int));
    int head = 0, tail = 0;

    if (sx == tx && sy == ty) {
        // liberar memória antes de retornar
        for (i = 0; i < 8; i++) free(dist[i]);
        free(dist);
        free(qx);
        free(qy);
        return 0;
    }

    dist[sx][sy] = 0;
    qx[tail] = sx;
    qy[tail] = sy;
    tail++;

    while (head < tail) {
        int x = qx[head];
        int y = qy[head];
        head++;

        for (i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;

                if (nx == tx && ny == ty) {
                    int ans = dist[nx][ny];

                    // libera memória
                    for (int k = 0; k < 8; k++) free(dist[k]);
                    free(dist);
                    free(qx);
                    free(qy);

                    return ans;
                }

                qx[tail] = nx;
                qy[tail] = ny;
                tail++;
            }
        }
    }

    // libera memória (não deve chegar aqui)
    for (i = 0; i < 8; i++) free(dist[i]);
    free(dist);
    free(qx);
    free(qy);

    return -1;
}

int main() {
    char a[3], b[3];

    while (scanf("%s %s", a, b) == 2) {
        int sx = a[0] - 'a';
        int sy = a[1] - '1';
        int tx = b[0] - 'a';
        int ty = b[1] - '1';

        int moves = bfs(sx, sy, tx, ty);

        printf("To get from %s to %s takes %d knight moves.\n", a, b, moves);
    }

    return 0;
}
