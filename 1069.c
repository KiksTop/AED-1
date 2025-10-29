#include <stdio.h>

int main(void) {
    int casos;
    if (scanf("%d", &casos) != 1) return 0;

    while (casos--) {
        char linha[1005];
        if (scanf("%1000s", linha) != 1) return 0;

        int pilha = 0;       // conta '<' pendentes
        int diamantes = 0;   // total de diamantes extraídos

        for (int i = 0; linha[i] != '\0'; i++) {
            char c = linha[i];
            if (c == '<') {
                pilha++;
            } else if (c == '>') {
                if (pilha > 0) {
                    pilha--;
                    diamantes++;
                }
            }
            // '.' é ignorado
        }

        printf("%d\n", diamantes);
    }
    return 0;
}
