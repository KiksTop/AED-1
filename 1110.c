//1110.c Throwing Cards Away
#include <stdio.h>

int main(void) {
    int n;
    while (scanf("%d", &n) == 1 && n != 0) {
        int q[60];          // fila: n <= 50 cabe folgado 
        int disc[60];       // sequência de descartes    
        int topo = 0;       // índice do início (saída da fila)
        int base = 0;       // próxima posição livre (entrada na fila)
        int qtd  = 0;       // quantidade na fila
        int capac  = 60;      // capacidade para o módulo
        int dcount = 0;
        int i;

        // enfileira 1..n 
        for (i = 1; i <= n; ++i) {
            q[base] = i;
            base = (base + 1) % capac;
            qtd++;
        }

        // simulação: descarta topo e move o próximo para o fim
        while (qtd > 1) {
            // descarta topo
            disc[dcount++] = q[topo];
            topo = (topo + 1) % capac;
            qtd--;

            // move o próximo para o fim
            {
                int x = q[topo];
                topo = (topo + 1) % capac;
                qtd--;
                q[base] = x;
                base = (base + 1) % capac;
                qtd++;
            }
        }

        // saída
        printf("Discarded cards:");
        if (dcount > 0) {
            printf(" ");
            for (i = 0; i < dcount; ++i) {
                if (i) printf(", ");
                printf("%d", disc[i]);
            }
        }
        printf("\nRemaining card: %d\n", q[topo]);
    }
    return 0;
}
