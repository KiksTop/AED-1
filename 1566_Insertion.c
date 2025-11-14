#include <stdio.h>
#include <stdlib.h>

void insercao (int v[], int n)
{
   int i, j, x;

   for (i = 1; i < n; i++) {
      x = v[i];
      j = i - 1;

      while (j >= 0 && v[j] > x) {
         v[j+1] = v[j];
         j--;
      }
      v[j+1] = x;
   }
}

int main (void)
{
   int casos;
   if (scanf("%d", &casos) != 1) return 0;

   while (casos--) {
      int n;
      scanf("%d", &n);

      int *v = malloc(n * sizeof(int));
      for (int i = 0; i < n; i++)
         scanf("%d", &v[i]);

      insercao(v, n);

      for (int i = 0; i < n; i++)
         printf("%d%c", v[i], (i == n - 1) ? '\n' : ' ');

      free(v);
   }
   return 0;
}
