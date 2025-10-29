// parenteses_pilha_vetor.c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *dados;
    int topo;
    int capacidade;
} Pilha;

void pilha_inicializar(Pilha *p) {
    p->capacidade = 64;
    p->topo = 0;
    p->dados = (int*) malloc(sizeof(int) * p->capacidade);
}

void pilha_esvaziar(Pilha *p) {
    p->topo = 0;
}

void pilha_libera(Pilha *p) {
    free(p->dados);
}

void pilha_empilha(Pilha *p, int valor) {
    if (p->topo == p->capacidade) {
        p->capacidade *= 2;
        p->dados = (int*) realloc(p->dados, sizeof(int) * p->capacidade);
    }
    p->dados[p->topo++] = valor;
}

int pilha_desempilha(Pilha *p) {
    if (p->topo == 0)
        return 0; // pilha vazia → erro
    p->topo--;
    return 1;
}

int pilha_vazia(Pilha *p) {
    return p->topo == 0;
}

int main(void) {
    int caractere;
    Pilha pilha;
    pilha_inicializar(&pilha);

    while (1) {
        int correto = 1;
        int leu_algo = 0;

        pilha_esvaziar(&pilha);

        // lê até o fim da linha ou EOF
        while ((caractere = getchar()) != EOF && caractere != '\n') {
            leu_algo = 1;

            if (caractere == '(') {
                pilha_empilha(&pilha, 1);
            } else if (caractere == ')') {
                if (!pilha_desempilha(&pilha)) {
                    correto = 0; // fechou sem abrir
                }
            }
        }

        if (!leu_algo && caractere == EOF)
            break;

        if (correto && pilha_vazia(&pilha))
            printf("correct\n");
        else
            printf("incorrect\n");

        if (caractere == EOF)
            break;
    }

    pilha_libera(&pilha);
    return 0;
}
