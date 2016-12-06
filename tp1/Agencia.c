#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Agencia.h"

void inicializaAgencia(Agencia *agencia) {
	agencia->saldoBRL = 0.00;
	agencia->saldoUSD = 0.00;
}

void fazerOperacaoSaque(Cliente *cliente, Agencia *agencia) {
	agencia->saldoBRL += cliente->quantidadeBRL;
}

void fazerOperacaoDeposito(Cliente *cliente, Agencia *agencia) {
	agencia->saldoBRL += cliente->quantidadeBRL;
}

void fazerOperacaoCambio(Cliente *cliente, Agencia *agencia) {
	agencia->saldoUSD += cliente->quantidadeUSD;
	agencia->saldoBRL += cliente->quantidadeBRL;
}

void verificarOperacao(Cliente *cliente, TFila *filaAutomatico, TFila *filaAtendente, TFila *filaCambio) {
	// Se a operacao for saque, enfileira na fila automatico
	if (strcmp(cliente->operacao, "SAQUE") == 0) {
		if (cliente->quantidadeBRL > 0) {
			printf("\n\tOperacao de saque soh pode ser feita com valores negativos.\n\n");
			exit(0);
		}
		Enfileira(*cliente, filaAutomatico);
	}
	// Se a operacao for deposito, enfileira na fila automatico
	if (strcmp(cliente->operacao, "DEPOSITO") == 0) {
		if (cliente->quantidadeBRL < 0) {
			printf("\n\tOperacao de deposito soh pode ser feita com valores positivos.\n\n");
			exit(0);
		}
		Enfileira(*cliente, filaAutomatico);
	}
	// Se a operacao for cambio, enfileira na fila cambio
	if (strcmp(cliente->operacao, "CÂMBIO") == 0) {
		Enfileira(*cliente, filaCambio);
	}
	// Se a operacao for caixa, enfileira na fila atendente
	if (strcmp(cliente->operacao, "CAIXA") == 0) {
		Enfileira(*cliente, filaAtendente);
	}
}

void desenfileiraCambio(Caixa *caixa, TFila *filaCambio, int *posicaoVetorSaida, Cliente *clientesSaida) {
	Cliente *clienteProximo = (Cliente*) malloc(sizeof(Cliente));
	while (!Vazia(*filaCambio)) {
		// Ao desenfileirar, uma copia do cliente vai para clienteProximo
		Desenfileira(filaCambio, clienteProximo);
		// Se tiver algum caixa de cambio disponivel
		if (caixaCambioVazio(caixa)) {
			// Recebe o indice de um caixa disponivel
			int i = caixaCambioDisponivel(caixa);
			enviarParaOCaixa(caixa, i);
			// Calcula os valores de tempo
			inicializaTempoComCaixa(clienteProximo, caixa, i, clientesSaida, posicaoVetorSaida);
		}
		else {
			// Recebe o indice de um caixa disponivel
			int i = caixaCambioDisponivel(caixa);
			liberaCaixa(caixa, i);
			enviarParaOCaixa(caixa, i);
			// Calcula os valores de tempo
			inicializaTempoSemCaixa(clienteProximo, caixa, i, clientesSaida, posicaoVetorSaida);
		}
	} 
	free(clienteProximo);
}

void desenfileiraAtendente(Caixa *caixa, TFila *filaAtendente, int *posicaoVetorSaida, Cliente *clientesSaida) {
	Cliente *clienteProximo = (Cliente*) malloc(sizeof(Cliente));
	while (!Vazia(*filaAtendente)) {
		// Ao desenfileirar, uma copia do cliente vai para clienteProximo
		Desenfileira(filaAtendente, clienteProximo);
		// Se tiver algum caixa com atendente disponivel
		if (caixaAtendenteVazio(caixa)) {
			// Recebe o indice de um caixa disponivel
			int i = caixaAtendenteDisponivel(caixa);
			enviarParaOCaixa(caixa, i);
			// Calcula os valores de tempo 
			inicializaTempoComCaixa(clienteProximo, caixa, i, clientesSaida, posicaoVetorSaida);
		}
		else {
			// Recebe o indice de um caixa disponivel
			int i = caixaAtendenteDisponivel(caixa);
			liberaCaixa(caixa, i);
			enviarParaOCaixa(caixa, i);
			// Calcula os valores de tempo
			inicializaTempoSemCaixa(clienteProximo, caixa, i, clientesSaida, posicaoVetorSaida);
		}
	} 
	free(clienteProximo);
}

