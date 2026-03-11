#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int contaNodo(struct nodo *p){

    struct nodo *visitados[100];
    int count = 0;

    while(p){

        for(int i=0;i<count;i++){
            if(visitados[i] == p)
                return count;
        }

        visitados[count++] = p;
        p = p->link;
    }

    return count;
}

int main(){

    struct nodo *n1 = malloc(sizeof(struct nodo));
    struct nodo *n2 = malloc(sizeof(struct nodo));
    struct nodo *n3 = malloc(sizeof(struct nodo));

    n1->link = n2;
    n2->link = n3;
    n3->link = n2;

    printf("B: %d\n", contaNodo(n1));

    return 0;
}