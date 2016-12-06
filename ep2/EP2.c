#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EP2.h"

/*void imprimeMatriz(int **matriz, int tamanhoDaPrimeira, int tamanhoDaSegunda) {
	int i,j;
	
	for (i=0; i<=tamanhoDaPrimeira; i++) {
		for (j=0; j<=tamanhoDaSegunda; j++) {
			printf("%d", matriz[i][j]);
		}
		printf("\n");
	}
}*/

char *leMaiorSubsequenciaComum(int **matriz, char *primeiraPalavra, int tamanhoDaPrimeira, int tamanhoDaSegunda, int tamamanhoSubsequencia) {
	// Cria e aloca memoria para o vetor que armazenara a maior subsequencia comum
	char *LMC;
	LMC = malloc(tamamanhoSubsequencia+1 * sizeof(char));
	LMC[tamamanhoSubsequencia] = 0;
	// Cria variaveis necessarias
	int i = tamanhoDaPrimeira;
	int j = tamanhoDaSegunda;
	// Indice do vetor LMC que comeca sendo preechido pelo final
	int k = tamamanhoSubsequencia-1;
	
	// Varre a matriz comecando do final
	while ((i>0) && (j>0)) {
		// Se o termo da matriz for igual ao termo de cima, sobe para a linha de cima
		if (matriz[i][j] == matriz[i-1][j]) {
			i = i - 1;	
		} 
		else {
			// Se o termo da matriz for igual ao termo do lado esquerdo, vai pro lado esquerdo
			if (matriz[i][j] == matriz[i][j-1]) {
				j = j - 1;	
			} 
			// Se nao caiu nas condicoes anteriores, quer dizer que ele veio da diagonal somado de 1
			else {
				// Coloca o caracter no final do vetor LMC
				LMC[k] = primeiraPalavra[i-1];
				i = i - 1;
				j = j - 1;
				k--;
			}
		}
	}
	// Retorna a maior subsequencia comum
	return LMC;
}

int calculaMaior(int cima, int lado) {
	// Se o termo de cima for maior, retorna ele
	if (cima > lado) {
		return cima;
	}
	// Se nao, retorna o do lado
	else {
		return lado;
	}
}

int preecheMatriz(int **matriz, char *primeiraPalavra, char *segundaPalavra, int tamanhoDaPrimeira, int tamanhoDaSegunda) {
	// j = linha
	// i = coluna
	int i,j;
	
	for (i=1; i<=tamanhoDaSegunda; i++) {
		for (j=1; j<=tamanhoDaPrimeira; j++) {
			// Se os caracteres forem iguais, o termo da matriz sera a sua diagonal somado de 1
			if (primeiraPalavra[j-1] == segundaPalavra[i-1]) {
				matriz[j][i] = (matriz[j-1][i-1] +1);
			}
			// Se o caracter nao for igual, o termo da matriz sera o maior termo entre o termo de cima e o do lado esquerdo
			else {
				matriz[j][i] = calculaMaior(matriz[j-1][i], matriz[j][i-1]);
			}
		}
	}
	// Retorna o tamanho da maior subsequencia comum
	return matriz[tamanhoDaPrimeira][tamanhoDaSegunda];
}

int main(int argc, char **argv) {
	
	// Verifica se foi enviado os argumentos necessarios
	if (argv[1] == NULL || argv[2] == NULL) {
		printf("\n*Eh necessario passar dois argumentos na execucao do programa.*\n\n");
		exit(0);
	}
	// Verifica se foi enviado mais de dois argumentos
	if (argv[3] != NULL) {
		printf("\n*O programa so aceita dois argumentos.*\n\n");
		exit(0);
	}
	
	// Criacao de variaveis necessarias para o programa
	int **matriz;
	char *primeiraPalavra = argv[1];
	char *segundaPalavra = argv[2];
	int tamanhoSubsequencia;
	char *LMC;
	
	int tamanhoDaPrimeira = strlen(primeiraPalavra);
	int tamanhoDaSegunda = strlen(segundaPalavra);
	
	// Aloca memoria para a matriz
	int i,j;
	matriz = malloc((tamanhoDaPrimeira+1)* sizeof(int*));
	for (i=0; i<=tamanhoDaPrimeira; i++) {
		matriz[i] = malloc((tamanhoDaSegunda+1) * sizeof(int));
		for (j=0; j<=tamanhoDaSegunda; j++) {
			matriz[i][j] = 0;
		}
	}
	
	// Calcula o tamanho da maior subsequencia comum
	tamanhoSubsequencia = preecheMatriz(matriz, primeiraPalavra, segundaPalavra, tamanhoDaPrimeira, tamanhoDaSegunda);
	// Calcula a maior subsequencia comum
	LMC = leMaiorSubsequenciaComum(matriz, primeiraPalavra, tamanhoDaPrimeira, tamanhoDaSegunda, tamanhoSubsequencia);
	// Verifica se existe uma subsequencia comum
	if (tamanhoSubsequencia == 0) {
		printf("\n*Nao existe subsequencia comum entre as duas strings.*\n\n");
	}
	else {
		// Exibe na tela a maior subsequencia comum
		printf("\n%s\n\n", LMC);
	}
	// ------------------------------------------------------------
	// Desaloca memoria para a matriz
	for (i=0; i<=tamanhoDaPrimeira; i++) {
		free(matriz[i]);
	}
	free(matriz);
	// Desaloca memoria do vetor
	free(LMC);
}

