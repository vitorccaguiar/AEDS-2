#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
* Nome: Vitor Claudio Chaves de Aguiar
* Curso: Sistema de Informacao
*
* Observacao: A matriz eh formada de cima para baixo
*/

void imprimirMatriz(int matriz[50][50], int tamanhoDaPrimeira, int tamanhoDaSegunda) {
	int i,j;
	printf("\n");
	for (i = 0; i<=tamanhoDaSegunda; i++) {
		printf("\t");
		for (j=0; j<=tamanhoDaPrimeira; j++) {
			// Se for o ultimo termo (distancia de edicao), imprime diferente
			if (i == tamanhoDaSegunda && j == tamanhoDaPrimeira) {
				printf("*%d*", matriz[i][j]);
			}
			else {
				// Se for um termo menor ou igual a 9, imprime com mais espaço
				if(matriz[i][j] <=9) {
					printf("%d%s", matriz[i][j], "  ");	
				}
				else {
					printf("%d%s", matriz[i][j], " ");	
				}
			}
		}
		printf("\n");
	}	
}

void preecheMatriz(int matriz[50][50], int tamanhoDaPrimeira, int tamanhoDaSegunda) {
	int i;

	// Coloca os numeros na linha
	for (i = 0; i<=(tamanhoDaPrimeira); i++) {
		matriz[0][i] = i;
	}

	// Coloca os numeros na coluna
	for (i = 1; i<=(tamanhoDaSegunda); i++) {
		matriz[i][0] = i;
	}
}

int calculaMenor(int cima, int lado, int diagonal, int valor) {
	int menor = 0;

	// Verifica se o valor de cima somado ao seu peso é o menor valor
	if ((cima + 1) <= (lado + 1) && (cima + 1) <= (diagonal + valor)) {
		menor = cima + 1;
	}

	// Verifica se o valor do lado esquerdo somado ao seu peso é o menor valor
	if ((lado + 1) <= (cima + 1) && (lado + 1) <= (diagonal + valor)) {
		menor = lado + 1;
	}

	// Verifica se o valor da diagonal superior esquerda somado ao seu peso é o menor valor
	if ((diagonal + valor) <= (lado + 1) && (diagonal + valor) <= (cima + 1)) {
		menor = diagonal + valor;
	}

	return menor;
}

int calculaDistancia(int matriz[50][50], char primeiraPalavra[], char segundaPalavra[], int tamanhoDaPrimeira, int tamanhoDaSegunda) {
	// i = linha
	// j = coluna
	int i,j,termo,valor;
	for (j=1; j<=tamanhoDaPrimeira; j++) {
		for (i=1; i<=tamanhoDaSegunda; i++) {
			// Verifica se uma letra eh igual a outra para decidir o custo da operacao de substituicao
			if (primeiraPalavra[j-1] != segundaPalavra[i-1]) {
				valor = 2;
			}
			else {
				valor = 0;
			}
			// Atribui ao termo o valor de menor dentre os tres avaliados
			termo = calculaMenor(matriz[i-1][j], matriz[i][j-1], matriz[i-1][j-1], valor);
			// Preeche o termo calculado na determinada posição da matriz
			matriz[i][j] = termo;
		}	
	}
	// Retorna o último termo da matriz que será a distância de edição
	return matriz[tamanhoDaSegunda][tamanhoDaPrimeira];
}

void menu(char *primeiraPalavra, char *segundaPalavra, int *tamanhoDaPrimeira, int *tamanhoDaSegunda) {
	// Cria variaveis para testar as entradas do usuario
	char primeiraPalavraTeste[101];
	char segundaPalavraTeste[101];
	int tamanhoDaPrimeiraTeste, tamanhoDaSegundaTeste;
	int i;

	// Fica em um loop infinito ate safisfazer as condicoes necessarias
	while (1) {
		int possuiSimbolo = 0;
		printf("\n\t\t\t%s", "EP1");
		printf("\n\t%s", "Digite a primeira palavra: ");
		// Le uma palavra de ate 100 caracteres
		scanf("%100s", primeiraPalavraTeste);
		tamanhoDaPrimeiraTeste = strlen(primeiraPalavraTeste);	

		// Verifica se a primeira palavra tem o tamanho adequado
		if (tamanhoDaPrimeiraTeste > 50) {
			printf("\n\t*A palavra digitada eh muito grande, repita o processo por favor.*\n");
			// Vai para a proxima interecao sem permitir que digite a segunda palavra
			continue;
		}
		// Verifica se tem algum caracter sem ser letra
		for (i=0; i<tamanhoDaPrimeiraTeste; i++) {
			if (!isalpha(primeiraPalavraTeste[i])) {
				possuiSimbolo = 1;
				printf("\n\t*A palavra digitada tem simbolos, repita o processo por favor.*\n");
			}
		} 
		// Se tiver algum simbolo ou numero, repete o processo
		if (possuiSimbolo == 1) {
			continue;
		}
		//----------------------------------------------------------------------------------------

		printf("\n\t%s", "Digite a segunda palavra: ");
		// Le uma palavra de ate 100 caracteres
		scanf("%100s", segundaPalavraTeste);
		tamanhoDaSegundaTeste = strlen(segundaPalavraTeste);

		// Verifica se a segunda palavra tem o tamanho adequado
		if (tamanhoDaSegundaTeste > 50) {
			printf("\n\t*A palavra digitada eh muito grande, repita o processo por favor.*\n");
			// Vai para proxima interecao
			continue;
		}
		// Verifica se tem algum caracter sem ser letra
		for (i=0; i<tamanhoDaSegundaTeste; i++) {
			if (!isalpha(segundaPalavraTeste[i])) {
				possuiSimbolo = 1;
				printf("\n\t*A palavra digitada tem simbolos, repita o processo por favor.*\n");
			}
		}
		// Se tiver algum simbolo ou numero, repete o processo
		if (possuiSimbolo == 1) {
			continue;
		}
		
		// Se as duas palavras possuem o tamanho correto, o valor das palavras de teste são atribuidas nas variaveis originais
		if (tamanhoDaPrimeiraTeste <= 50 && tamanhoDaSegundaTeste <= 50 && possuiSimbolo == 0) {
			strcpy(primeiraPalavra, primeiraPalavraTeste);
			strcpy(segundaPalavra, segundaPalavraTeste);
			*tamanhoDaPrimeira = tamanhoDaPrimeiraTeste;
			*tamanhoDaSegunda = tamanhoDaSegundaTeste;
			// Sai do loop
			return;
		}
	}
}

int main() {
	// Declaração de algumas variaveis que serão usadas no programa
	int matriz[50][50];
	char primeiraPalavra[51];
	char segundaPalavra[51];
	int tamanhoDaPrimeira, tamanhoDaSegunda;
	int distanciaDeEdicao;

	// Recebe os dados das palavras pelo usuário e faz a validacao quanto ao seu tamanho
	menu(primeiraPalavra, segundaPalavra, &tamanhoDaPrimeira, &tamanhoDaSegunda);

	// Preeche matriz com os valores iniciais
	preecheMatriz(matriz, tamanhoDaPrimeira, tamanhoDaSegunda);
	// Preeche a matriz efetuando os calculos
	distanciaDeEdicao = calculaDistancia(matriz, primeiraPalavra, segundaPalavra, tamanhoDaPrimeira, tamanhoDaSegunda);
	// Imprime matriz finalizada
	imprimirMatriz(matriz, tamanhoDaPrimeira, tamanhoDaSegunda);
	// Imprime distancia de edicao
	printf("\n\n\t%s%d\n\n", "A distancia de edicao sera: ", distanciaDeEdicao);
}
