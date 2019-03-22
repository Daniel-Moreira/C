/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Segundo Exercicio-Programa										**/
/** Arquivo: GeraIndice.c											**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 28/01/2014														**/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "GeraIndice.h"
#include "ArquivoReg.h"

void geraIndice(char* arq, char* arqTopo, char* arqBase)
{
	int ultimaPosValida = 0;
	long posAnterior = 0;
	int numBloco = 0;
	
	do
	{
		Registro* reg = leBloco(arq, QTD_BLOCOS, &ultimaPosValida, &posAnterior);
		
		registroToIndice(reg, "TempIndice.bin", ultimaPosValida, numBloco);
		
		numBloco += QTD_BLOCOS;
		
		free(reg);
	} while(ultimaPosValida == QTD_BLOCOS*registrosPorBloco());

	ordenaIndice("TempIndice.bin", arqTopo, arqBase);
	
	remove("TempIndice.bin");
}

void ordenaIndice(char* arq, char* arqTopo, char* arqSaida)
{	
	int qtdLeitura = 0;
	int i = 0;
	char temp[20];
	int ultimaPosValida = 0;
	long posAnterior = 0;
	long offsetTopo = 0;
	
	do
	{
		// tenta ler 2000 blocos e ordena os registros com quick-sort
		EntradaIndice* indice = leBlocoIndice(arq, QTD_BLOCOS, &ultimaPosValida, &posAnterior);
		
		if(ultimaPosValida == 0) break;
		
		qsort(indice, ultimaPosValida, sizeof(EntradaIndice), compareIndice);
		// escreve os dados ordenados no disco
		sprintf(temp, "Temp%d.bin", i);
		escreveArqIndice(indice, temp, ultimaPosValida);
		
		free(indice);
		i++;
		
	}while(ultimaPosValida == QTD_BLOCOS*indicesPorBloco());
	
	int tamanhoBuffer = QTD_BLOCOS/(i+1);
	int qtdRegistros = tamanhoBuffer*indicesPorBloco();
	EntradaIndice* bufferEntrada[i];
	EntradaIndice* bufferSaida = (EntradaIndice*)malloc(sizeof(EntradaIndice)*qtdRegistros);
	
	int j;
	int indices[i+1];
	long bufferPosAnterior[i+1];
	for(j = 0; j < i; j++) 
	{
		indices[j] = 0;
		bufferPosAnterior[j] = 0;
		sprintf(temp, "Temp%d.bin", j);
		bufferEntrada[j] = leBlocoIndice(temp, tamanhoBuffer, &ultimaPosValida, &bufferPosAnterior[j]);
	}
	indices[i] = 0;
		
	int indiceArq;
	while(TRUE)
	{
		indiceArq = 0;
		int menor = bufferEntrada[indiceArq][indices[indiceArq]].id;
		int menorI = indiceArq;
		
		indiceArq++;
		while(indiceArq < i)
		{
			int idArqI = bufferEntrada[indiceArq][indices[indiceArq]].id;
			
			if(menor > idArqI)
			{
				menor = idArqI;
				menorI = indiceArq;
			}
			
			indiceArq++;
		}
		
		if(menor == INFINITO) break;
		
		if(qtdLeitura == 0)
		{
			qtdLeitura = indicesPorBloco();
			
			EntradaIndice indiceTopo = bufferEntrada[menorI][indices[menorI]];
			indiceTopo.offset = offsetTopo;
			
			escreveArqIndice(&indiceTopo, arqTopo, 1);
		
			offsetTopo += indicesPorBloco()*sizeof(EntradaIndice);
			
		}
		qtdLeitura--;
		
		bufferSaida[indices[indiceArq]] = bufferEntrada[menorI][indices[menorI]];
		indices[indiceArq]++;
		indices[menorI]++;
		

		if(indices[menorI] == qtdRegistros)
		{
			indices[menorI] = 0;
			
			sprintf(temp, "Temp%d.bin", menorI);
			bufferEntrada[menorI] = leBlocoIndice(temp, tamanhoBuffer, &ultimaPosValida, &bufferPosAnterior[menorI]);
		}
		if(indices[indiceArq] == qtdRegistros) 
		{
			escreveArqIndice(bufferSaida, arqSaida, indices[indiceArq]);
			indices[indiceArq] = 0;
		}
	}
	
	for(j = 0; j < i; j++)
	{
		sprintf(temp, "Temp%d.bin", j);
		remove(temp);
	}
	escreveArqIndice(bufferSaida, arqSaida, indices[indiceArq]);
}

int compareIndice(const void* a, const void* b)
{
	return (*(Registro*)a).id - (*(Registro*)b).id;
}