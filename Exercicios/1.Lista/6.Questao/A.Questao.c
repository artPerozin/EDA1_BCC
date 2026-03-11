#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int contaNodo(struct nodo *p){

    int count = 0;

    while(p){
        count++;
        p = p->link;
    }

    return count;
}

int main(){

    struct nodo *n1 = malloc(sizeof(struct nodo));
    struct nodo *n2 = malloc(sizeof(struct nodo));
    struct nodo *n3 = malloc(sizeof(struct nodo));

    n1->x = 1;
    n2->x = 2;
    n3->x = 3;

    n1->link = n2;
    n2->link = n3;
    n3->link = NULL;

    printf("A: %d\n", contaNodo(n1));

    return 0;
}