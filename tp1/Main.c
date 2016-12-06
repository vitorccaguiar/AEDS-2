#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fila.h"
#include "Caixa.h"
#include "Agencia.h"
#include "Arquivo.h"

int main(int argc, char **argv) {
	// Valida argumentos
	if (argc != 3) {
		printf("\n\tO numero de argumentos esta errado. O programa deve receber 2 argumentos.\n\n");
		exit(0);
	}
	// Cria os caixas necessarios
	Caixa *caixa = (Caixa*)malloc(29*sizeof(Caixa));
	inicializaCaixas(caixa);

	// Cria a agencia
	Agencia *agencia = (Agencia*)malloc(sizeof(Agencia));
	inicializaAgencia(agencia);

	// Cria os clientes e preeche os dados com relacao ao arquivo de entrada
	Cliente *cliente;
	int numeroDeLinhas;
	numeroDeLinhas = leQuantidadeDeLinhas(argv[1], &cliente);
	preecheDadosDoArquivo(argv[1], cliente);

	// Cria todas as filas necessarias
	TFila *filaAutomatico = malloc(sizeof(TFila));
	strcpy(filaAutomatico->nome, "automatico");
	inicializaFila(filaAutomatico);
	TFila *filaAtendente = malloc(sizeof(TFila));
	strcpy(filaAtendente->nome, "atendente");
	inicializaFila(filaAtendente);
	TFila *filaCambio = malloc(sizeof(TFila));
	strcpy(filaCambio->nome, "cambio");
	inicializaFila(filaCambio);

	// Enfileira todos os clientes para as suas respectivas filas
	int i;
	for (i=0; i< numeroDeLinhas; i++) {
		verificarOperacao(&cliente[i], filaAutomatico, filaAtendente, filaCambio);
	} 
	
	// Cria um vetor que tera todos os clientes com todas as informacoes para usar na saida
	Cliente *clientesSaida = (Cliente*)malloc(numeroDeLinhas*sizeof(Cliente));
 	for(i = 0; i < numeroDeLinhas; i++) {
 	    clientesSaida[i].id = 0;
 	    clientesSaida[i].tempoChegada = 0;
 	    strcpy(clientesSaida[i].nome, "");
 	    clientesSaida[i].quantidadeBRL =  0;
 	    clientesSaida[i].quantidadeUSD = 0;
 	    strcpy(clientesSaida[i].operacao, "");
 	    clientesSaida[i].tempoOperacao =  0;
 	    clientesSaida[i].tempoSaida = 0;
 	    clientesSaida[i].tempoFila = 0;
 	}

	int *posicaoVetorSaida = (int*) malloc(sizeof(int));
	*posicaoVetorSaida = 0;
	
	// Retira um a um cada cliente da sua fila inicializando os valores de tempo de saida e tempo de fila
	desenfileiraCambio(caixa, filaCambio, posicaoVetorSaida, clientesSaida);
	desenfileiraAtendente(caixa, filaAtendente, posicaoVetorSaida, clientesSaida);
	desenfileiraAutomatico(caixa, filaAutomatico, posicaoVetorSaida, clientesSaida);
	
	// Calcula o saldo da agencia e as variacoes devolvendo todas as informacoes necessarias no outro arquivo csv
	imprimeSaida(clientesSaida, argv[2], numeroDeLinhas, agencia);
	
	free(posicaoVetorSaida);
	free(agencia);
	free(caixa);
	free(cliente);
	free(clientesSaida);
	free(filaAutomatico);
	free(filaAtendente);
	free(filaCambio);
	return 0;
}
