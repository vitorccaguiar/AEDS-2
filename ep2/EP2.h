#ifndef EP2
#define EP2

// Funcao que imprime a matriz formada pelas operacoes realizadas para descobrir o tamanho da maior subsequencia comum
void imprimeMatriz(int **matriz, int tamanhoDaPrimeira, int tamanhoDaSegunda);

// Recebe a matriz preechida e faz outras operacoes para saber a maior subsequencia comum e retornar um vetor com essa informacao.
char *leMaiorSubsequenciaComum(int **matriz, char *primeiraPalavra, int tamanhoDaPrimeira, int tamanhoDaSegunda, int tamamanhoSubsequencia);

// Dado dois termos da matriz, retorna o maior entre eles
int calculaMaior(int cima, int lado);

// Recebe uma matriz inicializada com 0 e preeche ela com calculos realizados para descobrir o tamanho da maior subsequencia comum
int preecheMatriz(int **matriz, char *primeiraPalavra, char *segundaPalavra, int tamanhoDaPrimeira, int tamanhoDaSegunda);

#endif
