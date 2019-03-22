/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Segundo Exercicio-Programa										**/
/** Arquivo: Busca.c												**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 28/01/2013														**/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "cronometro.h"
#include "GeraIndice.h"
#include "ArquivoReg.h"
#include "Busca.h"

void buscaSeq(char* arq, char* arqSaida, int id)
{
	startClock();
	
	int numBloco = 0;
	int ultimaPosValida = 0;
	long posAnterior = 0;
	
	Registro* reg = leBloco(arq, 1, &ultimaPosValida, &posAnterior);
	
	while(ultimaPosValida != 0)
	{		
		numBloco++;
		int i;
		
		for(i = 0; i < ultimaPosValida; i++)
		{
			if (reg[i].id == id)
			{
				stopClock();
				escreveArqBusca(id, &reg[i], arqSaida, numBloco, getTempo());
				return ;
			}
		}
		
		free(reg);
		reg = leBloco(arq, 1, &ultimaPosValida, &posAnterior);
	}
	
	stopClock();
	escreveArqBusca(id, NULL, arqSaida, numBloco, getTempo());
}

void buscaBin(char* arq, char* arqSaida, int id)
{
	startClock();
	
	int inicio = 0;
	int numBloco = 0;
	int fim = (tamanhoArq(arq)/sizeof(Registro))-1;
	
	while(inicio <= fim)
	{
		int meio = (inicio+fim)/2;
		Registro reg = leRegistroPos(arq, meio, &numBloco);
		
		if (reg.id == id)
		{
			stopClock();
			escreveArqBusca(id, &reg, arqSaida, numBloco, getTempo());
			return ;
		}
		else if (reg.id > id) fim = meio-1;
		else inicio = meio+1;
	}
	
	stopClock();
	escreveArqBusca(id, NULL, arqSaida, numBloco, getTempo());
}

void buscaInd(char* arq, char* arqTopo, char* arqBase, char* arqSaida, int id)
{
	startClock();
	
	int numBloco = 0;
	int blocosLidos = 0;
	
	int inicio = 0;
	int fim = (tamanhoArq(arqTopo)/sizeof(EntradaIndice))-1;
	
	// Busca binaria no arqTopo
	EntradaIndice indiceEncontrado = buscaBinIndice(arqTopo, &numBloco, inicio, fim, id);
	blocosLidos += numBloco;

	numBloco = 0;
	inicio = (indiceEncontrado.offset)/sizeof(EntradaIndice);
	fim = (inicio+indicesPorBloco())-1;
		
	if (fim > (tamanhoArq(arqBase)/sizeof(EntradaIndice))-1) fim = (tamanhoArq(arqBase)/sizeof(EntradaIndice))-1;
	
	// Busca binaria no arqBase
	indiceEncontrado = buscaBinIndice(arqBase, &numBloco, inicio, fim, id);
	blocosLidos += numBloco;
	
	if(indiceEncontrado.id == id)
	{
		int pos = (indiceEncontrado.offset)/sizeof(Registro);
		numBloco = 0;
		
		Registro reg = leRegistroPos(arq, pos, &numBloco);
		blocosLidos += numBloco;
		
		stopClock();
		escreveArqBusca(id, &reg, arqSaida, blocosLidos, getTempo());
	}
	else
	{
		stopClock();
		escreveArqBusca(id, NULL, arqSaida, blocosLidos, getTempo());
	}
}

EntradaIndice buscaBinIndice(char* arq, int* blocosLidos, int inicio, int fim, int id)
{
	EntradaIndice menor;
	
	while(inicio <= fim)
	{
		int meio = (inicio+fim)/2;
		EntradaIndice atual = leIndicePos(arq, meio, blocosLidos);
		
		if (atual.id == id) return atual;
		else if (atual.id > id) fim = meio-1;
		else
		{
			menor = atual;
			inicio = meio+1;
		}
	}

	return menor;
}