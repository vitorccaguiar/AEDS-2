#ifndef Agencia_h
#define Agencia_h
#include "Fila.h"
#include "Caixa.h"

typedef struct {
	float saldoBRL;
	float saldoUSD;
}Agencia;

// Recebe agencia. Coloca os valores iniciais ( = 0 ) para os atributos da agencia. 
void inicializaAgencia(Agencia *agencia);

// Recebe um cliente e a agencia. Soma no saldo BRL da agencia o valor da operacao do cliente.
void fazerOperacaoSaque(Cliente *cliente, Agencia *agencia);

// Recebe um cliente e a agencia. Soma no saldo BRL da agencia o valor da operacao do cliente.
void fazerOperacaoDeposito(Cliente *cliente, Agencia *agencia);

// Recebe um cliente e a agencia. Soma no saldo BRL da agencia e no de USD o valor da operacao do cliente.
void fazerOperacaoCambio(Cliente *cliente, Agencia *agencia);

// Recebe um cliente e as filas dos caixas. Verifica qual opera��o o cliente fara e enfileira na fila correta.
void verificarOperacao(Cliente *cliente, TFila *filaAutomatico, TFila *filaAtendente, TFila *filaCambio);

// Recebe um vetor de caixa, a fila de cambio, a posicao do vetor de saida e o vetor de saida. 
// Pega todos os clientes que est�o enfileirados e inicializam os tempos de fila.
void desenfileiraCambio(Caixa *caixa, TFila *filaCambio, int *posicaoVetorSaida, Cliente *clientesSaida);

// Recebe um vetor de caixa, a fila de atendente, a posi��o do vetor de saida e o vetor de saida. 
// Pega todos os clientes que est�o enfileirados e inicializam os tempos de fila.
void desenfileiraAtendente(Caixa *caixa, TFila *filaAtendente, int *posicaoVetorSaida, Cliente *clientesSaida);

// Recebe um vetor de caixa, a fila automatico, a posi��o do vetor de saida e o vetor de saida. 
// Pega todos os clientes que estao enfileirados, envia para um caixa (se n�o tiver dispon�vel, libera um) e inicializam os tempos de fila. 
// Se tiver os dois tipos de caixa autom�tico, da prioridade ao sem leitor biom�trico se a opera��o permitir. 
// Se liberar sem leitor biom�trico e o primeiro da fila n�o puder realizar a opera��o, acha a primeira pessoa na fila que pode e passa na frente.
void desenfileiraAutomatico(Caixa *caixa, TFila *filaAutomatico, int *posicaoVetorSaida, Cliente *clientesSaida);

#endif
