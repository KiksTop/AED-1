#include <stdio.h>
#include <stdlib.h>

// Função para intercalar duas metades ordenadas do vetor
void intercalar(int *vetor, int *aux, int inicio, int meio, int fim) {
    int i = inicio;
    int j = meio;
    int k = inicio;

    while (i < meio && j < fim) {
        if (vetor[i] <= vetor[j])
            aux[k++] = vetor[i++];
        else
            aux[k++] = vetor[j++];
    }

    while (i < meio)
        aux[k++] = vetor[i++];

    while (j < fim)
        aux[k++] = vetor[j++];

    // Copia de volta para o vetor original
    for (i = inicio; i < fim; i++)
        vetor[i] = aux[i];
}

// Função recursiva principal do Merge Sort
void mergesort(int *vetor, int *aux, int inicio, int fim) {
    if (fim - inicio <= 1)
        return;

    int meio = (inicio + fim) / 2;

    mergesort(vetor, aux, inicio, meio);
    mergesort(vetor, aux, meio, fim);
    intercalar(vetor, aux, inicio, meio, fim);
}

int main(void) {
    int casos;
    if (scanf("%d", &casos) != 1)
        return 0;

    while (casos--) {
        int n;
        scanf("%d", &n);

        int *vetor = (int*) malloc(n * sizeof(int));
        int *aux   = (int*) malloc(n * sizeof(int));

        for (int i = 0; i < n; i++)
            scanf("%d", &vetor[i]);

        // Ordena o vetor com Merge Sort
        mergesort(vetor, aux, 0, n);

        // Imprime em ordem crescente
        for (int i = 0; i < n; i++)
            printf("%d%c", vetor[i], (i == n - 1) ? '\n' : ' ');

        free(vetor);
        free(aux);
    }

    return 0;
}
