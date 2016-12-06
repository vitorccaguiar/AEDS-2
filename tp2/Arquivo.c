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

int leQuantidadeDeLinhas(char *caminhoDoArquivo, Time **times) {
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
  		// incrementar numeroDeLinhas mais uma vez
  		if (existeLinhas) {
  			numeroDeLinhas++;
  		}
      // Aloca memoria e inicializa o vetor de times que sera ordenado por nome
  		*times = (Time*)malloc((2*numeroDeLinhas)*sizeof(Time)+1);
  		int i;
  		for(i = 0; i < (2*numeroDeLinhas)-1; i++) {
     	    strcpy((*times)[i].nome, "");
     	    (*times)[i].pontuacao =  0;
    	}
  	}
  	fclose(arq);
  	return numeroDeLinhas;
}

void analisaLinhaVitoriaOuEmpate(char *operacao, Time *timesOrdenadoNome, Time *timesOrdenadoPontuacao, int *numeroDeTimes) {
  int indiceVetor, indiceVetor2;

  // Pega o segundo argumento da linha
  char *primeiroNome = strtok_single(NULL, ",");
  if (strlen(primeiroNome) > 64) {
    printf("\n\tTamanho de um nome de time esta incorreto. Maximo de 63 caracteres.\n\n");
    exit(0);
  }
  if (strcmp(primeiroNome, "")==0 || strcmp(primeiroNome, " ")==0) {
    printf("\n\tCampo nome esta vazio.\n\n");
    exit(0);
  }

  indiceVetor = buscaTimeNome(timesOrdenadoNome, primeiroNome, numeroDeTimes);
  // Se o time nao existir no vetor
  if (indiceVetor == -1) {
    // Faz a insercao nos vetores ordenados por nome e por pontuacao
    // Ordena esses vetores depois da insercao
    insereVetorTimeNome(timesOrdenadoNome, primeiroNome, numeroDeTimes);
    insereVetorTimePontuacao(timesOrdenadoPontuacao, primeiroNome, numeroDeTimes);
    *numeroDeTimes = *numeroDeTimes +1;
    OrdenaPorNome(timesOrdenadoNome, numeroDeTimes);
    OrdenaPorPontuacao(timesOrdenadoPontuacao, numeroDeTimes);

    // Armazena os indices apos a insercao do novo time nos vetores
    indiceVetor = buscaTimeNome(timesOrdenadoNome, primeiroNome, numeroDeTimes);
    indiceVetor2 = buscaTimePontuacao(timesOrdenadoPontuacao, timesOrdenadoNome[indiceVetor].pontuacao, numeroDeTimes);
    
    // Verifica se existe times com pontuacao igual a buscada
    // Volta pra primeira ocorrencia da pontuacao igual
    // Pesquisa no grupo que possui pontuacao igual aquele que possui o nome desejado
    int pontuacao = timesOrdenadoNome[indiceVetor].pontuacao;
    while (timesOrdenadoPontuacao[indiceVetor2-1].pontuacao == pontuacao && (indiceVetor2-1) > 0) {
      indiceVetor2 --;
    }
    int i;
    for (i=indiceVetor2; i<=*(numeroDeTimes); i++) {
      if (strcmp(timesOrdenadoPontuacao[i].nome, primeiroNome)==0) {
        indiceVetor2 = i;
      }
    }

    // Faz a operacao e ordena os vetores novamente
    if (strcmp(operacao, "VITORIA")==0) {
      fazOperacaoVitoria(timesOrdenadoNome, timesOrdenadoPontuacao, indiceVetor, indiceVetor2);
      OrdenaPorNome(timesOrdenadoNome, numeroDeTimes);
      OrdenaPorPontuacao(timesOrdenadoPontuacao, numeroDeTimes);
    }
    else {
      fazOperacaoEmpate(timesOrdenadoNome, timesOrdenadoPontuacao, indiceVetor, indiceVetor2);
      OrdenaPorNome(timesOrdenadoNome, numeroDeTimes);
      OrdenaPorPontuacao(timesOrdenadoPontuacao, numeroDeTimes);
    } 
  }
  // Se o time existir no vetor
  else {
    indiceVetor2 = buscaTimePontuacao(timesOrdenadoPontuacao, timesOrdenadoNome[indiceVetor].pontuacao, numeroDeTimes);

    // Verifica se existe times com pontuacao igual a buscada
    // Volta pra primeira ocorrencia da pontuacao igual
    // Pesquisa no grupo que possui pontuacao igual aquele que possui o nome desejado
    int pontuacao = timesOrdenadoNome[indiceVetor].pontuacao;
    while (timesOrdenadoPontuacao[indiceVetor2-1].pontuacao == pontuacao && (indiceVetor2-1) > 0) {
      indiceVetor2 --;
    }
    int i;
    for (i=indiceVetor2; i<=*(numeroDeTimes); i++) {
      if (strcmp(timesOrdenadoPontuacao[i].nome, primeiroNome)==0) {
        indiceVetor2 = i;
      }
    }

    // Faz a operacao e ordena os vetores novamente
    if (strcmp(operacao, "VITORIA")==0) {
      fazOperacaoVitoria(timesOrdenadoNome, timesOrdenadoPontuacao, indiceVetor, indiceVetor2);
      OrdenaPorNome(timesOrdenadoNome, numeroDeTimes);
      OrdenaPorPontuacao(timesOrdenadoPontuacao, numeroDeTimes);
    }
    else {
      fazOperacaoEmpate(timesOrdenadoNome, timesOrdenadoPontuacao, indiceVetor, indiceVetor2);
      OrdenaPorNome(timesOrdenadoNome, numeroDeTimes);
      OrdenaPorPontuacao(timesOrdenadoPontuacao, numeroDeTimes);
    } 
  } 

  // Pega o terceiro argumento da linha
  char *segundoNome = strtok_single(NULL, ",");
  if (strlen(segundoNome) > 64) {
    printf("\n\tTamanho de um nome de time esta incorreto. Maximo de 63 caracteres.\n\n");
    exit(0);
  }
  if (strcmp(segundoNome, "")==0 || strcmp(segundoNome, " ")==0) {
    printf("\n\tCampo nome esta vazio.\n\n");
    exit(0);
  }
  // Verifica se este argumento possui um \n na ultima posicao do seu vetor
  // Se possuir, substitui o \n por 0
  if (segundoNome[strlen(segundoNome)-1] == '\n') {
    segundoNome[strlen(segundoNome)-1] = 0;
  }
  if (segundoNome[strlen(segundoNome)-1] == '\r') {
    segundoNome[strlen(segundoNome)-1] = 0;
  }

  indiceVetor = buscaTimeNome(timesOrdenadoNome, segundoNome, numeroDeTimes);
  // Se o time nao existir no vetor
  if (indiceVetor == -1) {
    // Faz a insercao nos vetores ordenados por nome e por pontuacao
    // Ordena esses vetores depois da insercao
    insereVetorTimeNome(timesOrdenadoNome, segundoNome, numeroDeTimes);
    insereVetorTimePontuacao(timesOrdenadoPontuacao, segundoNome, numeroDeTimes);
    *numeroDeTimes = *numeroDeTimes +1;
    OrdenaPorNome(timesOrdenadoNome, numeroDeTimes);
    OrdenaPorPontuacao(timesOrdenadoPontuacao, numeroDeTimes);

    // Armazena os indices apos a insercao do novo time nos vetores
    indiceVetor = buscaTimeNome(timesOrdenadoNome, segundoNome, numeroDeTimes);
    indiceVetor2 = buscaTimePontuacao(timesOrdenadoPontuacao, timesOrdenadoNome[indiceVetor].pontuacao, numeroDeTimes);

    // Verifica se existe times com pontuacao igual a buscada
    // Volta pra primeira ocorrencia da pontuacao igual
    // Pesquisa no grupo que possui pontuacao igual aquele que possui o nome desejado
    int pontuacao = timesOrdenadoNome[indiceVetor].pontuacao;
    while (timesOrdenadoPontuacao[indiceVetor2-1].pontuacao == pontuacao && (indiceVetor2-1) > 0) {
      indiceVetor2 --;
    }
    int i;
    for (i=indiceVetor2; i<=*(numeroDeTimes); i++) {
      if (strcmp(timesOrdenadoPontuacao[i].nome, segundoNome)==0) {
        indiceVetor2 = i;
      }
    }   

    // So vai fazer operacao no terceiro argumento se a operacao for empate 
    if (strcmp(operacao, "EMPATE")==0) {
      fazOperacaoEmpate(timesOrdenadoNome, timesOrdenadoPontuacao, indiceVetor, indiceVetor2);
      OrdenaPorNome(timesOrdenadoNome, numeroDeTimes);
      OrdenaPorPontuacao(timesOrdenadoPontuacao, numeroDeTimes);
    }
  }
  // Se o time existir no vetor
  else {
    if (strcmp(operacao, "EMPATE")==0) {
      indiceVetor2 = buscaTimePontuacao(timesOrdenadoPontuacao, timesOrdenadoNome[indiceVetor].pontuacao, numeroDeTimes);
      
      int pontuacao = timesOrdenadoNome[indiceVetor].pontuacao;
      while (timesOrdenadoPontuacao[indiceVetor2-1].pontuacao == pontuacao && (indiceVetor2-1) > 0) {
        indiceVetor2 --;
      }
      int i;
      for (i=indiceVetor2; i<=*(numeroDeTimes); i++) {
        if (strcmp(timesOrdenadoPontuacao[i].nome, segundoNome)==0) {
          indiceVetor2 = i;
        }
      } 

      fazOperacaoEmpate(timesOrdenadoNome, timesOrdenadoPontuacao, indiceVetor, indiceVetor2);
      OrdenaPorNome(timesOrdenadoNome, numeroDeTimes);
      OrdenaPorPontuacao(timesOrdenadoPontuacao, numeroDeTimes);
    }
  } 
} 

