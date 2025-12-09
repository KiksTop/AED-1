#include <stdio.h>
#include <string.h>

int main() {
    int N;
    char s[105];
    
    scanf("%d%*c", &N);  // read N and discard newline

    while (N--) {
        fgets(s, sizeof(s), stdin);

        // remove trailing newline
        int len = strlen(s);
        if (s[len - 1] == '\n') s[--len] = '\0';

        int mid = len / 2;

        // reverse first half
        for (int i = mid - 1; i >= 0; i--)
            putchar(s[i]);

        // reverse second half
        for (int i = len - 1; i >= mid; i--)
            putchar(s[i]);

        putchar('\n');
    }

    return 0;
}
