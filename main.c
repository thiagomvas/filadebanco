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

//Cria estrutura para o caixa;
typedef struct RecebeCliente{
  int clientesAtendidos;
}Caixa;

void inicializaFila(Fila* fila){
  fila->inicio=NULL;
  fila->fim=NULL;
  fila->quant = 0;
}

//Prepara os caixas para recebimentos dos clientes.
void inicializaCaixa(Caixa vetorCaixas[]){
  for(int contador = 0; contador < 5; contador++){
    vetorCaixas[contador].clientesAtendidos = 0;
  }
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

void cadastrar(Fila* filaSemPrioridade,Fila* filaComPrioridade,No* pessoa){
  if(pessoa->idade>=60||pessoa->deficiente==1){//condição para ser prioridade
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
 
 int quantoTempo(Fila *filaPrioridade,Fila *filaNormal,No *pessoa){
	 int prioridade=pessoa->idade>=60||pessoa->deficiente;
	 if(prioridade){
		 int c=0;
		 noAtual=filaPrioridade->inicio;
		 while(noAtual!=pessoa){
			 noAtual=noAtual->prox;
			 c++;
		 }
		 int quantnormal=filaNormal->quant;
		 int quantnormal=quantnormal>c/2?c/2:quantnormal;
		 return c+quantnormal;
	 }
	else{
		int c=0;
		noAtual=filaNormal->inicio;
		 while(noAtual!=pessoa){
			 noAtual=noAtual->prox;
			 c++;
		 }
		 int quantprio=filaPrioridade->quant;
		 int quantprio=quantprio>2*c?2*c:quantprio;
		 return c+quantprio;
	}
 }

//Atende os clientes conforme a prioridade.
 void atendimentoCliente(Fila* fila, Fila* filaPrioridade, Fila* filaUsual, Caixa vetorCaixas[]){
  if(fila->inicio == NULL){
    printf("Nenhum cliente a ser atendido no momento.");
    return;
  }

  int contaPrioridade = 0, contAuxiliar = 0;
  No *aux1 = filaPrioridade -> inicio;
  No *aux2 = filaUsual -> inicio;

  while(filaPrioridade->quant > 0 || filaUsual->quant > 0){
    //Atende primeiramente os clientes que são prioridade na fila.
    if(filaPrioridade->quant > 0 && contaPrioridade != 2){
      printf("Cliente (PRIORIDADE) a ser atendido: %s.\n", aux1->nome);
      printf("Dirigir-se ao caixa de numero: %d.\n", contAuxiliar % 5 + 1);
      vetorCaixas[contAuxiliar % 5].clientesAtendidos++;
      sairDaFila(filaPrioridade);
      contaPrioridade++;
      aux1 = filaPrioridade -> inicio;
    }
    else{
      printf("Cliente a ser atendido: %s.\n", aux2->nome);
      printf("Dirigir-se ao caixa de numero: %d.\n", contAuxiliar % 5 + 1);
      vetorCaixas[contAuxiliar % 5].clientesAtendidos++;
      sairDaFila(filaUsual);
      contaPrioridade = 0;
      aux2 = filaUsual -> inicio;
    }
    contAuxiliar++;
  }

  printf("Atendimento concluido:\n");
  printf("Numero total de clientes atendidos: %d.\n", contAuxiliar);
  for(int contador = 1; contador <= 5; contador++){
    printf("CLIENTES ATENDIDOS PELO CAIXA 0%d: %d.\n", contador, vetorCaixas[contador].clientesAtendidos);
  }

 }

int main() {
    srand(time(0)); // Gera uma seed aleatoria pro RNG
    
    Fila filaSemPrioridade;
    Fila filaComPrioridade;
    Caixa caixas[5];

    inicializaFila(&filaSemPrioridade);
    inicializaFila(&filaComPrioridade);
    inicializaCaixa(caixas);

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