void analisaLinhaConsulta(Time *timesOrdenadoNome, Time *timesOrdenadoPontuacao, int *numeroDeTimes, FILE *saida) {
  char *tipoConsulta;
  // Retorna o argumento da linha que diz o tipo da consulta
  tipoConsulta = strtok_single(NULL, ",");

  if (strcmp(tipoConsulta, "PONTUACAO") == 0) {
    int indiceVetor;
    // Retorna o argumento da linha que possui o nome do time
    char *nome = strtok_single(NULL, ",");
    if (strlen(nome) > 64) {
      printf("\n\tTamanho de um nome de time esta incorreto. Maximo de 63 caracteres.\n\n");
      exit(0);
    }
    if (strcmp(nome, "")==0 || strcmp(nome, " ")==0) {
      printf("\n\tCampo nome esta vazio.\n\n");
      exit(0);
    }
    // Se o nome possuir \n no final, substitui por 0
    if (nome[strlen(nome)-1] == '\n') {
      nome[strlen(nome)-1] = '\0';
    }
    if (nome[strlen(nome)-1] == '\r') {
      nome[strlen(nome)-1] = 0;
    }

    indiceVetor = buscaTimeNome(timesOrdenadoNome, nome, numeroDeTimes);
    // Se o time nao existir no vetor
    if (indiceVetor == -1) {
      // Se consultar por time que nao jogou, retornar 0 na pontuacao
      fazConsultaPontuacao(nome, 0, saida);
    }
    // Se o time existir, faz a consulta retornando a pontuacao do time no vetor
    else {
      fazConsultaPontuacao(nome, timesOrdenadoNome[indiceVetor].pontuacao, saida);
    }
  } 
  else {
    if (strcmp(tipoConsulta, "RANKING") == 0) {
      int indiceVetor;

      char *nome = strtok_single(NULL, ",");
      if (strlen(nome) > 64) {
        printf("\n\tTamanho de um nome de time esta incorreto. Maximo de 63 caracteres.\n\n");
        exit(0);
      }
      if (strcmp(nome, "")==0 || strcmp(nome, " ")==0) {
        printf("\n\tCampo nome esta vazio.\n\n");
        exit(0);
      }
      if (nome[strlen(nome)-1] == '\n') {
        nome[strlen(nome)-1] = 0;
      }
      if (nome[strlen(nome)-1] == '\r') {
        nome[strlen(nome)-1] = 0;
      }

      indiceVetor = buscaTimeNome(timesOrdenadoNome, nome, numeroDeTimes);
      // Se o time nao existir no vetor
      if (indiceVetor == -1) {
        // Se consultar por time que nao jogou, retornar numeroDeTimes+1 no ranking
        fazConsultaRanking(nome, *(numeroDeTimes)+1, saida);
      }
      // Se existir no vetor
      else {
        int indiceVetorPontuacao;
        int pontuacao = timesOrdenadoNome[indiceVetor].pontuacao;
        indiceVetorPontuacao = buscaTimePontuacao(timesOrdenadoPontuacao, pontuacao, numeroDeTimes);
        
        // Verifica se existe times com pontuacao igual a buscada
        // Volta pra primeira ocorrencia da pontuacao igual
        // Pesquisa no grupo que possui pontuacao igual aquele que possui o nome desejado
        while (timesOrdenadoPontuacao[indiceVetorPontuacao-1].pontuacao == pontuacao && (indiceVetorPontuacao-1) > 0) {
          indiceVetorPontuacao --;
        }
        int i;
        for (i=indiceVetorPontuacao; i<=*(numeroDeTimes); i++) {
          if (strcmp(timesOrdenadoPontuacao[i].nome, nome)==0) {
            fazConsultaRanking(nome, i, saida);
          }
        }
      }              
    }
    else {
      printf("\n\tTipo de consulta invalida.\n\n");
      exit(0);
    }
  } 
} 

