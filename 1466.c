#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int conteudo;
    struct no *esq, *dir;
} no;

typedef no *arvore;

/* insere em BST */
arvore insere(arvore r, int x) {
    if (r == NULL) {
        arvore novo = (arvore) malloc(sizeof(no));
        novo->conteudo = x;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (x < r->conteudo)
        r->esq = insere(r->esq, x);
    else
        r->dir = insere(r->dir, x);
    return r;
}

/* travessia em largura usando fila */
void nivel(arvore r) {
    if (r == NULL) return;
    
    arvore fila[501];  /* máximo 500 nós */
    int ini = 0, fim = 0;
    int primeiro = 1;
    
    fila[fim++] = r;
    
    while (ini < fim) {
        arvore atual = fila[ini++];
        
        /* imprime com controle de espaço */
        if (!primeiro) printf(" ");
        printf("%d", atual->conteudo);
        primeiro = 0;
        
        if (atual->esq) fila[fim++] = atual->esq;
        if (atual->dir) fila[fim++] = atual->dir;
    }
}

int main(void) {
    int C;
    scanf("%d", &C);
    
    for (int caso = 1; caso <= C; caso++) {
        int N;
        scanf("%d", &N);
        
        arvore a = NULL;
        for (int i = 0; i < N; i++) {
            int x;
            scanf("%d", &x);
            a = insere(a, x);
        }
        
        printf("Case %d:\n", caso);
        nivel(a);
        printf("\n\n");
        
        /* libera memória (opcional, mas boa prática) */
        /* código de liberação omitido por simplicidade */
    }
    
    return 0;
}
