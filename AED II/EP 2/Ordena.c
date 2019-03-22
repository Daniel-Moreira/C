/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Segundo Exercicio-Programa										**/
/** Arquivo: ordena.c												**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 28/01/2014														**/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "GeraIndice.h"
#include "ArquivoReg.h"
#include "Ordena.h"

void ordena(char* arq, char* arqSaida)
{
	int i = 0;
	char temp[20];
	int ultimaPosValida = 0;
	long posAnterior = 0;
	
	do
	{
		// tenta ler 2000 blocos e ordena os registros com quick-sort
		Registro* reg = leBloco(arq, QTD_BLOCOS, &ultimaPosValida, &posAnterior);
		
		if(ultimaPosValida == 0) break;
		
		qsort(reg, ultimaPosValida, sizeof(Registro), compare);
		// escreve os dados ordenados no disco
		sprintf(temp, "Temp%d.bin", i);
		escreveArq(reg, temp, ultimaPosValida);
		
		free(reg);
		i++;
	}while(ultimaPosValida == QTD_BLOCOS*registrosPorBloco());
	
	int tamanhoBuffer = QTD_BLOCOS/(i+1);
	int qtdRegistros = tamanhoBuffer*registrosPorBloco();
	Registro* bufferEntrada[i];
	Registro* bufferSaida = (Registro*)malloc(sizeof(Registro)*qtdRegistros);
	
	int j;
	int indices[i+1];
	long bufferPosAnterior[i+1];
	for(j = 0; j < i; j++) 
	{
		indices[j] = 0;
		bufferPosAnterior[j] = 0;
		sprintf(temp, "Temp%d.bin", j);
		bufferEntrada[j] = leBloco(temp, tamanhoBuffer, &ultimaPosValida, &bufferPosAnterior[j]);
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
		
		bufferSaida[indices[indiceArq]] = bufferEntrada[menorI][indices[menorI]];
		indices[indiceArq]++;
		indices[menorI]++;
		
		if(indices[menorI] == qtdRegistros)
		{
			indices[menorI] = 0;
			
			sprintf(temp, "Temp%d.bin", menorI);
			bufferEntrada[menorI] = leBloco(temp, tamanhoBuffer, &ultimaPosValida, &bufferPosAnterior[menorI]);
		}
		if(indices[indiceArq] == qtdRegistros) 
		{
			escreveArq(bufferSaida, arqSaida, indices[indiceArq]);
			indices[indiceArq] = 0;
		}
	}
	
	for(j = 0; j < i; j++)
	{
		sprintf(temp, "Temp%d.bin", j);
		remove(temp);
	}
	escreveArq(bufferSaida, arqSaida, indices[indiceArq]);
}

int compare(const void* a, const void* b)
{
	return (*(Registro*)a).id - (*(Registro*)b).id;
}