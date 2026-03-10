#include <stdio.h>
#include <string.h>

struct teste2 {
    int inteiro;
    float real;
    char nome[30];
    struct teste2 *self;
};

int main() {
    struct teste2 x = {115, 2.5, "Smith", NULL};
    struct teste2 *p = NULL;

    p = &x;
    p->self = &x;

    printf("Endereco de x:        %p\n", (void*)&x);
    printf("Valor de p:           %p\n", (void*)p);
    printf("Valor de p->self:     %p\n", (void*)p->self);

    // Conferindo dados
    printf("\nConteudo de x:\n");
    printf("inteiro: %d\n", x.inteiro);
    printf("real: %.2f\n", x.real);
    printf("nome: %s\n", x.nome);

    return 0;
}