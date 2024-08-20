
#include "pessoa.h"

#ifndef FILA_H
#define FILA_H


typedef struct gerenciaFila { // Nó cabeça
	No* inicio;
	No* fim;
	int quant;
}Fila;

// Inicializa a fila
void inicializaFila(Fila* fila);

// Acrescenta uma pessoa na fila
void enfileirar(Fila* fila, No* pessoa);

// Mostra o cadastro de todas as pessoas na fila
void exibirFila(Fila* fila);

// Remove a pessoa da fila
No* sairDaFila(Fila* fila);

//Apaga todos os elementos da lista
void destruirFila(Fila* fila);

#endif // FILA_H