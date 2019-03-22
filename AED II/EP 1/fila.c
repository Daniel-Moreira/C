/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Primeiro Exercicio-Programa										**/
/** Arquivo: fila.c													**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 10/12/2013														**/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "geodist.h"
#include "grafo_op.h"
#include "fila.h"

Queue* inicializarFila()
{
	Queue* q = (Queue*) malloc(sizeof(Queue)); 
	
	q->inicio = NULL;
	q->fim = NULL;
	
	return q;
}

void enqueue(Queue* q, Vertice* v)
{
	No* novoNo = (No*) malloc(sizeof(No));
	novoNo->vertice = v;
	novoNo->prox = NULL;
	
	if(q->inicio) q->fim->prox = novoNo;
	else q->inicio = novoNo;
	q->fim = novoNo;
}

Vertice* dequeue(Queue* q)
{
	if(!q->inicio) return NULL;
	
	Vertice* v = q->inicio->vertice;
	q->inicio = q->inicio->prox;
	
	return v;
}

Vertice* getMenor(Queue* q)
{
	No* noAtual = q->inicio;
	No* noAnterior = NULL;
	No* noRetornoAnterior = NULL;
	No* noRetorno = NULL;
	
	int menorGlobal = INFINITE;
	
	while(noAtual)
	{
		Vertice* vAtual = noAtual->vertice;
		if(vAtual->d <= menorGlobal)
		{
			noRetornoAnterior = noAnterior;
			noRetorno = noAtual;
			menorGlobal = vAtual->d;
		}
		noAnterior = noAtual;
		noAtual = noAtual->prox;
	}
	
	if(noRetornoAnterior) noRetornoAnterior->prox = noRetorno->prox;
	else q->inicio = noRetorno->prox;
	
	Vertice* v = noRetorno->vertice;
	
	free(noRetorno);
	
	return v;
}

int filaVazia(Queue* q)
{
	if(q->inicio) return FALSE;
	return TRUE;
}