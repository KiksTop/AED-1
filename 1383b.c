#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    int *X = NULL;             // 1) ponteiro para o vetor

    if (scanf("%d", &N) != 1 || N <= 0) return 0;

    X = malloc((size_t)N * sizeof *X);       // 2) aloca dinamicamente a memória
    // X = malloc((size_t)N * sizeof(int));  // outra forma de alocar
    if (X == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // 3) leitura do vetor
    for (int i = 0; i < N; i++) {
        scanf("%d", &X[i]);              
    }

    int menor = X[0], pos = 0;
    // 4) busca do menor valor e sua posição
    for (int i = 1; i < N; i++) {
        if (X[i] < menor) { menor = X[i]; pos = i; }
    }

    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", pos);

    free(X);                             // 5) libera a memória alocada
    X = NULL;                            
    return 0;
}