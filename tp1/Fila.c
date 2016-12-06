#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fila.h"

void inicializaFila(TFila *Fila) {
	Fila->Frente = (TCelula*)malloc(sizeof(TCelula));
 	Fila->Tras = Fila->Frente;
 	Fila->Frente->Prox = NULL;
}

int Vazia(TFila Fila) {
	return (Fila.Frente == Fila.Tras);
}

void Enfileira(Cliente cliente, TFila *Fila) {
	Fila->Tras->Prox = malloc(sizeof(TCelula));
 	Fila->Tras = Fila->Tras->Prox;
 	Fila->Tras->cliente = cliente;
 	Fila->Tras->Prox = NULL;
}

void Desenfileira(TFila *Fila, Cliente *cliente) {
	if (Vazia(*Fila)) {
 		printf("Erro: fila vazia\n");
 		return;
 	}
 	Apontador q = Fila->Frente->Prox;
 	if (q->Prox == NULL) {
 		free(Fila->Frente);
 		Fila->Frente = Fila->Tras;
 	}

 	Fila->Frente->Prox = q->Prox;
 	cliente->id = q->cliente.id;
 	cliente->tempoChegada = q->cliente.tempoChegada;
 	strcpy(cliente->nome, q->cliente.nome);
 	strcpy(cliente->operacao, q->cliente.operacao);
 	cliente->quantidadeBRL = q->cliente.quantidadeBRL;
 	cliente->quantidadeUSD = q->cliente.quantidadeUSD;
 	cliente->tempoOperacao = q->cliente.tempoOperacao;
 	cliente->tempoSaida = q->cliente.tempoSaida;
 	cliente->tempoFila = q->cliente.tempoFila;
 	free(q);
}
