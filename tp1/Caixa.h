#ifndef Caixa_h
#define Caixa_h
#include "Fila.h"

typedef struct {
	int numero;
	int saqueIlimitado;
	int cambio;
	int ocupado;
	int leitor;
	unsigned long int tempoSaidaMenor;
}Caixa;

// Recebe um vetor de caixas e coloca os valores necessarios para definir os caixas do programa (colocando 0 ou 1 para as suas flags).
void inicializaCaixas(Caixa *caixa);

// Recebe um vetor de caixas e verifica se existe um caixa de atendente disponivel.
int caixaAtendenteVazio(Caixa *caixa);

// Recebe um vetor de caixas e verifica se existe um caixa automatico disponivel.
int caixaAutomaticoVazio(Caixa *caixa);

// Recebe um vetor de caixas e verifica se existe um caixa de cambio disponivel.
int caixaCambioVazio(Caixa *caixa);

// Recebe um vetor de caixas e verifica o primeiro caixa de cambio que vai ser liberado e retorna o seu indice do vetor.
int caixaCambioDisponivel(Caixa *caixa);

// Recebe um vetor de caixas e verifica o primeiro caixa de atendente que vai ser liberado e retorna o seu indice do vetor.
int caixaAtendenteDisponivel(Caixa *caixa);

// Recebe um vetor de caixas e verifica o primeiro caixa automatico que vai ser liberado e retorna o seu indice do vetor.
int caixaAutomaticoDisponivel(Caixa *caixa);

// Recebe um vetor de caixas e um indice que diz a partir de qual posição do vetor sera analisado se possui algum caixa automatico disponivel.
// Se existir, retorna o indice desse caixa.
int caixaAutomaticoDisponivelProximo(Caixa *caixa, int i);

// Recebe um vetor de caixa e um indice.
// Coloca o valor 0 na flag 'ocupado' do caixa com o indice recebido.
void liberaCaixa(Caixa *caixa, int i);

// Recebe um vetor de caixa e um indice. 
// Coloca o valor 1 na flag 'ocupado' do caixa com o indice recebido.
void enviarParaOCaixa(Caixa *caixa, int i);

// Recebe um vetor de caixa. 
// Verifica qual eh o caixa que sera liberado primeiro e retorna o valor de saida dele.
unsigned long int menorTempoSaidaAtendente(Caixa *caixa);

// Recebe um vetor de caixa. 
// Verifica qual eh o caixa que sera liberado primeiro e retorna o valor de saida dele.
unsigned long int menorTempoSaidaAutomatico(Caixa *caixa);

// Recebe um vetor de caixa e um indice. 
// Verifica qual caixa sera liberado primeiro a partir desse indice e retorna o valor de saida dele.
unsigned long int menorTempoSaidaAutomaticoProximo(Caixa *caixa, int i);

// Recebe um cliente, o vetor de caixa, um indice, o vetor de cliente usado na saida, posicao de insercao desse cliente no vetor de saida. 
// Calcula os valores de tempo de saida e tempo de fila. 
// Neste caso o tempo de fila sera 0 devido ao estado inicial que tera caixa disponivel.
void inicializaTempoComCaixa(Cliente *cliente, Caixa *caixa, int i, Cliente *saida, int *posicao);

// Recebe um cliente, o vetor de caixa, um indice, o vetor de cliente usado na saida, posicao de insercao desse cliente no vetor de saida. 
// Calcula os valores de tempo de saida e tempo de fila.
void inicializaTempoSemCaixa(Cliente *cliente, Caixa *caixa, int i, Cliente *saida, int *posicao);

#endif