void verificaOperacao(char *operacao, Time *timesOrdenadoNome, Time *timesOrdenadoPontuacao, int *numeroDeTimes, FILE *saida) {
  if (strcmp(operacao, "VITORIA")==0 || strcmp(operacao, "EMPATE")==0) {
    analisaLinhaVitoriaOuEmpate(operacao, timesOrdenadoNome, timesOrdenadoPontuacao, numeroDeTimes);
  }
  if (strcmp(operacao, "CONSULTA")==0) {
    analisaLinhaConsulta(timesOrdenadoNome, timesOrdenadoPontuacao, numeroDeTimes, saida);
  } 
}

void analisaArquivo(char *caminhoDoArquivo, Time *timesOrdenadoNome, Time *timesOrdenadoPontuacao, FILE *saida) {
	char linha[150];
	char *operacao;
  // A cada insercao nos vetores ordenados por nome e pontuacao se acrescenta o valor de numeroDeTimes
	int *numeroDeTimes = (int*)malloc(sizeof(int));
  *numeroDeTimes = 0;

  // Abre arquivo para leitura
	FILE *arq = fopen(caminhoDoArquivo, "r");
	if (arq == NULL) {
		printf("\nNao foi possivel abrir o arquivo.\n");
    exit(0);
	}
	else {
		char c;
		int contadorArgumentos = 0;
    // Valida se o numero de argumentos da linha esta correto
		while ((c = fgetc(arq)) != EOF) {
			if(c == '\n') {
				if (contadorArgumentos != 2) {
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
    // Volta a ler o arquivo do inicio
		fseek(arq, 0, SEEK_SET);
    // Le linha por linha do arquivo 
 		while (fgets(linha, sizeof(linha), arq) != NULL) {
      // Verifica o tamanho maximo da linha
 			if (strlen(linha) > 138) {
 				printf("\n\tNumero de caracteres na linha invalido. Maximo eh 138.\n\n");
 				exit(0);
 			}
      // Pega o primeiro argumento da linha
 			operacao = strtok_single(linha, ",");
      // Verifica se a operacao eh valida
 			if (!strcmp(operacao, "VITORIA")==0 && !strcmp(operacao, "EMPATE")==0 && !strcmp(operacao, "CONSULTA")==0) {
 				printf("\n\tAlguma operacao de um cliente no arquivo esta invalida.\n\n");
 				exit(0);
 			}
      // Verifica se eh uma operacao de vitoria/empate ou consulta
      verificaOperacao(operacao, timesOrdenadoNome, timesOrdenadoPontuacao, numeroDeTimes, saida);
 		}
    // Retorna o ranking final do campeonato, apos todas as operacoes
    fazListaRanking(timesOrdenadoPontuacao, saida, numeroDeTimes);
	}
	fclose(arq);
  free(numeroDeTimes);
}
