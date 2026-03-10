#include <stdio.h>
#include "informacao.h"

int main(void)
{
    informacao *p = NULL;
    informacao x = {321, 2.39, "Silva"};

    p = &x;

    if (p)
    {
        printf("ponteiro inicializado corretamente\n");
        printf("valores da struct X: %i, %.2f, %s\n",
               p->inteiro, p->real, p->nome);
    }
    else
        printf("o ponteiro está anulado\n");

    return 0;
}