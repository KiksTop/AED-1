#include <stdio.h>
#include <string.h>

#define MAX 100005   /* linha 7 agora é correta e simples */

char linha[MAX];
char letra[MAX];
int prox[MAX];

int main(void) {
    while (fgets(linha, sizeof(linha), stdin)) {

        int n = strlen(linha);
        if (n > 0 && linha[n - 1] == '\n') {
            linha[n - 1] = '\0';
            n--;
        }

        prox[0] = 0;
        int ultimo = 0;
        int atual = 0;
        int qtd = 0;

        for (int i = 0; i < n; i++) {
            char c = linha[i];

            if (c == '[') {
                atual = 0;
            } else if (c == ']') {
                atual = ultimo;
            } else {
                qtd++;
                letra[qtd] = c;

                prox[qtd] = prox[atual];
                prox[atual] = qtd;

                if (atual == ultimo)
                    ultimo = qtd;

                atual = qtd;
            }
        }

        for (int i = prox[0]; i != 0; i = prox[i])
            putchar(letra[i]);
        putchar('\n');
    }

    return 0;
}
