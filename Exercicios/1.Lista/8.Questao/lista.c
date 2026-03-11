#include <stdlib.h>
#include "lista.h"

int contaNodo(Descritor *p){

    if(p == NULL)
        return 0;

    int total = 0;

    for(int i = 0; i < p->TAMvet; i++){

        Nodo *aux = p->vet[i];

        while(aux){
            total++;
            aux = aux->link;
        }
    }

    return total;
}