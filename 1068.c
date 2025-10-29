// balance_array_stack.c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int top;        // número de elementos na pilha
    int cap;        // capacidade alocada
} Stack;

static void stack_init(Stack *s) {
    s->cap = 64;
    s->top = 0;
    s->data = (int*)malloc(sizeof(int) * s->cap);
}
static void stack_clear(Stack *s) { s->top = 0; }
static void stack_free(Stack *s)  { free(s->data); }

static void stack_push(Stack *s, int v) {
    if (s->top == s->cap) {
        s->cap <<= 1;
        s->data = (int*)realloc(s->data, sizeof(int) * s->cap);
    }
    s->data[s->top++] = v;
}
static int stack_empty(const Stack *s) { return s->top == 0; }
static int stack_pop(Stack *s) {
    if (s->top == 0) return 0; // erro
    s->top--;
    return 1;
}

int main(void) {
    int c;
    Stack st;
    stack_init(&st);

    for (;;) {
        int ok = 1, any = 0;
        stack_clear(&st);

        // lê uma linha até '\n' ou EOF
        while ((c = getchar()) != EOF && c != '\n') {
            any = 1;
            if (c == '(') {
                stack_push(&st, 1);
            } else if (c == ')') {
                if (!stack_pop(&st)) {
                    ok = 0; // fechou sem abrir
                }
            }
        }

        if (!any && c == EOF) break;

        // linha válida se não houve erro e pilha ficou vazia
        if (ok && stack_empty(&st)) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }

        if (c == EOF) break; // EOF sem '\n' final
    }

    stack_free(&st);
    return 0;
}
