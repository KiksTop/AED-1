// parenteses_pilha_lista.c
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

typedef struct {
    No *topo;
} Pilha;

void pilha_inicializar(Pilha *p) {
    p->topo = NULL;
}

void pilha_empilha(Pilha *p, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = p->topo;
    p->topo = novo;
}

int pilha_desempilha(Pilha *p) {
    if (p->topo == NULL)
        return 0; // pilha vazia → erro
    No *remover = p->topo;
    p->topo = remover->prox;
    free(remover);
    return 1;
}

int pilha_vazia(Pilha *p) {
    return p->topo == NULL;
}

void pilha_esvaziar(Pilha *p) {
    while (p->topo != NULL) {
        No *remover = p->topo;
        p->topo = remover->prox;
        free(remover);
    }
}

int main(void) {
    int caractere;
    Pilha pilha;
    pilha_inicializar(&pilha);

    while (1) {
        int correto = 1;
        int leu_algo = 0;

        pilha_esvaziar(&pilha);

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

    pilha_esvaziar(&pilha);
    return 0;
}
