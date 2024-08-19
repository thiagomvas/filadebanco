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
No* criarNo(char nome[],char cpf[],int idade,int deficiente){
  No* novoCliente=(No*)malloc(sizeof(No));
  strcpy(novoCliente->nome,nome);
  strcpy(novoCliente->cpf,cpf);
  novoCliente->idade=idade;
  novoCliente->deficiente=deficiente;
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
  No* novoCliente=pessoa;
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
		 No *noAtual=filaPrioridade->inicio;
		 while(noAtual!=pessoa){
			 noAtual=noAtual->prox;
			 c++;
		 }
		 int quantnormal=filaNormal->quant;
		 quantnormal=quantnormal>c/2?c/2:quantnormal;
		 return c+quantnormal;
	 }
	else{
		int c=0;
		No *noAtual=filaNormal->inicio;
		 while(noAtual!=pessoa){
			 noAtual=noAtual->prox;
			 c++;
		 }
		 int quantprio=filaPrioridade->quant;
		 quantprio=quantprio>2*c?2*c:quantprio;
		 return c+quantprio;
	}
 }

//Atende os clientes um a um conforme a prioridade.
 void atendimentoCliente(Fila* filaPrioridade, Fila* filaUsual, Caixa vetorCaixas[], int *contAuxiliar, int *contaPrioridade){
  if(filaPrioridade->quant == 0 && filaUsual->quant == 0){
    printf("Nenhum cliente a ser atendido no momento.");
    return;
  }

  No *aux1 = filaPrioridade -> inicio;
  No *aux2 = filaUsual -> inicio;

  //Atende primeiramente os clientes que são prioridade na fila.
  if(filaPrioridade->quant > 0 && (*contaPrioridade) != 2){
    printf("Cliente (PRIORIDADE) a ser atendido: %s.\n", aux1->nome);
    printf("Dirigir-se ao caixa de numero: %d.\n", *contAuxiliar % 5 + 1);
    vetorCaixas[*contAuxiliar % 5].clientesAtendidos++;
    sairDaFila(filaPrioridade);
    contaPrioridade++;
    aux1 = filaPrioridade -> inicio;
  }
  else{
    printf("Cliente a ser atendido: %s.\n", aux2->nome);
    printf("Dirigir-se ao caixa de numero: %d.\n", *contAuxiliar % 5 + 1);
    vetorCaixas[*contAuxiliar % 5].clientesAtendidos++;
    sairDaFila(filaUsual);
    contaPrioridade = 0;
    aux2 = filaUsual -> inicio;
  }
  printf("Atendimento concluido:\n");
  contAuxiliar++;
}

//Mostra o veredito do trabalho no dia.
void finalizarExpediente(int contAuxiliar, Caixa vetorCaixas[]){
  printf("Expediente concluido:\n");
  printf("Numero total de clientes atendidos: %d.\n", contAuxiliar);
  for(int contador = 1; contador <= 5; contador++){
    printf("CLIENTES ATENDIDOS PELO CAIXA 0%d: %d.\n", contador, vetorCaixas[contador].clientesAtendidos);
  }
}

 
 void combinarFila(Fila filaComPrioridade, Fila filaSemPrioridade,int prioridadeAtendidos,Fila *resultado){
	Fila novaFila;
	if(filaComPrioridade.quant==0){
		*resultado=filaSemPrioridade;
		return;
  }
	if(filaSemPrioridade.quant==0){
		*resultado=filaComPrioridade;
		return;
  }
	novaFila.inicio=NULL;
	novaFila.fim=NULL;
	novaFila.quant=0;
	int c=prioridadeAtendidos;
	No *semPriorAtual=filaSemPrioridade.inicio;
	No *comPriorAtual=filaComPrioridade.inicio;
	while(semPriorAtual!=NULL && comPriorAtual!=NULL){
		if(c==2){
			enfileirar(&novaFila,semPriorAtual);
			c=0;
			semPriorAtual=semPriorAtual->prox;
		}
		else{
			enfileirar(&novaFila,comPriorAtual);
			c++;
			comPriorAtual=comPriorAtual->prox;
		}
	}
	if(semPriorAtual==NULL){
		while(comPriorAtual!=NULL){
			enfileirar(&novaFila,comPriorAtual);
			comPriorAtual=comPriorAtual->prox;
		}
	}
	if(comPriorAtual==NULL){
		while(semPriorAtual!=NULL){
			enfileirar(&novaFila,semPriorAtual);
			semPriorAtual=semPriorAtual->prox;
		}
	}
	*resultado=novaFila;
	
}

int main() {
	
    srand(time(0)); // Gera uma seed aleatoria pro RNG
    
    Fila filaSemPrioridade;
    Fila filaComPrioridade;
    Caixa caixas[5];

    inicializaFila(&filaSemPrioridade);
    inicializaFila(&filaComPrioridade);
    inicializaCaixa(caixas);

   

    for(int i = 0; i < 5; i++)
    {
         No *pessoa = (No*)malloc(sizeof(No));
    if (pessoa == NULL) {
        perror("Falhou a alocação");
        return 1;
    }
        gerarPessoa(pessoa);
        cadastrar(&filaSemPrioridade,&filaComPrioridade,pessoa);

        
        
    }
    printf("=========================\n");
    printf("Fila com prioridade: \n");
    exibirFila(&filaComPrioridade);
    printf("=========================\n");
    printf("Fila sem prioridade: \n");
    exibirFila(&filaSemPrioridade);
    printf("=========================\n");
	
	
	int op=0;
	int prioridadeAtendidos=0, contAuxiliar = 0, contPrioridade = 0;
	do{
		printf("1-Cadastrar cliente na fila\n2-Exibir fila\n3-Chamar cliente para atendimento\n4-Exibir quantitativo de clientes atendidos por cada caixa\n5-Sair");
		scanf("%d",&op);
		switch(op){
			case 1:;
        char nome[30];
        char cpf[12];
        int idade,deficiente;
        printf("Insira o nome do cliente\n");
        gets(nome);
        printf("Insira o CPF do cliente\n");
        gets(cpf);
        printf("Insira a idade do cliente\n");
        scanf("%d",&idade);
        printf("Insira 1 se o cliente for deficiente, senão insira 0\n");
        scanf("%d",&deficiente);
        No *pessoa=criarNo(nome,cpf,idade,deficiente);
        cadastrar(&filaSemPrioridade,&filaComPrioridade,pessoa);
        break;
			case 2:;
        Fila novaFila;
        combinarFila(filaComPrioridade,filaSemPrioridade,prioridadeAtendidos,&novaFila);
        exibirFila(&novaFila);
        break;
			case 3:
        atendimentoCliente(&filaComPrioridade, &filaSemPrioridade, caixas, &contAuxiliar, &contPrioridade);
        break;
			case 4:
        break;
      case 5:
        finalizarExpediente(contAuxiliar, caixas);
        break;
      default:
        printf("Erro: Escolha uma opcao valida. Por gentileza\n");
		}
    system("pause");
	}
	while(op!=5);

    return 0;
}

