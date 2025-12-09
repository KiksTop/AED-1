#include <stdio.h>

int main(void) {
    int n;
    while (scanf("%d", &n) == 1) {
        int rem = 1 % n;
        int len = 1;
        while (rem != 0) {
            rem = (rem * 10 + 1) % n;
            len++;
        }
        printf("%d\n", len);
    }
    return 0;
}
