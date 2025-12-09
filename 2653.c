#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 200003  // tabela hash grande (número primo)

typedef struct No {
    char *str;
    struct No *prox;
} No;

No *hashTable[TAM];

unsigned long hash(const char *s) {
    unsigned long h = 5381;
    int c;
    while ((c = *s++))
        h = ((h << 5) + h) + c;
    return h % TAM;
}

int inserir(const char *s) {
    unsigned long h = hash(s);
    No *atual = hashTable[h];

    while (atual) {
        if (!strcmp(atual->str, s))
            return 0; // já existe, não aumenta o contador
        atual = atual->prox;
    }

    No *novo = (No*)malloc(sizeof(No));
    novo->str = strdup(s); // copia a string
    novo->prox = hashTable[h];
    hashTable[h] = novo;

    return 1; // nova string adicionada
}

int main() {
    char buffer[1000005];
    int diferentes = 0;

    while (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // remover \n
        diferentes += inserir(buffer);
    }

    printf("%d\n", diferentes);

    return 0;
}
