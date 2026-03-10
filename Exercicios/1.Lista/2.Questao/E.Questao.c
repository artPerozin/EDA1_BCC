#include <stdio.h>
#include <stdlib.h>
#include "informacao.h"

int main (void)
{
    informacao *p = NULL;
    informacao x = {321, 2.39, "Silva"};
    p = (struct teste *) malloc(sizeof(struct teste));
    p = &x;
    printf("Campos da variavel x: %i, %f, %s", p->inteiro, p->real, p->nome);
}