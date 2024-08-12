#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"

typedef struct Pessoa{ // especificação do nó da fila
char nome[30];
char cpf[12];
int idade;
int deficiente;
struct Pessoa* prox;} No;

typedef struct gerenciaFila{ // Nó cabeça
  No* inicio;
  No* fim;}fila;

//Cria nó do tipo de Cliente
No* criarNo(char nome[], char cpf[],int idade, int deficiente){
  No* novoCliente=(No*)malloc(sizeof(No));
  strcpy(novoCliente->nome,nome);
  strcpy(novoCliente->cpf,cpf);
  novoCliente->idade=idade;
  novoCliente->deficiente=deficiente;
  novoCliente->prox=NULL;
  return novoCliente;
}

void inicializaFila(fila* fila){
  fila->inicio=NULL;
  fila->fim=NULL;
}

void enfileirar(fila* fila, char nome[], char cpf[], int idade, int deficiente){
  No* novoCliente=criarNo(nome, cpf, idade, deficiente);
  if(novoCliente==NULL){
    printf("Falha na alocação\n");
    return;
  }
  if(fila->inicio==NULL){ //caso fila esteja vazia
    fila->inicio=novoCliente;
    fila->fim=novoCliente;
  }
  else{
    fila->fim->prox=novoCliente;// caso fila já tenha alguém
    fila->fim=novoCliente;
  }
}

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

