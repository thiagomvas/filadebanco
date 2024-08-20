#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"
#include "fila.h"
#include <time.h>


// Variáveis globais
int op = 0;
char nome[TAMANHOMAX_NOME];
char cpf[TAMANHO_CPF];
int caixa = 0;
int prefAtendidos = 0;
int totalPrioridade = 0, totalUsual = 0;

//Cadastra a pessoa na fila de acordo com a prioridade
void cadastar(Fila* filaSemPrioridade, Fila* filaComPrioridade, No* pessoa) {
	if (pessoa->idade >= 60 || pessoa->deficiente == 1) {//condição para ser prioridade
		enfileirar(filaComPrioridade, pessoa);
	}
	else {
		enfileirar(filaSemPrioridade, pessoa);
	}
}

// Limpa o console
void limparConsole()
{
#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#else
	system("clear");
#endif  
}

//Calcula o tempo de espera e mostra quem estar na frente
void exibirPrevisao(Fila* filaComPrioridade, Fila* filaSemPrioridade, char nome[TAMANHOMAX_NOME]) {
	No* tempPessoaComPrioridade = filaComPrioridade->inicio;
	No* tempPessoaSemPrioridade = filaSemPrioridade->inicio;
	int tempoDeEspera = 0;
	int posicaoNaFila = 1;
	int pessoasAtendidasComPrioridade = 0;
	int pessoasAtendidasSemPrioridade = 0;

	printf("Pessoas à frente:\n");

	// Percorrer como se fosse uma fila combinada
	while (tempPessoaComPrioridade != NULL || tempPessoaSemPrioridade != NULL) {
		if (pessoasAtendidasComPrioridade < 2 && tempPessoaComPrioridade != NULL) {
			// Exibir pessoa da fila com prioridade
			if (strcmp(tempPessoaComPrioridade->nome, nome) == 0) {
				printf("Tempo de espera estimado: %d minutos\n", tempoDeEspera);
				return;
			}
			printf("%d. %s (Prioridade)\n", posicaoNaFila, tempPessoaComPrioridade->nome);
			tempoDeEspera += 1;
			posicaoNaFila++;
			pessoasAtendidasComPrioridade++;
			tempPessoaComPrioridade = tempPessoaComPrioridade->prox;
		}
		else if (pessoasAtendidasSemPrioridade < 1 && tempPessoaSemPrioridade != NULL) {
			// Exibir pessoa da fila sem prioridade
			if (strcmp(tempPessoaSemPrioridade->nome, nome) == 0) {
				printf("Tempo de espera estimado: %d minutos\n", tempoDeEspera);
				return;
			}
			printf("%d. %s (Sem Prioridade)\n", posicaoNaFila, tempPessoaSemPrioridade->nome);
			tempoDeEspera += 1;
			posicaoNaFila++;
			pessoasAtendidasSemPrioridade++;
			tempPessoaSemPrioridade = tempPessoaSemPrioridade->prox;

			// Reiniciar contadores, pois quando alguem não preferencial for atendido, já deve atender alguem preferencial
			pessoasAtendidasComPrioridade = 0;
			pessoasAtendidasSemPrioridade = 0;

		}
		else {
			// Se não há mais pessoas na fila com prioridade, continue com a fila sem prioridade
			if (tempPessoaSemPrioridade != NULL) {
				if (strcmp(tempPessoaSemPrioridade->nome, nome) == 0) {
					printf("Tempo de espera estimado: %d minutos\n", tempoDeEspera);
					return;
				}
				printf("%d. %s (Sem Prioridade)\n", posicaoNaFila, tempPessoaSemPrioridade->nome);
				tempoDeEspera += 1;
				posicaoNaFila++;
				tempPessoaSemPrioridade = tempPessoaSemPrioridade->prox;
			}
		}
	}

	// Se o nome não foi encontrado
	printf("Pessoa com nome '%s' não encontrada na fila.\n", nome);
}

void atenderCliente(No *pessoa, Fila *filaComPrioridade, Fila *filaSemPrioridade,  int *caixas){
	limparConsole(); //Limpando a tela para exibição de dados.
	
	//Atende primeiramente os clientes que são prioridade na fila.
	if (prefAtendidos < 2 && filaComPrioridade->quant > 0){
		pessoa = sairDaFila(filaComPrioridade);
		prefAtendidos++;
		totalPrioridade++;
	}
	else if(filaSemPrioridade->quant > 0){//Atende uma pessoa com prioridade caso tenha e se duas pessoas prioridade forem atendidas
		pessoa = sairDaFila(filaSemPrioridade);
		prefAtendidos = 0;
		totalUsual++;
	}
	else if (filaComPrioridade->quant > 0) {  // Se não tiver ninguem na fila sem prioridade, atender prioridade
		pessoa = sairDaFila(filaComPrioridade);
		prefAtendidos++;
		totalPrioridade++;
	}
	else //Não há ninguem em ambas as filas;
		pessoa = NULL;
	
	
	if(pessoa != NULL){//Foi encontrado um cliente.
		printf("O caixa %d, está chamando!!!!\n", (caixa%5)+1);
		if (pessoa->deficiente || pessoa->idade >= 60){
			printf("'%s(prioridade)' está sendo atendido(a) no caixa %d\n", pessoa->nome, (caixa%5)+1);
		}
		else{
			printf("'%s' está sendo atendido(a) no caixa %d\n", pessoa->nome, (caixa%5)+1);
		}
		caixas[caixa % 5]++;
		free(pessoa);
		caixa++;
	}
	else{//Não foi encontrado o cliente.
		printf("Não há alguém na fila para ser chamado\n");
	}
}

