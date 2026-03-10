#include <stdio.h>
#include <stdlib.h>

// Lista simplesmente encadeada
struct xxx {
    int w;              // valor do nó (só para visualizar)
    struct xxx *b;      // ponteiro para o próximo
};

int main() {
    // Nós da lista
    struct xxx n1 = {1, NULL};
    struct xxx n2 = {2, NULL};
    struct xxx n3 = {3, NULL};

    // Ponteiros dados pelo enunciado
    struct xxx *pt1, *pt2, *pt3;

    // ===== ESTADO INICIAL (A1) =====
    // pt1 → n1 → n3 → NULL
    // pt2 → n2 → NULL
    // pt3 → n3

    pt1 = &n1;
    pt2 = &n2;
    pt3 = &n3;

    n1.b = &n3;   // n1 → n3
    n2.b = NULL;  // n2 isolado
    n3.b = NULL;  // fim da lista

    printf("=== Antes (A1) ===\n");
    struct xxx *p = pt1;
    while (p) {
        printf("%d -> ", p->w);
        p = p->b;
    }
    printf("NULL\n");

    // ===== OPERAÇÃO PEDIDA =====
    // Inserir nó pt2 entre pt1 e pt3
    // Menor número de comandos:

    pt2->b = pt3;   // N2 passa a apontar para N3
    pt1->b = pt2;   // N1 passa a apontar para N2

    // ===== ESTADO FINAL (A2) =====
    // pt1 → n1 → n2 → n3 → NULL

    printf("\n=== Depois (A2) ===\n");
    p = pt1;
    while (p) {
        printf("%d -> ", p->w);
        p = p->b;
    }
    printf("NULL\n");

    return 0;
}