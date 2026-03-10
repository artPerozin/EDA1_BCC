#include <stdio.h>

// Lista duplamente encadeada
struct yyy {
    int k;
    struct yyy *a; // esquerda
    struct yyy *b; // direita
};

void print_lista(struct yyy *inicio) {
    while (inicio) {
        printf("%d ", inicio->k);
        inicio = inicio->b;
        if (inicio) printf("<-> ");
    }
    printf("\n");
}

int main() {
    // Nós
    struct yyy n1 = {1, NULL, NULL};
    struct yyy n2 = {2, NULL, NULL};
    struct yyy nX = {99, NULL, NULL}; // nó a inserir

    struct yyy *pt1, *pt2;

    // ===== Estado inicial (B1) =====
    // n1 <-> n2
    n1.b = &n2;
    n2.a = &n1;

    pt2 = &n2;
    pt1 = &nX; // isolado

    printf("=== Antes (B1) ===\n");
    print_lista(&n1);

    // ===== Inserção =====
    pt1->a = pt2->a;   // esquerda de pt1 = n1
    pt1->b = pt2;      // direita de pt1 = n2
    pt2->a->b = pt1;   // n1->direita = pt1
    pt2->a = pt1;      // n2->esquerda = pt1

    // ===== Estado final (B2) =====
    printf("=== Depois (B2) ===\n");
    print_lista(&n1);

    return 0;
}