/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Segundo Exercicio-Programa										**/
/** Arquivo: ep2.c													**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 28/01/2014														**/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cronometro.h"
#include "GeraIndice.h"
#include "ArquivoReg.h"
#include "Ordena.h"
#include "Busca.h"

#define  TAMANHO_STRING 100

char* leLinha(FILE* arq)
{
	char* linha = (char*)malloc(sizeof(char)*TAMANHO_STRING);
	
	fscanf(arq, "%s", linha);
	
	return linha;
}

int defineOp(char* ope)
{
	int retorno = -1;
	
	if(strcmp(ope, "ordena") == 0) retorno = 0;
	else if(strcmp(ope, "gera_indice") == 0) retorno = 1;
	else if(strcmp(ope, "busca_seq") == 0) retorno = 2;
	else if(strcmp(ope, "busca_bin") == 0) retorno = 3;
	else if(strcmp(ope, "busca_indice") == 0)retorno = 4;
	else if(strcmp(ope, "create") == 0)retorno = 5;
	
	return retorno;
}

int main(int argSize, char* args[])
{
	FILE* config = abreArqLeitura(args[1]);
	
	char* operacao = leLinha(config);
	
	int ope = defineOp(operacao);
	
	char* nomeArqEntrada = leLinha(config);
	char* nomeArqSaida = leLinha(config);
	
	if(ope == 0)
	{
		remove(nomeArqSaida);
		
		ordena(nomeArqEntrada, nomeArqSaida);
	}
	else if(ope == 1)
	{
		char* nomeArqTopo = nomeArqSaida;
		char* nomeArqBase = leLinha(config);
		
		remove(nomeArqTopo);
		remove(nomeArqBase);
		
		geraIndice(nomeArqEntrada, nomeArqTopo, nomeArqBase);
	}
	else if(ope == 2)
	{
		remove(nomeArqSaida);
		
		int qtdBuscas = atoi(leLinha(config));
		int i;
		
		for(i = 0; i < qtdBuscas; i++)
		{
			int id = atoi(leLinha(config));
			buscaSeq(nomeArqEntrada, nomeArqSaida, id);
		}
	}
	else if(ope == 3)
	{
		remove(nomeArqSaida);
		
		int qtdBuscas = atoi(leLinha(config));
		int i;
		
		for(i = 0; i < qtdBuscas; i++)
		{
			int id = atoi(leLinha(config));
			buscaBin(nomeArqEntrada, nomeArqSaida, id);
		}
	}
	else if(ope == 4)
	{
		
		char* nomeArqTopo = nomeArqSaida;
		char* nomeArqBase = leLinha(config);
		
		nomeArqSaida = leLinha(config);
		remove(nomeArqSaida);
		
		int qtdBuscas = atoi(leLinha(config));
		int i;
		
		for(i = 0; i < qtdBuscas; i++)
		{
			int id = atoi(leLinha(config));
			buscaInd(nomeArqEntrada, nomeArqTopo, nomeArqBase, nomeArqSaida, id);
		}
	}
	else if(ope == 5)
	{
		remove(nomeArqEntrada);
		
		int qtdR = atoi(nomeArqSaida)*registrosPorBloco();
		Registro* reg = (Registro*)malloc(sizeof(Registro)*qtdR);
		int i;
		
		for(i = 0; i < qtdR; i++)
		{
			reg[i].id = qtdR-i;
			sprintf(reg[i].conteudo, "Numero: %d ", qtdR-i);
		}
		
		escreveArq(reg, nomeArqEntrada, qtdR);
	}
	else
	{
		printf("Comando Invalido!");
	}
	
	fclose(config);
	
	return 0;
}
