<<<<<<< HEAD
#include <stdio.h>

int main() {
    int N;
    if (scanf("%d", &N) != 1 || N <= 0) return 0;

    int X[N];              
    int *p = X;            // ponteiro para o início do vetor 

    // leitura usando ponteiros 
    for (int i = 0; i < N; i++) {
        scanf("%d", p + i);
    }

    int menor = *p;        // primeiro elemento via ponteiro
    int posicao = 0;

    // busca do menor usando aritmética de ponteiros
    for (int i = 1; i < N; i++) {
        if (*(p + i) < menor) {
            menor = *(p + i);
            posicao = i;
        }
    }
    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", posicao);
    return 0;
}
=======
#include <stdio.h>

int main() {
    int N;
    if (scanf("%d", &N) != 1 || N <= 0) return 0;

    int X[N];              
    int *p = X;            // ponteiro para o início do vetor 

    // leitura usando ponteiros 
    for (int i = 0; i < N; i++) {
        scanf("%d", p + i);
    }

    int menor = *p;        // primeiro elemento via ponteiro
    int posicao = 0;

    // busca do menor usando aritmética de ponteiros
    for (int i = 1; i < N; i++) {
        if (*(p + i) < menor) {
            menor = *(p + i);
            posicao = i;
        }
    }
    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", posicao);
    return 0;
}
>>>>>>> 778744e3694df30abbb4792b48e0f205490583e0
