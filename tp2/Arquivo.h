#ifndef Arquivo_h
#define Arquivo_h
#include "Time.h"

// Recebe a string e o separador. 
// Diferente do strtok convencional, a função separa a string quando encontra o separador
// porem não ocorre problemas ao se deparar com dois separadores seguidos.
char *strtok_single (char * str, char const * delims);

//Le o numero de linhas que o arquivo possui e aloca memoria para o vetorOrdenadoNome
int leQuantidadeDeLinhas(char *caminhoDoArquivo, Time **times);

// Verifica se eh uma operacao de vitoria/empate ou consulta
void verificaOperacao(char *operacao, Time *timesOrdenadoNome, Time *timesOrdenadoPontuacao, int *numeroDeTimes, FILE *saida);

// Analisa os dados da linha quando a operacao eh vitoria ou empate
void analisaLinhaVitoriaOuEmpate(char *operacao, Time *timesOrdenadoNome, Time *timesOrdenadoPontuacao, int *numeroDeTimes);

// Analisa os dados da linha quando a operacao eh consulta
void analisaLinhaConsulta(Time *timesOrdenadoNome, Time *timesOrdenadoPontuacao, int *numeroDeTimes, FILE *saida);

// Faz validacoes do arquivo de entrada e le linha por linha para fazer as operacoes desejadas
void analisaArquivo(char *caminhoDoArquivo, Time *timesOrdenadoNome, Time *timesOrdenadoPontuacao, FILE *saida);

#endif
