#include <stdio.h>
#include <stdlib.h>

// Função para trocar dois elementos
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Particiona o vetor usando o último elemento como pivô
int particionar(int *vetor, int inicio, int fim) {
    int pivo = vetor[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (vetor[j] <= pivo) {
            i++;
            trocar(&vetor[i], &vetor[j]);
        }
    }
    trocar(&vetor[i + 1], &vetor[fim]);
    return i + 1;
}

// Implementação recursiva do QuickSort
void quicksort(int *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int indice_pivo = particionar(vetor, inicio, fim);
        quicksort(vetor, inicio, indice_pivo - 1);
        quicksort(vetor, indice_pivo + 1, fim);
    }
}

int main(void) {
    int casos;
    if (scanf("%d", &casos) != 1)
        return 0;

    while (casos--) {
        int n;
        scanf("%d", &n);

        int *vetor = (int*) malloc(n * sizeof(int));
        if (vetor == NULL) return 1;

        for (int i = 0; i < n; i++)
            scanf("%d", &vetor[i]);

        quicksort(vetor, 0, n - 1);

        for (int i = 0; i < n; i++)
            printf("%d%c", vetor[i], (i == n - 1) ? '\n' : ' ');

        free(vetor);
    }

    return 0;
}
