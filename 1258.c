#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[101];
    char cor[10];
    char tamanho;
} Camiseta;

int valor_tamanho(char t) {
    // Ordem correta exigida pelo problema: P < M < G
    if (t == 'P') return 1;
    if (t == 'M') return 2;
    return 3; // 'G'
}

int comparar(const void *a, const void *b) {
    const Camiseta *c1 = (const Camiseta *)a;
    const Camiseta *c2 = (const Camiseta *)b;

    // Ordenar pela cor (ascendente)
    int r = strcmp(c1->cor, c2->cor);
    if (r != 0) return r;

    // Ordenar pelo tamanho (P < M < G)
    int t1 = valor_tamanho(c1->tamanho);
    int t2 = valor_tamanho(c2->tamanho);
    if (t1 != t2) return t1 - t2;

    // Ordenar pelo nome (ascendente)
    return strcmp(c1->nome, c2->nome);
}

int main() {
    int N;
    int primeiro_caso = 1;

    while (scanf("%d", &N) == 1 && N != 0) {

        Camiseta *lista = (Camiseta *) malloc(N * sizeof(Camiseta));
        getchar(); // consumir o '\n' após o número

        for (int i = 0; i < N; i++) {

            // Lê o nome completo
            fgets(lista[i].nome, sizeof(lista[i].nome), stdin);
            lista[i].nome[strcspn(lista[i].nome, "\n")] = '\0';

            // Lê a linha contendo "cor tamanho"
            char linha[32];
            fgets(linha, sizeof(linha), stdin);

            sscanf(linha, "%s %c", lista[i].cor, &lista[i].tamanho);
        }

        qsort(lista, N, sizeof(Camiseta), comparar);

        if (!primeiro_caso)
            printf("\n");
        primeiro_caso = 0;

        // Imprime na ordem pedida
        for (int i = 0; i < N; i++) {
            printf("%s %c %s\n",
                   lista[i].cor,
                   lista[i].tamanho,
                   lista[i].nome);
        }

        free(lista);
    }

    return 0;
}
