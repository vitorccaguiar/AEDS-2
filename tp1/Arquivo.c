#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Arquivo.h"

char *strtok_single (char * str, char const * delims) {
	static char  *src = NULL;
 	char  *p,  *ret = 0;

 	if (str != NULL) {
		src = str;
 	}

 	if (src == NULL) {
   		return NULL;
   	}

 	if ((p = strpbrk (src, delims)) != NULL) {
   		*p  = 0;
   		ret = src;
   		src = ++p;
 	}
 	else if (*src) {
   		ret = src;
   		src = NULL;
 	}

 	return ret;
}

int leQuantidadeDeLinhas(char *caminhoDoArquivo, Cliente **cliente) {
	int numeroDeLinhas = 0;
	int existeLinhas = 0;
	char caractere;
	FILE *arq = fopen(caminhoDoArquivo, "r");
	if (arq == NULL) {
		printf("\nNao foi possivel abrir o arquivo.\n");
	}
	else {
		while((caractere = fgetc(arq)) != EOF){
    		existeLinhas = 1; // ha conteudo no arquivo

    		if(caractere == '\n'){ // se tem quebra de linha
      			numeroDeLinhas++;
    		}
  		}
  		// se nao houver uma quebra de linha na ultima linha
 	 	// a contagem sera sempre um a menos. Assim, eh melhor
  		// incrementar quant_linhas mais uma vez
  		if (existeLinhas) {
  			numeroDeLinhas++;
  		}
  		*cliente = (Cliente*)malloc(numeroDeLinhas*sizeof(Cliente));
  		int i;
  		for(i = 0; i < numeroDeLinhas; i++) {
     	    (*cliente)[i].id = 0;
     	    (*cliente)[i].tempoChegada = 0;
     	    strcpy((*cliente)[i].nome, "");
     	    (*cliente)[i].quantidadeBRL =  0;
     	    (*cliente)[i].quantidadeUSD = 0;
     	    strcpy((*cliente)[i].operacao, "");
     	    (*cliente)[i].tempoOperacao =  0;
     	    (*cliente)[i].tempoSaida = 0;
     	    (*cliente)[i].tempoFila = 0;
    	}
  	}
  	fclose(arq);
  	return numeroDeLinhas;
}

void preecheDadosDoArquivo(char *caminhoDoArquivo, Cliente *cliente) {
	char linha[350];
	char *nomeTeste;
  	char *operacaoTeste;

	FILE *arq = fopen(caminhoDoArquivo, "r");
	if (arq == NULL) {
		printf("\nNao foi possivel abrir o arquivo.\n");
	}
	else {
		char c;
		int contadorArgumentos = 0;
		while ((c = fgetc(arq)) != EOF) {
			if(c == '\n') {
				if (contadorArgumentos != 5) {
					printf("\n\tNumero de informacoes em uma linha esta incorreto.\n\n");
					exit(0);
				}
				contadorArgumentos = 0;
			}
			else {
				if(c == ',') {
					contadorArgumentos++;
				}
			}
		}
		fseek(arq, 0, SEEK_SET);
		int i = 0;
		// Pega linha por linha no arquivo
  		while (fgets(linha, sizeof(linha), arq) != NULL) {
  			if (strlen(linha) > 300) {
  				printf("\n\tNumero de caracteres na linha invalido. Maximo eh 300.\n\n");
  				exit(0);
  			}
  			cliente[i].id = i+1;
  			// 1 split vai pro tempoChegada
  			cliente[i].tempoChegada = atoi(strtok_single(linha, ","));
  			// 2 split vai pro nome
  			nomeTeste = strtok_single(NULL, ",");
  			if (strlen(nomeTeste) > 100 || strlen(nomeTeste) == 0) {
  				printf("\n\tNumero de caracteres no campo nome invalido. Maximo eh 100 e nao pode estar vazio.\n\n");
  				exit(0);
  			}
  			strncpy(cliente[i].nome, nomeTeste, 100);
  			// 3 split vai pra operacao
  			operacaoTeste = strtok_single(NULL, ",");
  			if (!strcmp(operacaoTeste, "SAQUE")==0 && !strcmp(operacaoTeste, "DEPOSITO")==0 && !strcmp(operacaoTeste, "CAIXA")==0 && !strcmp(operacaoTeste, "CÂMBIO")==0) {
				printf("\n\tAlguma operacao de um cliente no arquivo esta invalida.\n\n");
  				exit(0);
			}
  			strncpy(cliente[i].operacao,operacaoTeste, 10);
  			// 4 split vai pra quantidadeBRL
  			cliente[i].quantidadeBRL = atof(strtok_single(NULL, ","));
  			// 5 split vai pra quantidadeUSD
  			cliente[i].quantidadeUSD = atof(strtok_single(NULL, ","));
  			// 6 split vai pro tempoOperacao
  			cliente[i].tempoOperacao = atoi(strtok_single(NULL, ","));
  			cliente[i].tempoSaida = 0;
  			cliente[i].tempoFila = 0;
  			i++;
  		}
	}
	fclose(arq);
}

