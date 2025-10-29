#include <stdio.h>

int main(void) {
    int n;

    while (scanf("%d", &n) == 1 && n != 0) {
        while (1) {
            int primeiro;
            if (scanf("%d", &primeiro) != 1) return 0;

            if (primeiro == 0) {          // fim do bloco atual
                printf("\n");             // linha em branco após o bloco
                break;
            }

            int desejado[1005];
            desejado[0] = primeiro;
            for (int i = 1; i < n; i++)   // lê o restante da permutação
                scanf("%d", &desejado[i]);

            // simulação com pilha
            int pilha[1005];
            int topo = 0;                 // pilha vazia
            int proximo = 1;              // próximo vagão chegando de A
            int ok = 1;

            for (int i = 0; i < n; i++) {
                int alvo = desejado[i];

                // empilha até o topo ser o alvo (ou acabarem os que chegam)
                while ((topo == 0 || pilha[topo - 1] != alvo) && proximo <= n) {
                    pilha[topo++] = proximo++;
                }

                if (topo > 0 && pilha[topo - 1] == alvo) {
                    topo--; // envia para B
                } else {
                    ok = 0; // impossível formar a ordem
                    // ainda precisamos consumir os números desta linha? já foram lidos
                    // a simulação acaba aqui
                    break;
                }
            }

            printf(ok ? "Yes\n" : "No\n");
        }
    }

    return 0;
}
