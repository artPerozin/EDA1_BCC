#include <stdio.h>
#include <stdlib.h>
#include "informacao.h"

int main(void)
{
    int a = 10, vet[] = {1,2,3,4,5};
    float b = 35.75;
    informacao y = {31, 2.5, "Wilson"};

    void *ptr;

    // int
    ptr = &a;
    printf("a = %d\n", *((int*) ptr));

    // float
    ptr = &b;
    printf("b = %.2f\n", *((float*) ptr));

    // struct
    ptr = &y;
    printf("nome = %s, inteiro = %d\n",
           ((informacao*) ptr)->nome,
           ((informacao*) ptr)->inteiro);

    // vetor
    printf("\nAcessando vetor com ponteiro:\n");
    int *p = vet;
    for (int i = 0; i < 5; i++, p++)
        printf("vet[%d] = %d\n", i, *p);

    return 0;
}