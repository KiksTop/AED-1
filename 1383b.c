#include <stdio.h>

int main(void) {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    int mat[9][9];          // sem malloc: matriz fixa 
    int (*m)[9] = mat;      // ponteiro para array de 9 ints (linha)

    for (int inst = 1; inst <= T; inst++) {
        // leitura via ponteiros 
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                scanf("%d", (*(m + i) + j));   /// &mat[i][j]
            }
        }

        int ok = 1;

        // verifica linhas
        for (int i = 0; i < 9 && ok; i++) {
            int seen[10] = {0};
            int *row = *(m + i);                                    // linha i
            for (int j = 0; j < 9; j++) {
                int v = *(row + j);                                 // mat[i][j]
                if (v < 1 || v > 9 || seen[v]) { ok = 0; break; }
                seen[v] = 1;
            }
        }

        // verifica colunas
        for (int j = 0; j < 9 && ok; j++) {
            int seen[10] = {0};
            for (int i = 0; i < 9; i++) {
                int v = *(*(m + i) + j);                            // mat[i][j]
                if (v < 1 || v > 9 || seen[v]) { ok = 0; break; }
                seen[v] = 1;
            }
        }

        // verifica blocos 3x3
        for (int si = 0; si < 9 && ok; si += 3) {
            for (int sj = 0; sj < 9 && ok; sj += 3) {
                int seen[10] = {0};
                for (int di = 0; di < 3 && ok; di++) {
                    int *row = *(m + si + di);                               // linha base do bloco
                    for (int dj = 0; dj < 3; dj++) {
                        int v = *(row + sj + dj);                           // mat[si+di][sj+dj]
                        if (v < 1 || v > 9 || seen[v]) { ok = 0; break; }
                        seen[v] = 1;
                    }
                }
            }
        }

        printf("Instancia %d\n", inst);
        switch (ok) {
            case 1:
                printf("SIM\n\n");
                break;
            default:
                printf("NAO\n\n");
                break;
        }
    }
    return 0;
}
