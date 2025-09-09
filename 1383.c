#include <stdio.h>
// comentário para teste de commit
int main(void) {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    const int FULL = 0x3FE; /* bits 1..9 ligados (1022) */
    int mat[9][9];

    for (int inst = 1; inst <= T; inst++) {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                scanf("%d", &mat[i][j]);

        int ok = 1;

        /* Verifica linhas */
        for (int i = 0; i < 9 && ok; i++) {
            int mask = 0;
            for (int j = 0; j < 9; j++) {
                int v = mat[i][j];
                if (v < 1 || v > 9) { ok = 0; break; }
                mask |= (1 << v);
            }
            if (mask != FULL) ok = 0;
        }

        /* Verifica colunas */
        for (int j = 0; j < 9 && ok; j++) {
            int mask = 0;
            for (int i = 0; i < 9; i++) {
                int v = mat[i][j];
                if (v < 1 || v > 9) { ok = 0; break; }
                mask |= (1 << v);
            }
            if (mask != FULL) ok = 0;
        }

        /* Verifica submatrizes 3x3 */
        for (int si = 0; si < 9 && ok; si += 3) {
            for (int sj = 0; sj < 9 && ok; sj += 3) {
                int mask = 0;
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++) {
                        int v = mat[si + i][sj + j];
                        if (v < 1 || v > 9) { ok = 0; i = 3; j = 3; break; }
                        mask |= (1 << v);
                    }
                if (mask != FULL) ok = 0;
            }
        }

        printf("Instancia %d\n", inst);
        printf(ok ? "SIM\n\n" : "NAO\n\n");
    }

    return 0;
}
