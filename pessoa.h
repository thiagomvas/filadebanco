#ifndef PESSOA_H
#define PESSOA_H

#define TAMANHO_CPF 12			// Numero de caracteres no CPF
#define TAMANHOMAX_NOME 100		// Tamanho max do nome
#define NUM_NOMES 10			// Numero de nomes na array de nomes aleatorios
#define NUM_SOBRENOMES 10		// Numero de sobrenomes na array de sobrenomes aleatorios
#define MIN_IDADE 18			// Idade minima na geração de pessoas
#define MAX_IDADE 100			// Idade máxima na geração de pessoas

extern char *nomes[NUM_NOMES]; 		// Array de nomes aleatorios
extern char *sobrenomes[NUM_SOBRENOMES];// Array de sobrenomes aleatorios

// Tipo de cada pessoa na fila
typedef struct No{ // especificação do nó da fila
char nome[30];
char cpf[12];
int idade;
int deficiente;
struct No* prox;
} No;

// Função de geração de ints aleatorios entre min e max(inclusivo)
int intAleatorio(int min, int max);

// Função de geração de pessoa com dados aleatorios
void gerarPessoa(No *pessoa);

// Função para exibir pessoa
void exibirPessoa(No *pessoa); 
#endif // PESSOA_H

No* criarPessoa(const char* nome, const char* cpf, int idade, int deficiente);