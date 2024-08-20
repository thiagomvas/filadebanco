#include "fila.h"
#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Inicializa a fila
void inicializaFila(Fila* fila) {
	fila->inicio = NULL;
	fila->fim = NULL;
	fila->quant = 0;
}

// Acrescenta uma pessoa na fila
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

// Mostra o cadastro de todas as pessoas na fila
void exibirFila(Fila* fila) {
	No* tempPessoa = fila->inicio;
	while (tempPessoa != NULL) {
		exibirPessoa(tempPessoa);
		tempPessoa = tempPessoa->prox;
	}
}

// Remove a pessoa da fila
No* sairDaFila(Fila* fila) {
	No* primeiroNo = fila->inicio;
	fila->inicio = primeiroNo->prox;
	fila->quant--;
	return primeiroNo;

}

//Apaga todos os elementos da lista 
void destruirFila(Fila* fila) {
	No* tempPessoa = fila->inicio;
	No* tempPessoaAnterior;

	while (tempPessoa != NULL) {
		tempPessoaAnterior = tempPessoa;
		tempPessoa = tempPessoa->prox;
		free(tempPessoaAnterior);
	}

	fila->inicio = NULL;
	fila->fim = NULL;
	fila->quant = 0;
}
