#ifndef Fila_h
#define Fila_h

typedef struct {
	int id;
	unsigned long int tempoChegada;
	char nome[100];
	char operacao[10];
	float quantidadeBRL;
	float quantidadeUSD;
	int tempoOperacao;
	unsigned long int tempoSaida;
	int tempoFila;
}Cliente;

typedef struct Celula *Apontador;

typedef struct Celula {
	Cliente cliente;
	Apontador Prox;
}TCelula;

typedef struct {
	char nome[20];
	Apontador Frente;
	Apontador Tras;
}TFila;

// Recebe uma fila por parâmetro. 
// Cria uma celula e faz os apontadores da fila apontarem pra essa célula (mesmo lugar) e o Prox dessa celula pra NULL.
void inicializaFila(TFila *Fila);

// Recebe uma fila e verifica se os apontadores Frente e Tras estao apontando pro mesmo lugar.
int Vazia(TFila Fila);

// Recebe uma fila e um cliente, cria uma nova celula e coloca a informacao do cliente nela (coloca um cliente na fila).
void Enfileira(Cliente cliente, TFila *Fila);

// Recebe uma fila e uma referencia de um cliente.
// Retira um cliente da fila e passa a informacao desse cliente por referencia no cliente recebido por parametro.
void Desenfileira(TFila *Fila, Cliente *cliente);

#endif
