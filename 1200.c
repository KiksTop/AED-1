#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    char conteudo;
    struct no *esq, *dir;
} no;

typedef no *arvore;

arvore insere(arvore r, char x) {
    if (r == NULL) {
        arvore novo = (arvore) malloc(sizeof(no));
        novo->conteudo = x;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (x < r->conteudo)
        r->esq = insere(r->esq, x);
    else if (x > r->conteudo)
        r->dir = insere(r->dir, x);
    return r;
}

int pertence(arvore r, char x) {
    if (r == NULL) return 0;
    if (x == r->conteudo) return 1;
    if (x < r->conteudo) return pertence(r->esq, x);
    return pertence(r->dir, x);
}

int primeiro; /* controle para espaços na impressão */

void infixa(arvore r) {
    if (r == NULL) return;
    infixa(r->esq);
    if (!primeiro) printf(" ");
    printf("%c", r->conteudo);
    primeiro = 0;
    infixa(r->dir);
}

void prefixa(arvore r) {
    if (r == NULL) return;
    if (!primeiro) printf(" ");
    printf("%c", r->conteudo);
    primeiro = 0;
    prefixa(r->esq);
    prefixa(r->dir);
}

void posfixa(arvore r) {
    if (r == NULL) return;
    posfixa(r->esq);
    posfixa(r->dir);
    if (!primeiro) printf(" ");
    printf("%c", r->conteudo);
    primeiro = 0;
}

int main(void) {
    arvore a = NULL;
    char comando[20];
    char x;

    while (scanf("%s", comando) != EOF) {
        if (strcmp(comando, "I") == 0) {
            scanf(" %c", &x);
            a = insere(a, x);
        } else if (strcmp(comando, "P") == 0) {
            scanf(" %c", &x);
            if (pertence(a, x))
                printf("%c existe\n", x);
            else
                printf("%c nao existe\n", x);
        } else if (strcmp(comando, "INFIXA") == 0) {
            primeiro = 1;
            infixa(a);
            printf("\n");
        } else if (strcmp(comando, "PREFIXA") == 0) {
            primeiro = 1;
            prefixa(a);
            printf("\n");
        } else if (strcmp(comando, "POSFIXA") == 0) {
            primeiro = 1;
            posfixa(a);
            printf("\n");
        }
    }

    return 0;
}
