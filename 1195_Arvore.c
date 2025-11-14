#include <stdio.h>
#include <stdlib.h>

typedef struct cel {
    int chave;
    struct cel *esq, *dir;
} No;

No *novo_no(int x) {
    No *p = (No*) malloc(sizeof(No));
    p->chave = x;
    p->esq = p->dir = NULL;
    return p;
}

/* Inserção recursiva: < vai para a esquerda; >= vai para a direita (chaves são distintas) */
No *insere(int x, No *p) {
    if (p == NULL) return novo_no(x);
    if (x < p->chave) p->esq = insere(x, p->esq);
    else              p->dir = insere(x, p->dir);
    return p;
}

/* Impressão sem espaço ao final: usa flag inteiro "primeiro" */
void imprime_num(int x, int *primeiro) {
    if (*primeiro) { printf("%d", x); *primeiro = 0; }
    else           { printf(" %d", x); }
}

void pre_ordem(No *p, int *primeiro) {
    if (p == NULL) return;
    imprime_num(p->chave, primeiro);
    pre_ordem(p->esq, primeiro);
    pre_ordem(p->dir, primeiro);
}

void in_ordem(No *p, int *primeiro) {
    if (p == NULL) return;
    in_ordem(p->esq, primeiro);
    imprime_num(p->chave, primeiro);
    in_ordem(p->dir, primeiro);
}

void pos_ordem(No *p, int *primeiro) {
    if (p == NULL) return;
    pos_ordem(p->esq, primeiro);
    pos_ordem(p->dir, primeiro);
    imprime_num(p->chave, primeiro);
}

void libera(No *p) {
    if (p == NULL) return;
    libera(p->esq);
    libera(p->dir);
    free(p);
}

int main(void) {
    int C;
    if (scanf("%d", &C) != 1) return 0;

    for (int caso = 1; caso <= C; caso++) {
        int N, i, x;
        No *raiz = NULL;

        scanf("%d", &N);
        for (i = 0; i < N; i++) {
            scanf("%d", &x);
            raiz = insere(x, raiz);
        }

        printf("Case %d:\n", caso);

        printf("Pre.: ");
        int primeiro = 1; pre_ordem(raiz, &primeiro); printf("\n");

        printf("In..: ");
        primeiro = 1; in_ordem(raiz, &primeiro); printf("\n");

        printf("Post: ");
        primeiro = 1; pos_ordem(raiz, &primeiro); printf("\n\n");

        libera(raiz);
    }
    return 0;
}