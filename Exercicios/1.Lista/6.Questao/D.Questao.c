#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int contaNodoDescritor(struct descritor *p){

    if(p == NULL)
        return 0;

    return p->posicao;
}

int main(){

    struct descritor d;

    d.posicao = 3;

    printf("D: %d\n", contaNodoDescritor(&d));

    return 0;
}