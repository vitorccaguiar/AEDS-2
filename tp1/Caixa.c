#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Caixa.h"

void inicializaCaixas(Caixa *caixa) {
	int i = 0;
	// 1 caixa de cambio (1)
	caixa[i].numero = i+1;
	caixa[i].saqueIlimitado = 0;
	caixa[i].cambio = 1;
	caixa[i].ocupado = 0;
	caixa[i].leitor = 0;
	caixa[i].tempoSaidaMenor = 0;
	i++;

	// 3 caixas de atendimento (2 ate 4)
	for (; i < 4; i++) {
		caixa[i].numero = i+1;
		caixa[i].saqueIlimitado = 1;
		caixa[i].cambio = 0;
		caixa[i].ocupado = 0;
		caixa[i].leitor = 0;
		caixa[i].tempoSaidaMenor = 0;
	}

	// 15 caixas automaticos sem leitor (5 ate 19)
	for (; i < 19; i++) {
		caixa[i].numero = i+1;
		caixa[i].saqueIlimitado = 0;
		caixa[i].cambio = 0;
		caixa[i].ocupado = 0;
		caixa[i].leitor = 0;
		caixa[i].tempoSaidaMenor = 0;
	}

	// 10 caixas automaticos com leitor (20 ate 29)
	for (; i < 29; i++) {
		caixa[i].numero = i+1;
		caixa[i].saqueIlimitado = 0;
		caixa[i].cambio = 0;
		caixa[i].ocupado = 0;
		caixa[i].leitor = 1;
		caixa[i].tempoSaidaMenor = 0;
	}
}

int caixaAtendenteVazio(Caixa *caixa) {
	int i = 0;
	for(i=1; i<4; i++) {
		if (caixa[i].ocupado == 0) {
			return 1;
		}
	}
	return 0;
}

int caixaAutomaticoVazio(Caixa *caixa) {
	int i = 0;
	for(i=4; i<29; i++) {
		if (caixa[i].ocupado == 0) {
			return 1;
		}
	}
	return 0;
}

int caixaCambioVazio(Caixa *caixa) {
	if (caixa[0].ocupado == 0) {
			return 1;
	}
	return 0;
}

unsigned long int menorTempoSaidaAtendente(Caixa *caixa) {
	int i = 0;
	unsigned long int menor = caixa[1].tempoSaidaMenor;
	for (i=2;i<4;i++) {
		if (caixa[i].tempoSaidaMenor < menor) {
			menor = caixa[i].tempoSaidaMenor;
		}
	} 
	return menor;
}

unsigned long int menorTempoSaidaAutomatico(Caixa *caixa) {
	int i = 0;
	unsigned long int menor = caixa[4].tempoSaidaMenor;
	for (i=5;i<29;i++) {
		if (caixa[i].tempoSaidaMenor < menor) {
			menor = caixa[i].tempoSaidaMenor;
		}
	}
	return menor;
}

unsigned long int menorTempoSaidaAutomaticoProximo(Caixa *caixa, int indice) {
	int i = indice;
	unsigned long int menor = caixa[i].tempoSaidaMenor;
	for (;i<29;i++) {
		if (caixa[i].tempoSaidaMenor < menor) {
			menor = caixa[i].tempoSaidaMenor;
		}
	}
	return menor;
}

void inicializaTempoComCaixa(Cliente *cliente, Caixa *caixa, int i, Cliente *saida, int *posicao) {
	cliente->tempoFila = 0;
	cliente->tempoSaida = cliente->tempoChegada + cliente->tempoFila + cliente->tempoOperacao;
	caixa[i].tempoSaidaMenor = cliente->tempoSaida;
	
	
	// Coloca o cliente com todos os dados no vetor que sera usado para a saida
	saida[*posicao].id = cliente->id;
	strcpy(saida[*posicao].nome, cliente->nome);
	strcpy(saida[*posicao].operacao, cliente->operacao);
	saida[*posicao].quantidadeBRL = cliente->quantidadeBRL;
	saida[*posicao].quantidadeUSD = cliente->quantidadeUSD;
	saida[*posicao].tempoChegada = cliente->tempoChegada;
	saida[*posicao].tempoFila = cliente->tempoFila + cliente->tempoOperacao;
	saida[*posicao].tempoOperacao = cliente->tempoOperacao;
	saida[*posicao].tempoSaida = cliente->tempoSaida;
	*posicao = *posicao + 1;
}

void inicializaTempoSemCaixa(Cliente *cliente, Caixa *caixa, int i, Cliente *saida, int *posicao) {
	cliente->tempoFila = caixa[i].tempoSaidaMenor - cliente->tempoChegada;
	if (cliente->tempoFila < 0) {
		cliente->tempoFila = 0;
	}
	cliente->tempoSaida = cliente->tempoChegada + cliente->tempoFila + cliente->tempoOperacao;
	caixa[i].tempoSaidaMenor = cliente->tempoSaida;
	
	// Coloca o cliente com todos os dados no vetor que sera usado para a saida
	saida[*posicao].id = cliente->id;
	strcpy(saida[*posicao].nome, cliente->nome);
	strcpy(saida[*posicao].operacao, cliente->operacao);
	saida[*posicao].quantidadeBRL = cliente->quantidadeBRL;
	saida[*posicao].quantidadeUSD = cliente->quantidadeUSD;
	saida[*posicao].tempoChegada = cliente->tempoChegada;
	saida[*posicao].tempoFila = cliente->tempoFila + cliente->tempoOperacao;
	saida[*posicao].tempoOperacao = cliente->tempoOperacao;
	saida[*posicao].tempoSaida = cliente->tempoSaida;
	*posicao = *posicao + 1;
}

int caixaCambioDisponivel(Caixa *caixa) {
	return 0;
}

int caixaAtendenteDisponivel(Caixa *caixa) {
	unsigned long int menor = menorTempoSaidaAtendente(caixa);
	int i = 0;
	for(i=1;i<4;i++) {
		if (caixa[i].tempoSaidaMenor == menor) {
			return i;
		}
	}
	return 1;
}

int caixaAutomaticoDisponivel(Caixa *caixa) {
	unsigned long int menor = menorTempoSaidaAutomatico(caixa);
	int i = 0;
	for(i=4;i<29;i++) {
		if (caixa[i].tempoSaidaMenor == menor) {
			return i;
		} 
	}
	return 1;
}

int caixaAutomaticoDisponivelProximo(Caixa *caixa, int indice) {
	int i = indice;
	unsigned long int menor = menorTempoSaidaAutomaticoProximo(caixa, i);
	for(;i<29;i++) {
		if (caixa[i].tempoSaidaMenor == menor) {
			return i;
		}
	}
	return 1;
}

void liberaCaixa(Caixa *caixa, int i) {
	caixa[i].ocupado = 0;
}

void enviarParaOCaixa(Caixa *caixa, int i) {
	caixa[i].ocupado = 1;
}
