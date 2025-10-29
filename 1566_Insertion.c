#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int NC;
    if (scanf("%d", &NC) != 1) return 0;

    while (NC--) {
        int N;
        scanf("%d", &N);
        int *a = (int*)malloc(N * sizeof(int));

        for (int i = 0; i < N; i++)
            scanf("%d", &a[i]);

        // Insertion Sort
        for (int i = 1; i < N; i++) {
            int key = a[i], j = i - 1;
            while (j >= 0 && a[j] > key) {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = key;
        }

        for (int i = 0; i < N; i++)
            printf("%d%c", a[i], i == N - 1 ? '\n' : ' ');

        free(a);
    }
    return 0;
}
