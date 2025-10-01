// Verifica se uma string de parênteses está balanceada (sem fgets/puts)
#include <stdio.h>

int main(void) {
    int c;

    while (1) {
        int verif = 0, ok = 1, any = 0;

        // Lê uma linha inteira (até '\n' ou EOF)
        while ((c = getchar()) != EOF && c != '\n') {
            any = 1;
            if (c == '(') {
                verif++;
            } else if (c == ')') {
                if (verif == 0) {
                    ok = 0;            // fechou sem abrir
                } else {
                    verif--;
                }
            }
        }

        // Se não leu nada e chegou EOF, termina
        if (!any && c == EOF) break;

        // Decide a saída para a linha lida
        if (ok && verif == 0) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }

        // Se acabou o arquivo sem '\n' final, termina
        if (c == EOF) break;
    }
    return 0;
}
