#include <string.h>
#include <stdio.h>
#include <stdlib.h>  

#define TAMANHO_CPF 12
#define TAMANHOMAX_NOME 100  
#define NUM_NOMES 10
#define NUM_SOBRENOMES 10
#define MIN_IDADE 18
#define MAX_IDADE 100

char *nomes[NUM_NOMES] = { "Alice", "Miguel", "Maria", "Artur", "Helena", "Joao", "Paulo", "Pedro", "Teo", "Igor" };

char *sobrenomes[NUM_SOBRENOMES] = { "Oliveira", "Silva", "Cardoso", "Santos", "Souza", "Gomes", "Matos", "Nascimento", "Alves", "Pereira" };

typedef struct {
    char Nome[TAMANHOMAX_NOME];
    char CPF[TAMANHO_CPF];
    int Idade;
    int Deficiente;
} Pessoa;

int intAleatorio(int min, int max)
{
    return min + rand() % (max - min + 1); // Max Inclusivo
}

void gerarPessoa(Pessoa *pessoa)
{
    char *nome = nomes[intAleatorio(0, NUM_NOMES - 1)];
    int idade = intAleatorio(MIN_IDADE, MAX_IDADE);
    char cpf[TAMANHO_CPF];

    for(int i = 0; i < TAMANHO_CPF; i++)
    {
        cpf[i] = '0' + rand() % 10; // Num aleatorio de 0 a 9
    }
    cpf[TAMANHO_CPF - 1] = '\0';

    snprintf(pessoa->Nome, TAMANHOMAX_NOME, "%s", nome);
    snprintf(pessoa->CPF, TAMANHO_CPF, "%s", cpf);

    pessoa->Idade = idade;
    pessoa->Deficiente = rand() % 2;
}

int main() {
    srand(rand()); 
    Pessoa *pessoa = (Pessoa*)malloc(sizeof(Pessoa));
    if (pessoa == NULL) {
        perror("Falhou a alocação");
        return 1;
    }

    gerarPessoa(pessoa);
    
    printf("Nome: %s\n", pessoa->Nome);
    printf("CPF: %s\n", pessoa->CPF);
    printf("Idade: %d\n", pessoa->Idade);
    printf("Deficiente: %d\n", pessoa->Deficiente);
     
    free(pessoa);

    return 0;
}

