#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main(){

    Descritor lista;

    lista.tamanho = 0;
    lista.inicio = NULL;

    Nodo *n1 = malloc(sizeof(Nodo));
    Nodo *n2 = malloc(sizeof(Nodo));

    n1->dt = 10;
    n2->dt = 20;

    insere(&lista, n1, 1);
    insere(&lista, n2, 2);

    printf("Tamanho da lista: %d\n", lista.tamanho);

    reinicia(&lista);

    printf("Tamanho apos reinicia: %d\n", lista.tamanho);

    return 0;
}