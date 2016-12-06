#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arquivo.h"

int main(int argc, char **argv) {
	// Verifica se o numero de argumentos passados na execucao do programa esta correta
	if (argc != 3) {
		printf("\n\tO numero de argumentos esta errado. O programa deve receber 2 argumentos.\n\n");
		exit(0);
	}

	// Cria, aloca e inicializa vetor de times que sera ordenado por nome
	Time *timesOrdenadoNome;
	int numeroDeLinhas;
	numeroDeLinhas = leQuantidadeDeLinhas(argv[1], &timesOrdenadoNome);

	// Cria, aloca e inicializa vetor de times que sera ordenado por pontuacao
	Time *timesOrdenadoPontuacao = (Time*)malloc((2*numeroDeLinhas)*sizeof(Time)+1);
  	int i;
  	for(i = 0; i < (2*numeroDeLinhas)-1; i++) {
    	strcpy(timesOrdenadoPontuacao[i].nome, "");
    	timesOrdenadoPontuacao[i].pontuacao =  0;
    }

    FILE *saida = fopen(argv[2], "w");
    if (saida == NULL) {
		printf("\nNao foi possivel abrir o arquivo.\n");
		exit(0);
	}
    // Faz validacoes do arquivo de entrada e le linha por linha para fazer as operacoes desejadas
	analisaArquivo(argv[1], timesOrdenadoNome, timesOrdenadoPontuacao, saida);

	free(timesOrdenadoNome);
	free(timesOrdenadoPontuacao);
	fclose(saida);
}