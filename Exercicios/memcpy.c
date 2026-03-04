#include <stdio.h>
#include <string.h>

int main() {
    // Exemplo: Copiando uma struct
    struct Pessoa {
        char nome[50];
        int idade;
    };

    struct Pessoa p1 = {"Arthur", 20};
    struct Pessoa p2;

    memcpy(&p2, &p1, sizeof(struct Pessoa));

    printf("Struct copiada:\n");
    printf("Nome: %s\n", p2.nome);
    printf("Idade: %d\n", p2.idade);

    return 0;
}