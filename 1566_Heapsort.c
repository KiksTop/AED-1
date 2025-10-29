#include <stdio.h>
#include <stdlib.h>

/* Ajusta o heap máximo descendo o elemento na posição i (0-based) */
void ajustar_heap(int *vetor, int tamanho, int i) {
    for (;;) {
        int maior = i;
        int esq = 2 * i + 1;
        int dir = esq + 1;

        if (esq < tamanho && vetor[esq] > vetor[maior]) maior = esq;
        if (dir < tamanho && vetor[dir] > vetor[maior]) maior = dir;

        if (maior == i) break;

        int tmp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = tmp;

        i = maior;  // continua descendo
    }
}

int main(void) {
    int casos;
    if (scanf("%d", &casos) != 1) return 0;

    while (casos--) {
        int n;
        if (scanf("%d", &n) != 1) return 0;

        int *vetor = (int*) malloc((size_t)n * sizeof(int));
        if (!vetor) return 0;

        for (int i = 0; i < n; i++)
            scanf("%d", &vetor[i]);

        /* 1) Constrói heap máximo (bottom-up) */
        for (int i = (n / 2) - 1; i >= 0; i--)
            ajustar_heap(vetor, n, i);

        /* 2) Repetidamente move o máximo para o fim e restaura o heap */
        for (int fim = n - 1; fim > 0; fim--) {
            int tmp = vetor[0];
            vetor[0] = vetor[fim];
            vetor[fim] = tmp;
            ajustar_heap(vetor, fim, 0);
        }

        /* 3) Imprime ordenado em ordem crescente */
        for (int i = 0; i < n; i++)
            printf("%d%c", vetor[i], (i == n - 1) ? '\n' : ' ');

        free(vetor);
    }

    return 0;
}