void imprimeSaida(Cliente *cliente, char *caminhoDoArquivo, int numeroDeLinhas, Agencia *agencia) {
	float menorBRL = 0;
	float maiorBRL = 0;
	float menorUSD = 0;
	float maiorUSD = 0;
	int menorTempo = 0;
	int maiorTempo = 0;
	menorTempo = cliente[0].tempoFila;
	
	FILE *arq = fopen(caminhoDoArquivo, "w");
	if (arq == NULL) {
		printf("\nNao foi possivel abrir o arquivo.\n");
	}
	else {
		int j=0;
		// Pega o primeiro cliente que saiu da agencia (menor tempo de saida)
		while (j != numeroDeLinhas) {
			int i, indice;
			unsigned long int menor = cliente[0].tempoSaida;
			for (i=1; i<numeroDeLinhas; i++) {
				// Se o tempo de saida eh menor e ele nao foi escrito na saida ainda
				if (cliente[i].tempoSaida < menor) {
					menor = cliente[i].tempoSaida;
				}
			}
			for (i=0; i<numeroDeLinhas; i++) {
				if (cliente[i].tempoSaida == menor ) {
					// Informa que esse cliente ja foi escrito na saida
					indice = i;
					break;
				}
			}
			
			// Faz a operacao proposta pelo cliente
			if (strcmp(cliente[indice].operacao, "SAQUE") == 0) {
				fazerOperacaoSaque(&cliente[indice], agencia);
			}
		
			if (strcmp(cliente[indice].operacao, "DEPOSITO") == 0) {
				fazerOperacaoDeposito(&cliente[indice], agencia);
			}
		
			if (strcmp(cliente[indice].operacao, "CAIXA") == 0) {
				if (cliente[indice].quantidadeBRL < 0) {
					fazerOperacaoSaque(&cliente[indice], agencia);
				}
				else {
					fazerOperacaoDeposito(&cliente[indice], agencia);
				}
			}
		
			if (strcmp(cliente[indice].operacao, "CÂMBIO") == 0) {
				fazerOperacaoCambio(&cliente[indice], agencia);
			}
			
			// Verifica os valores de maior e menor de BRL, USD e tempo
			if (agencia->saldoBRL < menorBRL) {
				menorBRL = agencia->saldoBRL;
			}
			if (agencia->saldoBRL > maiorBRL) {
				maiorBRL = agencia->saldoBRL;
			}
			if (agencia->saldoUSD < menorUSD) {
				menorUSD = agencia->saldoUSD;
			}
			if (agencia->saldoUSD > maiorUSD) {
				maiorUSD = agencia->saldoUSD;
			}
			if (cliente[indice].tempoFila < menorTempo) {
				menorTempo = cliente[indice].tempoFila;
			}
			if (cliente[indice].tempoFila > maiorTempo) {
				maiorTempo = cliente[indice].tempoFila;
			}
		
			char linha[100];
			sprintf(linha,"%lu,%s,%s,%.2f,%.2f,%d", cliente[indice].tempoSaida, cliente[indice].nome, cliente[indice].operacao,
			agencia->saldoBRL, agencia->saldoUSD, cliente[indice].tempoFila);
			fprintf(arq, "%s\n", linha);
			cliente[i].tempoSaida = ULONG_MAX;
			j++; 
		}
		// Escreve no arquivo de saida as variacoes
		fprintf(arq, "VARIACAO DE BRL: %.2f a %.2f\n", menorBRL, maiorBRL);
		fprintf(arq, "VARIACAO DE USD: %.2f a %.2f\n", menorUSD, maiorUSD);
		fprintf(arq, "VARIACAO DE TEMPO: %d a %d\n", menorTempo, maiorTempo);
		fclose(arq);
	}
}
