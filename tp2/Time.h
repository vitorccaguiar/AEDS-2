#ifndef Time_h
#define Time_h

typedef struct {
	char nome[64];
	int pontuacao;
}Time;

// Faz uma pesquisa binaria sendo que a chave buscada eh o nome do time
int buscaTimeNome(Time *times, char *nome, int *tamanhoVetor);

// Faz uma pesquisa binaria sendo que a chave buscada eh a pontuacao do time
int buscaTimePontuacao(Time *times, int pontuacao, int *tamanhoVetor);

// Insere na ultima posicao do vetor de times ordenados por nome
void insereVetorTimeNome(Time *times, char *nome, int *final);

// Insere na ultima posicao do vetor de times ordenados por pontuacao
void insereVetorTimePontuacao(Time *times, char *nome, int *final);

// Insere na ultima posicao do vetor de times que nao jogaram
void insereTimeQueNaoJogou(Time *times, char *nome, int *final);

// Ordena o vetor pela chave pontuacao e considerando a ordem alfabetica no empate utilizando o metodo de Insercao
void OrdenaPorPontuacao(Time *times, int *n);

// Ordena o vetor pela chave nome utilizando o metodo de Insercao
void OrdenaPorNome(Time *times, int *n);

// Soma 3 pontos em determinado time nos vetores timesOrdenadoNome e timesOrdenadoPontuacao
void fazOperacaoVitoria(Time *timesOrdenadoNome, Time *timesOrdenadoPontuacao, int indiceVetor, int indiceVetor2);

// Soma 1 ponto para dois times nos vetores timesOrdenadoNome e timesOrdenadoPontuacao
void fazOperacaoEmpate(Time *timesOrdenadoNome, Time *timesOrdenadoPontuacao, int indiceVetor, int indiceVetor2);

// Procura time e retorna a sua posicao no ranking
void fazConsultaRanking(char *nome, int ranking, FILE *saida);

// Procura time e retorna a sua pontuacao
void fazConsultaPontuacao(char *nome, int pontuacao, FILE *saida);

// Retorna o ranking final do campeonato, apos todas as operacoes
void fazListaRanking(Time *timesOrdenadoPontuacao, FILE *saida, int *numeroDeTimes);

#endif