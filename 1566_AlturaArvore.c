#include <stdio.h>
#include <stdlib.h>

typedef struct cel {
    int chave;
    int freq;
    struct cel *esq, *dir;
} No;

No *novo_no(int x) {
    No *p = (No*) malloc(sizeof(No));
    p->chave = x;
    p->freq = 1;
    p->esq = p->dir = NULL;
    return p;
}

No *insere(int x, No *p) {
    if (p == NULL) return novo_no(x);
    if (x < p->chave) p->esq = insere(x, p->esq);
    else if (x > p->chave) p->dir = insere(x, p->dir);
    else p->freq++;
    return p;
}

void escreve_int_com_espaco(int x, int *primeiro) {
    if (*primeiro) {
        printf("%d", x);
        *primeiro = 0;
    } else {
        printf(" %d", x);
    }
}

void in_ordem_imprime(No *p, int *primeiro) {
    if (p == NULL) return;
    in_ordem_imprime(p->esq, primeiro);
    for (int k = 0; k < p->freq; k++) escreve_int_com_espaco(p->chave, primeiro);
    in_ordem_imprime(p->dir, primeiro);
}

void destroi(No *p) {
    if (p == NULL) return;
    destroi(p->esq);
    destroi(p->dir);
    free(p);
}

int main(void) {
    int NC;
    if (scanf("%d", &NC) != 1) return 0;
    for (int caso = 0; caso < NC; caso++) {
        int N, h;
        scanf("%d", &N);
        No *raiz = NULL;
        for (int i = 0; i < N; i++) {
            scanf("%d", &h);
            raiz = insere(h, raiz);
        }
        int primeiro = 1;
        in_ordem_imprime(raiz, &primeiro);
        printf("\n");
        destroi(raiz);
    }
    return 0;
}