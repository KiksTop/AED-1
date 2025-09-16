#include <stdio.h>
#include <stdlib.h> 

//programa que verifica se uma solução de Sudoku é válida
int main() {
    int T, mat[9][9];
    if (scanf("%d", &T) != 1) return 0;


    for (int inst = 1; inst <= T; inst++) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                scanf("%d", &mat[i][j]);
            }
        }

        int ok = 1;

        /* Verifica linhas */
        for (int i = 0; i < 9 && ok; i++) {
            int seen[10] = {0};
            for (int j = 0; j < 9 && ok; j++) {
                int v = mat[i][j];
                if (v < 1 || v > 9 || seen[v]) ok = 0;
                else seen[v] = 1;
            }
        }

        /* Verifica colunas */
        for (int j = 0; j < 9 && ok; j++) {
            int seen[10] = {0};
            for (int i = 0; i < 9 && ok; i++) {
                int v = mat[i][j];
                if (v < 1 || v > 9 || seen[v]) ok = 0;
                else seen[v] = 1;
            }
        }

        /* Verifica blocos 3x3 */
        for (int si = 0; si < 9 && ok; si += 3) {
            for (int sj = 0; sj < 9 && ok; sj += 3) {
                int seen[10] = {0};
                for (int di = 0; di < 3 && ok; di++) {
                    for (int dj = 0; dj < 3 && ok; dj++) {
                        int v = mat[si + di][sj + dj];
                        if (v < 1 || v > 9 || seen[v]) ok = 0;
                        else seen[v] = 1;
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

    return 0; 
}

