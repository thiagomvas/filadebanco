#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"
#include <time.h>


typedef struct gerenciaFila { // Nó cabeça
    No* inicio;
    No* fim;
    int quant;
}Fila;

//Cria nó do tipo de Cliente
No* criarNo(No* pessoa) {
    No* novoCliente = (No*)malloc(sizeof(No));
    strcpy(novoCliente->nome, pessoa->nome);
    strcpy(novoCliente->cpf, pessoa->cpf);
    novoCliente->idade = pessoa->idade;
    novoCliente->deficiente = pessoa->deficiente;
    novoCliente->prox = NULL;
    return novoCliente;
}

void inicializaFila(Fila* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->quant = 0;
}

void enfileirar(Fila* fila, No* pessoa) {
    No* novoCliente = criarNo(pessoa);
    if (novoCliente == NULL) {
        printf("Falha na alocação\n");
        return;
    }
    if (fila->inicio == NULL) { //caso fila esteja vazia
        fila->inicio = novoCliente;
        fila->fim = novoCliente;
        fila->quant++;
    }
    else {
        fila->fim->prox = novoCliente;// caso fila já tenha alguém
        fila->fim = novoCliente;
        fila->quant++;
    }
}

void exibirFila(Fila* fila) {
    No* tempPessoa = fila->inicio;
    while (tempPessoa != NULL) {
        exibirPessoa(tempPessoa);
        tempPessoa = tempPessoa->prox;
    }
}
No* sairDaFila(Fila* fila) {
    No* primeiroNo = fila->inicio;
    fila->inicio = primeiroNo->prox;
    fila->quant--;
    return primeiroNo;

}

void limparConsole()
{
#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#else
	system("clear");
#endif  
}

int main() {
    srand(time(0)); // Gera uma seed aleatoria pro RNG

    Fila filaSemPrioridade;
    Fila filaComPrioridade;

    inicializaFila(&filaSemPrioridade);
    inicializaFila(&filaComPrioridade);

    No* pessoa = (No*)malloc(sizeof(No));
    if (pessoa == NULL) {
        perror("Falhou a alocação");
        return 1;
    }

    for (int i = 0; i < 10; i++)
    {
        gerarPessoa(pessoa);

		if (pessoa->deficiente == 1 || pessoa->idade >= 60)
			enfileirar(&filaComPrioridade, pessoa);
		else
			enfileirar(&filaSemPrioridade, pessoa);
    }


    int op = 0;
	char nome[TAMANHOMAX_NOME];
	char cpf[TAMANHO_CPF];
	int idade;
	int deficiente;
    int caixa = 0;

    int prefAtendidos = 0;



    while (op != 4)
    {
		printf("1 - Adicionar pessoa na fila\n");
		printf("2 - Remover pessoa da fila\n");
		printf("3 - Exibir fila\n");
		printf("4 - Sair\n");
		scanf("%d", &op);
		limparConsole();


        // Limpar o buffer do teclado
        while (getchar() != '\n');

		if (op == 1)
		{
            // Pedir dados para o usuário
            printf("Digite o nome: ");
            fgets(pessoa->nome, TAMANHOMAX_NOME, stdin);
            pessoa->nome[TAMANHOMAX_NOME - 1] = '\0';
            printf("Digite o CPF: ");
            fgets(pessoa->cpf, TAMANHO_CPF, stdin);
            pessoa->cpf[TAMANHO_CPF - 1] = '\0';
            printf("Digite a idade: ");
            scanf("%d", &idade);
            printf("Deficiente (1 - Sim, 0 - Não): ");
            scanf("%d", &deficiente);

            pessoa->idade = idade;
            pessoa->deficiente = deficiente;

            if (pessoa->deficiente == 1 || pessoa->idade >= 60)
                enfileirar(&filaComPrioridade, pessoa);
            else
                enfileirar(&filaSemPrioridade, pessoa);
		}
		else if (op == 2)
		{
            printf("Caixa chamando: ");
			scanf("%d", &caixa);

            if (prefAtendidos < 2 && filaComPrioridade.quant > 0)
            {
				pessoa = sairDaFila(&filaComPrioridade);
				prefAtendidos++;
			}
            else if (filaSemPrioridade.quant > 0)
            {
				pessoa = sairDaFila(&filaSemPrioridade);
                prefAtendidos = 0;
			}

            if (pessoa != NULL)
            {
				printf("'%s' está sendo atendido no caixa %d\n", pessoa->nome, caixa);
            }
			else
			{
                printf("Ninguém na fila\n");
            }
		}
		else if (op == 3)
		{
			printf("=========================\n");
			printf("Fila com prioridade: \n");
			exibirFila(&filaComPrioridade);
			printf("=========================\n");
			printf("Fila sem prioridade: \n");
			exibirFila(&filaSemPrioridade);
			printf("=========================\n");
		}
		else if (op == 4)
		{
			break;
		}
    }


    return 0;
}
