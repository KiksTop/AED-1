//1340.c Código I Can Guess the Data Structure!

#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, x, i, pilha[1000], fila[1000], p=0, f=0, maior=0, aux;
    char c;
    while(scanf("%d", &n) != EOF){
        p = 0; f = 0; maior = 0;
        int pilhaV = 1, filaV = 1, pV = 1;
        for(i=0; i<n; i++){
            scanf(" %c %d", &c, &x);
            if(c == 'I'){
                pilha[p] = x;
                fila[f] = x;
                p++; f++;
                maior++;
            }
            else{
                if(pilhaV){
                    if(p > 0){
                        aux = pilha[p-1];
                        p--;
                        if(aux != x)
                            pilhaV = 0;
                    }
                    else
                        pilhaV = 0;
                }
                if(filaV){
                    if(f > 0){
                        aux = fila[maior - f];
                        f--;
                        if(aux != x)
                            filaV = 0;
                    }
                    else
                        filaV = 0;
                }
                if(pV){
                    int j, encontrou = 0;
                    for(j=maior-1; j>=maior-f; j--){
                        if(fila[j] == x){
                            encontrou = 1;
                            break;
                        }
                    }
                    if(encontrou){
                        pV = 1;
                        maior--;
                    }
                    else
                        pV = 0;
                }
            }
        }
        if(pilhaV && !filaV && !pV)
            printf("stack\n");
        else if(!pilhaV && filaV && !pV)
            printf("queue\n");
        else if(!pilhaV && !filaV && pV)
            printf("priority queue\n");
        else if(!pilhaV && !filaV && !pV)
            printf("impossible\n");
        else
            printf("not sure\n");
    }
    return 0;
}