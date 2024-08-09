# Projeto Estrutura de Dados - Fila de Banco
## Integrates
1. Artur Freitas Oliveira Alves
2. Gabriela Safira Neves de Oliveira
3. Guilherme Inácio Santos Paes
4. Irwing Felipe Pereira Vieira
5. Thiago Menezes Vasconcelos

## Instalação
Usando o compilador preferido, compile ``main.c`` e ``pessoa.c`` em um arquivo só. Exemplo usando ``gcc``
```bash
gcc -o main.exe main.c pessoa.c
```

## Descrição
Imagine que você está desenvolvendo um sistema de controle de fila de banco.
Implementar um sistema que controle a fila do banco considerando que apesar de haver
5 caixas disponíveis há apenas uma fila. Considere que há pessoas deficientes, com 60
anos ou mais e outras que devem, por lei, ter prioridade no atendimento. Para que os
clientes que não são prioridade não fiquem indefinidamente sem atendimento, deve-se
especificar que após o atendimento de 2 clientes com prioridades, deve-se atender um
cliente que não seja prioridade. Caso não haja clientes com prioridade os não prioridade
são atendidos normalmente. Para cada cliente deve ser guardado nome, CPF e a
informação se o cliente é prioridade ou não. O sistema deve possuir as seguintes funcionalidades:

- Cadastrar cliente na fila (lembre que o cliente pode ter prioridade ou não)
- Exibir previsão de atendimento do cliente (exibir listagem da organização da fila)
- Chamar cliente para atendimento
- Exibir quantitativo de clientes atendidos por cada caixa

Obs: A funcionalidade de chamar cliente para atendimento deve ser feita da seguinte
forma. Cada vez que um caixa terminar de atender um cliente ele deve chamar o próximo
cliente da fila. No painel (monitor) o cliente será chamado pelo nome e será indicado a
que caixa ele deve e dirigir. Ao final do expediente, deve ser exibida a quantidade de
cientes atendidos por cada caixa durante o expediente.

