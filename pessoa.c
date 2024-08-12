#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pessoa.h"

// Nomes usados na geração aleatoria
char *nomes[NUM_NOMES] = { "Alice", "Miguel", "Maria", "Artur", "Helena", "Joao", "Paulo", "Pedro", "Teo", "Igor" };

// Sobrenomes usados na geração aleatoria
char *sobrenomes[NUM_SOBRENOMES] = { "Oliveira", "Silva", "Cardoso", "Santos", "Souza", "Gomes", "Matos", "Nascimento", "Alves", "Pereira" };

// Gera um inteiro aleatorio de min a max (inclusivo)
int intAleatorio(int min, int max)
{
    return min + rand() % (max - min + 1); // Max Inclusivo
}

// Gera dados aleatorios para uma dada pessoa
void gerarPessoa(Pessoa *pessoa)
{
    char *nome = nomes[intAleatorio(0, NUM_NOMES - 1)];
    char *sobrenome1 = sobrenomes[intAleatorio(0, NUM_SOBRENOMES - 1)];
    char *sobrenome2 = sobrenomes[intAleatorio(0, NUM_SOBRENOMES - 1)];
    int idade = intAleatorio(MIN_IDADE, MAX_IDADE);
    char cpf[TAMANHO_CPF];
    for(int i = 0; i < TAMANHO_CPF - 1; i++)
    {
        cpf[i] = '0' + rand() % 10; // Num aleatorio de 0 a 9
    }
    cpf[TAMANHO_CPF - 1] = '\0';

    snprintf(pessoa->Nome, TAMANHOMAX_NOME, "%s %s %s", nome, sobrenome1, sobrenome2);
    snprintf(pessoa->CPF, TAMANHO_CPF, "%s", cpf);

    pessoa->Idade = idade;
    pessoa->Deficiente = rand() % 2;
}

void exibirPessoa(Pessoa *pessoa)
{
    printf("Nome: %s\n", pessoa->Nome);
    printf("CPF: %s\n", pessoa->CPF);
    printf("Idade: %d\n", pessoa->Idade);
    printf("Deficiente: %d\n", pessoa->Deficiente);
}
