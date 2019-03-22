/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Primeiro Exercicio-Programa										**/
/** Arquivo: heapB.c												**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 10/12/2013														**/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "geodist.h"
#include "grafo_op.h"
#include "heapB.h"

int tamanhoHeap(Heap* h)
{
	return h->tamanho;
}

Heap* inicializaHeap(int tamanho)
{
	Heap* h = (Heap*)malloc(sizeof(Heap));
	
	h->array = (Vertice**)malloc(tamanho * sizeof(Vertice*));
	h->tamanho = 0;
	return h;
}

void inseriHeap(Heap* h, Vertice* inserido)
{
	Vertice** array = h->array;
	int tamanho = h->tamanho;
	
	inserido->descritor = tamanho;
	array[tamanho] = inserido;
	
	h->tamanho += 1;
}

void alteraDistancia(Heap* h, int i)
{
	Vertice** array = h->array;
	
	int pai = (i-1)/2;
	
	while (i > 0 && array[pai]->d > array[i]->d)
	{
		array[i]->descritor = pai;
		array[pai]->descritor = i;
		
		Vertice* aux = array[i];
		array[i] = array[pai];
		array[pai] = aux;
		i = pai;
		
		pai = (pai-1)/2; 
	}
}

Vertice* extraiMenor(Heap* h)
{
	Vertice** array = h->array;
	int tamanho = h->tamanho;
	
	Vertice* menor = array[0];
	array[0] = array[tamanho-1];
	
	array[0]->descritor = 0;
	
	h->tamanho -= 1;
	
	minimizaHeap(h, 0);
	
	return menor;
}

void minimizaHeap(Heap* h, int i)
{
	Vertice** array = h->array;
	int tamanho = h->tamanho;
	int e = (2*i) + 1;
	int d = (2*i) + 2;

	int menor = i;
	if(e < tamanho && array[e]->d < array[i]->d) menor = e;
	if(d < tamanho && array[d]->d < array[menor]->d) menor = d;
	if(menor != i)
	{
		int descI = array[i]->descritor;
		array[i]->descritor = array[menor]->descritor;
		array[menor]->descritor = descI;
		
		Vertice* aux = array[i];
		array[i] = array[menor];
		array[menor] = aux;
		minimizaHeap(h, menor);
	}
}