#include <stdio.h>

// Criando um apelido para unsigned int
typedef unsigned int uint;

// Criando um tipo Pessoa com typedef
typedef struct {
    char nome[50];
    int idade;
} Pessoa;

int main() {

    uint numero = 100;
    printf("Numero (uint): %u\n\n", numero);

    Pessoa p1;

    snprintf(p1.nome, sizeof(p1.nome), "Arthur");
    p1.idade = 20;

    printf("Pessoa criada com typedef:\n");
    printf("Nome: %s\n", p1.nome);
    printf("Idade: %d\n", p1.idade);

    return 0;
}