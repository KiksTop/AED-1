#include <stdio.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d%*c", &N) != 1) return 0;  // lê N e consome o '\n'

    char s[1005];

    while (N--) {
        if (!fgets(s, sizeof(s), stdin)) break;

        int len = strlen(s);
        if (len > 0 && s[len - 1] == '\n') {
            s[--len] = '\0';  // remove '\n'
        }

        // 1) Deslocar letras +3 na ASCII
        for (int i = 0; i < len; i++) {
            if ((s[i] >= 'a' && s[i] <= 'z') ||
                (s[i] >= 'A' && s[i] <= 'Z')) {
                s[i] = s[i] + 3;
            }
        }

        // 2) Reverter a string
        for (int i = 0, j = len - 1; i < j; i++, j--) {
            char tmp = s[i];
            s[i] = s[j];
            s[j] = tmp;
        }

        // 3) Deslocar metade final -1 na ASCII
        for (int i = len / 2; i < len; i++) {
            s[i] = s[i] - 1;
        }

        printf("%s\n", s);
    }

    return 0;
}
