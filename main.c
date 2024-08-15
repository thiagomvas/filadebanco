#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"
#include <time.h>


typedef struct gerenciaFila{ // Nó cabeça
  No* inicio;
  No* fim;
  int quant;}Fila;

//Cria nó do tipo de Cliente
No* criarNo(No* pessoa){
  No* novoCliente=(No*)malloc(sizeof(No));
  strcpy(novoCliente->nome,pessoa->nome);
  strcpy(novoCliente->cpf,pessoa->cpf);
  novoCliente->idade=pessoa->idade;
  novoCliente->deficiente=pessoa->deficiente;
  novoCliente->prox=NULL;
  return novoCliente;
}

void inicializaFila(Fila* fila){
  fila->inicio=NULL;
  fila->fim=NULL;
  fila->quant = 0;
}

void enfileirar(Fila* fila, No* pessoa){
  No* novoCliente=criarNo(pessoa);
  if(novoCliente==NULL){
    printf("Falha na alocação\n");
    return;
  }
  if(fila->inicio==NULL){ //caso fila esteja vazia
    fila->inicio=novoCliente;
    fila->fim=novoCliente;
    fila->quant++;
  }
  else{
    fila->fim->prox=novoCliente;// caso fila já tenha alguém
    fila->fim=novoCliente;
    fila->quant++;
  }
}

void cadastar(Fila* filaSemPrioridade,Fila* filaComPrioridade,No* pessoa){
  if(pessoa->idade==60||pessoa->deficiente==1){//condição para ser prioridade
    enfileirar(filaComPrioridade,pessoa);
  }
  else{
    enfileirar(filaSemPrioridade,pessoa);
  }
}

void exibirFila(Fila* fila){
 No *tempPessoa = fila->inicio;
 while(tempPessoa != NULL){
    exibirPessoa(tempPessoa);
    tempPessoa = tempPessoa->prox;
  }
 }
 void sairDaFila(Fila* fila){
  No *primeiroNo = fila->inicio;
  fila->inicio = primeiroNo->prox;
  free(primeiroNo);
  fila->quant--;
 }

int main() {
    srand(time(0)); // Gera uma seed aleatoria pro RNG
    
    Fila filaSemPrioridade;
    Fila filaComPrioridade;

    inicializaFila(&filaSemPrioridade);
    inicializaFila(&filaComPrioridade);

    No *pessoa = (No*)malloc(sizeof(No));
    if (pessoa == NULL) {
        perror("Falhou a alocação");
        return 1;
    }

    for(int i = 0; i < 5; i++)
    {
        
        gerarPessoa(pessoa);
        criarNo(pessoa);
        if(pessoa->deficiente == 0)
          enfileirar(&filaSemPrioridade,pessoa);
        else
          enfileirar(&filaComPrioridade,pessoa);

        
        
    }
    printf("=========================\n");
    printf("Fila com prioridade: \n");
    exibirFila(&filaComPrioridade);
    printf("=========================\n");
    printf("Fila sem prioridade: \n");
    exibirFila(&filaSemPrioridade);
    printf("=========================\n");
    return 0;
}

