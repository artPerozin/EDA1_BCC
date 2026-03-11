# Questão 9 — Uso da diretiva `#include` e encapsulamento em C

A diretiva `#include` da linguagem C permite dividir um programa em múltiplos arquivos, promovendo organização, reutilização de código e ocultação de implementação. Esse processo é frequentemente chamado de **modularização** ou **encapsulamento**.

## Separação em módulos

Em projetos maiores, é comum dividir o sistema em dois tipos principais de módulos:

* **Módulo Cliente**: utiliza funções e estruturas fornecidas por outro módulo.
* **Módulo Servidor**: implementa as funções e estruturas que serão utilizadas.

Entre esses dois módulos existe uma **interface**, normalmente definida em um arquivo **header (`.h`)**.

```
Cliente  <---- interface (.h) ---->  Servidor
```

## Papel do `#include`

A diretiva `#include` permite que um arquivo utilize as declarações presentes em outro arquivo. Geralmente:

* Arquivos **`.h`** contêm:

  * definições de estruturas
  * protótipos de funções
  * constantes

* Arquivos **`.c`** contêm:

  * implementação das funções

Exemplo:

### Arquivo `lista.h` (Interface)

```c
#ifndef LISTA_H
#define LISTA_H

typedef struct nodo{
    int x;
    struct nodo *link;
} Nodo;

int contaNodo(Nodo *p);

#endif
```

Esse arquivo define **o que pode ser usado**, mas não mostra **como foi implementado**.

---

### Arquivo `lista.c` (Implementação)

```c
#include "lista.h"

int contaNodo(Nodo *p){

    int count = 0;

    while(p){
        count++;
        p = p->link;
    }

    return count;
}
```

Aqui está a **implementação real da função**.

---

### Arquivo `main.c` (Cliente)

```c
#include "lista.h"

int main(){
    Nodo *p = NULL;

    int total = contaNodo(p);

    return 0;
}
```

O `main` apenas usa a função declarada no **header**, sem precisar saber como ela foi implementada.

---

## Vantagens do encapsulamento

A separação em módulos traz vários benefícios:

### 1. Ocultação de implementação

O módulo cliente usa apenas a interface, sem acessar detalhes internos do código.

### 2. Organização do projeto

O código fica dividido em arquivos menores e mais fáceis de manter.

### 3. Reutilização

Um módulo pode ser reutilizado em diferentes programas.

### 4. Manutenção facilitada

Mudanças na implementação (`.c`) não afetam os arquivos que utilizam a interface (`.h`).

### 5. Desenvolvimento em equipe

Diferentes programadores podem trabalhar em módulos distintos do sistema.

---

## Conclusão

O uso da diretiva `#include` em conjunto com arquivos `.h` e `.c` permite implementar **encapsulamento em C**, separando a **interface** da **implementação**. Essa abordagem melhora a organização do código, facilita manutenção e promove reutilização de módulos em sistemas maiores.
