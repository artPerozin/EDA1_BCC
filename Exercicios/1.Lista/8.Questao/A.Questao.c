#include <stdio.h>
#include <stdlib.h>
#include "Interface.h"

Nodo* criaNodo(int v){

    Nodo *n = malloc(sizeof(Nodo));
    n->x = v;
    n->link = NULL;

    return n;
}

int main(){

    Descritor d;

    d.TAMvet = 3;
    d.vet = malloc(sizeof(Nodo*) * d.TAMvet);

    /* lista 0 */
    Nodo *a = criaNodo(1);
    Nodo *b = criaNodo(2);
    a->link = b;
    d.vet[0] = a;

    /* lista 1 */
    Nodo *c = criaNodo(3);
    d.vet[1] = c;

    /* lista 2 vazia */
    d.vet[2] = NULL;

    printf("Total de nodos: %d\n", contaNodo(&d));

    return 0;
}