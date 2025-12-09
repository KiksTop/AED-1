#include <stdio.h>

int main() {
    double N1, N2, N3, N4, exam, avg, final;

    scanf("%lf %lf %lf %lf", &N1, &N2, &N3, &N4);

    avg = (N1*2 + N2*3 + N3*4 + N4*1) / 10.0;

    printf("Media: %.1f\n", avg);

    if (avg >= 7.0) {
        printf("Aluno aprovado.\n");
    }
    else if (avg < 5.0) {
        printf("Aluno reprovado.\n");
    }
    else {  
        printf("Aluno em exame.\n");
        scanf("%lf", &exam);
        printf("Nota do exame: %.1f\n", exam);

        final = (avg + exam) / 2.0;

        if (final >= 5.0)
            printf("Aluno aprovado.\n");
        else
            printf("Aluno reprovado.\n");

        printf("Media final: %.1f\n", final);
    }

    return 0;
}
