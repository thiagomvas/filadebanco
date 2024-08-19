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
void gerarPessoa(No *pessoa)
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

    snprintf(pessoa->nome, TAMANHOMAX_NOME, "%s %s %s", nome, sobrenome1, sobrenome2);
    snprintf(pessoa->cpf, TAMANHO_CPF, "%s", cpf);

    pessoa->idade = idade;
    pessoa->deficiente = rand() % 2;
}

void exibirPessoa(No *pessoa)
{
    printf("Nome: %s\n", pessoa->nome);
    printf("CPF: %s\n", pessoa->cpf);
    printf("Idade: %d\n", pessoa->idade);
    printf("Deficiente: %d\n", pessoa->deficiente);
}

No* criarPessoa(const char* nome, const char* cpf, int idade, int deficiente) {
    // Aloca memória para um novo nó
    No* novaPessoa = (No*)malloc(sizeof(No));
    if (novaPessoa == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    // Inicializa os campos do novo nó
    strncpy(novaPessoa->nome, nome, sizeof(novaPessoa->nome) - 1);
    novaPessoa->nome[sizeof(novaPessoa->nome) - 1] = '\0';  // Garante terminação nula
    strncpy(novaPessoa->cpf, cpf, sizeof(novaPessoa->cpf) - 1);
    novaPessoa->cpf[sizeof(novaPessoa->cpf) - 1] = '\0';    // Garante terminação nula
    novaPessoa->idade = idade;
    novaPessoa->deficiente = deficiente;
    novaPessoa->prox = NULL;

    return novaPessoa;
}
