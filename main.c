#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"

int main() {
    srand(rand()); // Gera uma seed aleatoria pro RNG

    Pessoa *pessoa = (Pessoa*)malloc(sizeof(Pessoa));
    if (pessoa == NULL) {
        perror("Falhou a alocação");
        return 1;
    }

    for(int i = 0; i < 5; i++)
    {
        printf("========================\n");
        gerarPessoa(pessoa);
        exibirPessoa(pessoa);
    }
    free(pessoa);

    return 0;
}