//Mostra os resultados do trabalho dos caixas no dia.
void finalizaExpediente(int numeroCaixas, int *caixas){
	printf("Expediente concluido: \n");
	for (int i = 0; i < numeroCaixas; i++){
		printf("Caixa %d atendeu %d pessoas\n", i + 1, caixas[i]);
	}
	printf("Total de clientes com prioridade atendidos: %d.\n", totalPrioridade);
	printf("Total de clientes sem prioridade atendidos: %d.\n", totalUsual);
}

int main() {
	srand(time(0)); // Gera uma seed aleatoria pro RNG

	Fila filaSemPrioridade;
	Fila filaComPrioridade;

	inicializaFila(&filaSemPrioridade);
	inicializaFila(&filaComPrioridade);

	// Inicializa o no pessoa
	No* pessoa = NULL;


	int numCaixas = 5;

	int* caixas = (int*)malloc(sizeof(int) * numCaixas);

	for (int i = 0; i < numCaixas; i++)
		caixas[i] = 0;

	while (op != 6) {
		printf("=========================================\n");
		printf("1 - Adicionar pessoa na fila (MANUAL)\n");
		printf("2 - Adicionar pessoa na fila (AUTOMATICO)\n");
		printf("3 - Remover pessoa da fila\n");
		printf("4 - Exibir previsão\n");
		printf("5 - Exibir ambas filas separadas\n");
		printf("6 - Sair\n");
		scanf("%d", &op);

		// Limpar o buffer do teclado
		while (getchar() != '\n');

		switch (op) {
		case 1: // Cadastrar na fila (MANUAL)
			// Alocar memória para uma nova pessoa
			pessoa = (No*)malloc(sizeof(No));
			if (pessoa == NULL) {
				perror("Falhou a alocação");
				return 1;
			}

			// Pedir dados para o usuário
			printf("Digite o nome: ");
			fgets(pessoa->nome, TAMANHOMAX_NOME, stdin);
			pessoa->nome[strcspn(pessoa->nome, "\n")] = '\0'; // Remover o '\n' do final

			printf("Digite o CPF: ");
			fgets(pessoa->cpf, TAMANHO_CPF, stdin);
			pessoa->cpf[strcspn(pessoa->cpf, "\n")] = '\0'; // Remover o '\n' do final

			printf("Digite a idade: ");
			scanf("%d", &pessoa->idade);

			printf("Deficiente (1 - Sim, 0 - Não): ");
			scanf("%d", &pessoa->deficiente);

			// Limpar buffer do teclado
			while (getchar() != '\n');

			// Adicionar a pessoa na fila
			cadastar(&filaSemPrioridade, &filaComPrioridade, pessoa);
			limparConsole();

			break;

		case 2: // Cadastrar na fila (AUTOMATICO)
			// Alocar memória para uma nova pessoa
			pessoa = (No*)malloc(sizeof(No));
			if (pessoa == NULL) {
				perror("Falhou a alocação");
				return 1;
			}

			gerarPessoa(pessoa); // Gerar dados aleatorios
			cadastar(&filaSemPrioridade, &filaComPrioridade, pessoa);
			limparConsole();
			printf("Cadastrado:");
			exibirPessoa(pessoa);

			break;


		case 3: // Chamar cliente
			atenderCliente(pessoa, &filaComPrioridade, &filaSemPrioridade, caixas);
			break;


		case 4: // Mostrar o tempo de espera e as pessoas que estão na frente
			limparConsole();
			printf("Digite o seu nome completo:");
			fgets(nome, TAMANHOMAX_NOME, stdin);
			nome[strcspn(nome, "\n")] = '\0'; // Remover o '\n' do final

			exibirPrevisao(&filaComPrioridade, &filaSemPrioridade, nome);
			break;

		case 5: // Exibir ambas as filas
			limparConsole();
			printf("Fila com prioridade ==================\n");
			exibirFila(&filaComPrioridade);
			printf("Fila sem prioridade ==================\n");
			exibirFila(&filaSemPrioridade);
			printf("======================================\n");
			break;
		case 6: // Sair do sistema
			limparConsole();
			finalizaExpediente(numCaixas, caixas);
			// Liberar memoria utilizada
			destruirFila(&filaComPrioridade);
			destruirFila(&filaSemPrioridade);
			free(caixas);
			free(pessoa);
			return 0;
		default:
			limparConsole();
			printf("Opção inválida! Tente novamente.\n");
			break;
		}
	}


	return 0;
}
