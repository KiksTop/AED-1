#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int nota;
    int indice_original; // posição de chegada (0-based)
} Aluno;

int cmp_desc_estavel(const void *a, const void *b) {
    const Aluno *x = (const Aluno*)a;
    const Aluno *y = (const Aluno*)b;
    if (x->nota != y->nota) {
        return (y->nota - x->nota); // nota decrescente
    }
    // desempate estável: menor índice original vem antes
    return (x->indice_original - y->indice_original);
}

int main(void) {
    int casos;
    if (scanf("%d", &casos) != 1) return 0;

    while (casos--) {
        int m;
        scanf("%d", &m);

        Aluno *fila = (Aluno*) malloc(m * sizeof(Aluno));
        Aluno *ordenado = (Aluno*) malloc(m * sizeof(Aluno));

        for (int i = 0; i < m; i++) {
            scanf("%d", &fila[i].nota);
            fila[i].indice_original = i;
            ordenado[i] = fila[i];
        }

        qsort(ordenado, m, sizeof(Aluno), cmp_desc_estavel);

        int nao_mudam = 0;
        for (int i = 0; i < m; i++) {
            // permanece no mesmo lugar se o aluno que fica na posição i
            // após a ordenação é exatamente quem já estava na posição i
            if (ordenado[i].indice_original == i) nao_mudam++;
        }

        printf("%d\n", nao_mudam);

        free(fila);
        free(ordenado);
    }
    return 0;
}
