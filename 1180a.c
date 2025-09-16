
#include <stdio.h>
#include <stdlib.h>

//programa de localização do menor valor em um vetor sem ponteiros
int main() {
    int N;
    scanf("%d", &N);  
    int X[N];
    int posicao = 0;
    
    for(int i = 0; i < N; i++) {
        scanf("%d", &X[i]);
    }
    int menor = X[0];
    for(int i = 1; i < N; i++) {
        if(X[i] < menor) {
            menor = X[i];
            posicao = i;
        }
    }

    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", posicao);

    return 0;
}