void desenfileiraAutomatico(Caixa *caixa, TFila *filaAutomatico, int *posicaoVetorSaida, Cliente *clientesSaida) {
	Cliente *clienteProximo = (Cliente*) malloc(sizeof(Cliente));
	while (!Vazia(*filaAutomatico)) {
		// Ao desenfileirar, uma copia do cliente vai para clienteProximo
		Desenfileira(filaAutomatico, clienteProximo);
		// Se tiver algum caixa automatico disponivel
		if (caixaAutomaticoVazio(caixa)) {
			// Recebe o indice de um caixa disponivel
			int i = caixaAutomaticoDisponivel(caixa);
			// Verifica se a operacao do cliente pode ser feita em qualquer tipo de caixa automatico
			if (fabs(clienteProximo->quantidadeBRL) <= 300) {
				enviarParaOCaixa(caixa, i);
			}
			// Se a operacao deve ser feita em um caixa com leitor biometrico
			else {
				int achouCaixa = 0;
				// Procura um caixa que pode ser feita a operacao
				while(achouCaixa == 0) {
					if(i >= 19 && i <= 28) {
						enviarParaOCaixa(caixa, i);
						achouCaixa = 1;
					}
					else {
						int j = i+1;
						i = caixaAutomaticoDisponivelProximo(caixa, j);
					}
				}
			} 
			// Calcula os valores de tempo
			inicializaTempoSemCaixa(clienteProximo, caixa, i, clientesSaida, posicaoVetorSaida);
		} 
		// Se nao tiver caixa disponivel
		else {
			// Procura primeiro caixa que vai ficar disponivel
			int indice = caixaAutomaticoDisponivel(caixa);
			liberaCaixa(caixa, indice);
			// Se o caixa que liberou foi sem leitor
			if (indice >=4 && indice <=18) {
				int achouCliente = 0;
				// Cria uma fila auxiliar
				TFila *filaAuxiliar = malloc(sizeof(TFila));
				strcpy(filaAuxiliar->nome, "auxiliar");
				inicializaFila(filaAuxiliar);
				// Procura um cliente que possa fazer a operacao no caixa sem leitor liberado
				while (!Vazia(*filaAutomatico) && achouCliente == 0) {
					// Se achou o cliente para fazer a operacao
					if (fabs(clienteProximo->quantidadeBRL) <= 300) {
						int indice2 = caixaAutomaticoDisponivel(caixa);
						enviarParaOCaixa(caixa, indice2);
						inicializaTempoSemCaixa(clienteProximo, caixa, indice2, clientesSaida, posicaoVetorSaida);
						achouCliente = 1;
					}
					// Se o cliente nao puder fazer a operacao, coloca na fila auxiliar
					else {
						Enfileira(*clienteProximo, filaAuxiliar);
						Desenfileira(filaAutomatico,clienteProximo);
					}
				}
				// Verifica o o ultimo desenfileirado
				if (Vazia(*filaAutomatico) && fabs(clienteProximo->quantidadeBRL) <= 300) {
					int indice3 = caixaAutomaticoDisponivel(caixa); 
					enviarParaOCaixa(caixa, indice3);
					inicializaTempoSemCaixa(clienteProximo, caixa, indice3, clientesSaida, posicaoVetorSaida);
				}	
				else {
					Enfileira(*clienteProximo, filaAuxiliar);
				}		
				
				Cliente *proximo = (Cliente*)malloc(sizeof(Cliente));
				// Volta os clientes da fila auxiliar para a fila automatico
				while (!Vazia(*filaAuxiliar)) {
					Desenfileira(filaAuxiliar, proximo);
					Enfileira(*proximo, filaAutomatico);
				}
				free(filaAuxiliar);
				if (clienteProximo->tempoChegada != proximo->tempoChegada) {
					free(proximo);
				}
			}
			// Se liberou caixa com leitor biometrico
			else {
				int i = caixaAutomaticoDisponivel(caixa);
				enviarParaOCaixa(caixa, i);
				inicializaTempoSemCaixa(clienteProximo, caixa, i, clientesSaida, posicaoVetorSaida);
			} 
		}
	}
	free(clienteProximo);
}
