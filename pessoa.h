#ifndef PESSOA_H
#define PESSOA_H

#define TAMANHO_CPF 12
#define TAMANHOMAX_NOME 100
#define NUM_NOMES 10
#define NUM_SOBRENOMES 10
#define MIN_IDADE 18
#define MAX_IDADE 100

extern char *nomes[NUM_NOMES];
extern char *sobrenomes[NUM_SOBRENOMES];

typedef struct {
    char Nome[TAMANHOMAX_NOME];
    char CPF[TAMANHO_CPF];
    int Idade;
    int Deficiente;
} Pessoa;

int intAleatorio(int min, int max);
void gerarPessoa(Pessoa *pessoa);

#endif // PESSOA_H

