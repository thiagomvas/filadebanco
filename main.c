#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"

int main() {
    srand(rand()); 
    Pessoa *pessoa = (Pessoa*)malloc(sizeof(Pessoa));
    if (pessoa == NULL) {
        perror("Falhou a alocação");
        return 1;
    }

    for(int i = 0; i < 5; i++)
    {
        printf("========================\n");
        gerarPessoa(pessoa);
        printf("Nome: %s\n", pessoa->Nome);
        printf("CPF: %s\n", pessoa->CPF);
        printf("Idade: %d\n", pessoa->Idade);
        printf("Deficiente: %d\n", pessoa->Deficiente);

    }
    free(pessoa);

    return 0;
}

