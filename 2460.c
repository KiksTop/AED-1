#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    int *fila = (int*) malloc((size_t)N * sizeof(int));
    for (int i = 0; i < N; i++) scanf("%d", &fila[i]);

    int M;
    scanf("%d", &M);

    /* IDs em [1, 1_000_000] -> marcações de quem saiu */
    const int LIM_ID = 1000000;
    unsigned char *saiu = (unsigned char*) calloc(LIM_ID + 1, sizeof(unsigned char));

    for (int i = 0; i < M; i++) {
        int id;
        scanf("%d", &id);
        if (id >= 1 && id <= LIM_ID) saiu[id] = 1;
    }

    /* Imprime os que permaneceram, na ordem original de chegada */
    int primeiro = 1;
    for (int i = 0; i < N; i++) {
        int id = fila[i];
        if (id >= 1 && id <= LIM_ID && !saiu[id]) {
            if (!primeiro) printf(" ");
            printf("%d", id);
            primeiro = 0;
        }
    }
    printf("\n");

    free(fila);
    free(saiu);
    return 0;
}
