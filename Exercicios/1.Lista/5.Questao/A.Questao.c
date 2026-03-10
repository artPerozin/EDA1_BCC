#include <stdio.h>

// Lista duplamente encadeada
struct no {
    char id;
    struct no *esq; // anterior
    struct no *dir; // próximo
};

void imprime_ida(struct no *p) {
    while (p) {
        printf("%c ", p->id);
        p = p->dir;
    }
    printf("\n");
}

void imprime_volta(struct no *p) {
    while (p) {
        printf("%c ", p->id);
        p = p->esq;
    }
    printf("\n");
}

int main(void) {
    // ===== Nós =====
    struct no A = {'A', NULL, NULL};
    struct no B = {'B', NULL, NULL};
    struct no C = {'C', NULL, NULL};

    struct no *p;

    // ===== Estado 1 =====
    // A <-> C   e   B isolado
    A.dir = &C;
    C.esq = &A;

    p = &C;

    printf("Estado 1 (ida):   ");
    imprime_ida(&A);

    // ===== Inserção de B entre A e C =====
    B.esq = &A;   // B aponta para A (esquerda)
    B.dir = &C;   // B aponta para C (direita)
    A.dir = &B;   // A agora aponta para B
    C.esq = &B;   // C agora aponta para B

    // ===== Estado 2 =====
    printf("Estado 2 (ida):   ");
    imprime_ida(&A);

    printf("Estado 2 (volta): ");
    imprime_volta(&C);

    return 0;
}