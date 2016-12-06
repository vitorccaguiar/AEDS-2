#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Time.h"

int buscaTimeNome(Time *times, char *nome, int *tamanhoVetor) {
	int inf = 1; // Limite inferior     
    int sup = *(tamanhoVetor); // Limite superior    
    int meio;
    while (inf <= sup) {
    	meio = (inf + sup)/2;
        if (strcmp(times[meio].nome, nome) == 0) {
            return meio;
        }
        else {
        	if (strcmp(nome, times[meio].nome) < 0) {
            	sup = meio-1;
            }
       	    else {
            	inf = meio+1;
        	}
        }
    }
    return -1;
}

int buscaTimePontuacao(Time *times, int pontuacao, int *tamanhoVetor) {
  int inf = 1; // Limite inferior      
    int sup = *(tamanhoVetor); // Limite superior    
    int meio;
    while (inf <= sup) {
      meio = (inf + sup)/2;
        if (times[meio].pontuacao == pontuacao) {
            return meio;
        }
        else {
          if (times[meio].pontuacao < pontuacao) {
              sup = meio-1;
            }
            else {
              inf = meio+1;
          }
        }
    }
    return -1;
}

void OrdenaPorPontuacao(Time *times, int *n){
    int i=0, j=0, aux=0;
    Time x;
    for (i = 2; i <= *n; i++) {
        x = times[i];
        j = i - 1;
        times[0] = x; // sentinela 
        // Se for uma posicao valida e a pontuacao do time do meio for maior
        while (x.pontuacao >= times[j].pontuacao && j > 0 && aux!=1){
            // Analisa a ordem alfabetica em caso de empate
            if (x.pontuacao == times[j].pontuacao && strcmp(x.nome, times[j].nome) < 0) {
                times[j+1] = times[j];
                j--;
            }
            else {
                if (x.pontuacao > times[j].pontuacao) {
                    times[j+1] = times[j];
                    j--;
                }
                else {
                    aux=1;
                }
            }
        }
        aux=0;
        times[j+1] = x;
    }
}

void OrdenaPorNome(Time *times, int *n){
	int i, j;
	Time x;
	for (i = 2; i <= *n; i++) {
		x = times[i];
		j = i - 1;
		times[0] = x; // sentinela 
		while (strcmp(x.nome, times[j].nome) < 0){
			times[j+1] = times[j];
			j--;
		}
		times[j+1] = x;
	}
}

void insereTimeQueNaoJogou(Time *times, char *nome, int *final) {
    // Insere no final + 1, pois eh a ultima posicao
    strcpy(times[*final+1].nome, nome);
    times[*final+1].pontuacao = 0;
}

void insereVetorTimeNome(Time *times, char *nome, int *final) {
    // Insere no final + 1, pois eh a ultima posicao
    strcpy(times[*final+1].nome, nome);
    times[*final+1].pontuacao = 0;
}

void insereVetorTimePontuacao(Time *times, char *nome, int *final) {
    // Insere no final + 1, pois eh a ultima posicao
    strcpy(times[*final+1].nome, nome);
    times[*final+1].pontuacao = 0;
}

void fazOperacaoVitoria(Time *timesOrdenadoNome, Time *timesOrdenadoPontuacao, int indiceVetor, int indiceVetor2) {
	timesOrdenadoNome[indiceVetor].pontuacao += 3;
	timesOrdenadoPontuacao[indiceVetor2].pontuacao += 3;
}

void fazOperacaoEmpate(Time *timesOrdenadoNome, Time *timesOrdenadoPontuacao, int indiceVetor, int indiceVetor2) {
	timesOrdenadoNome[indiceVetor].pontuacao += 1;
	timesOrdenadoPontuacao[indiceVetor2].pontuacao += 1;
}

void fazConsultaRanking(char *nome, int ranking, FILE *saida) {
    char linha[100];

    sprintf(linha, "RANKING,%s,%d", nome, ranking);
    fprintf(saida, "%s\n", linha);
}

void fazConsultaPontuacao(char *nome, int pontuacao, FILE *saida) {
    char linha[100];

    sprintf(linha, "PONTUACAO,%s,%d", nome, pontuacao);
    fprintf(saida, "%s\n", linha);
}

void fazListaRanking(Time *timesOrdenadoPontuacao, FILE *saida, int *numeroDeTimes) {
    int i;
    char linha[100];
    for (i=1; i<=*(numeroDeTimes); i++) {
        sprintf(linha, "%d,%s,%d", i, timesOrdenadoPontuacao[i].nome, timesOrdenadoPontuacao[i].pontuacao);
        fprintf(saida, "%s\n", linha);
    }
}