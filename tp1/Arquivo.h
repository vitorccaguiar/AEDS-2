#ifndef Arquivo_h
#define Arquivo_h
#include "Fila.h"
#include "Agencia.h"

// Recebe a string e o separador. 
// Diferente do strtok convencional, a função separa a string quando encontra o separador
// porem não ocorre problemas ao se deparar com dois separadores seguidos.
char *strtok_single (char * str, char const * delims);

// Recebe o caminho do arquivo e um vetor de cliente. 
// Abre o arquivo para ler e contar quantas linhas ele possui com a finalidade de alocar memoria para o vetor de clientes.
// Faz todas as validacoes do arquivo de entrada
int leQuantidadeDeLinhas(char *caminhoDoArquivo, Cliente **cliente);

// Recebe o caminho do arquivo e um cliente. 
// Abre o arquivo para ler cada linha e separar cada informacao para armazenar nas estruturas corretas.
void preecheDadosDoArquivo(char *caminhoDoArquivo, Cliente *cliente);

// Recebe o vetor de clientes para saida, caminho do arquivo, numero de linhas do arquivo e a agencia. 
// Faz a operacao dos clientes na ordem de saida deles. 
// Calcula as variacoes de BRL, USD e tempo. Abre o arquivo para escrita e escreve todas as informacoes dos clientes e variacoes.
void imprimeSaida(Cliente *cliente, char *caminhoDoArquivo, int numeroDeLinhas, Agencia *agencia);

#endif
