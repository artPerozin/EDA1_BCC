#include "lista.h"

int reinicia(Descritor *p){

    if(p == NULL)
        return 0;

    Nodo *aux = p->inicio;
    Nodo *tmp;

    while(aux){
        tmp = aux;
        aux = aux->link;
        free(tmp);
    }

    p->inicio = NULL;
    p->tamanho = 0;

    return 1;
}

int insere(Descritor *p, Nodo *novo, int pos){

    if(p == NULL || novo == NULL)
        return 0;

    if(pos < 1 || pos > p->tamanho + 1)
        return 0;

    if(pos == 1){
        novo->link = p->inicio;
        p->inicio = novo;
    }
    else{

        Nodo *aux = p->inicio;

        for(int i = 1; i < pos - 1; i++)
            aux = aux->link;

        novo->link = aux->link;
        aux->link = novo;
    }

    p->tamanho++;

    return 1;
}