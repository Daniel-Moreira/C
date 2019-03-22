/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Primeiro Exercicio-Programa										**/
/** Arquivo: grafo_op.c												**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 10/12/2013														**/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

#include "geodist.h"
#include "grafo_op.h"
#include "fila.h"
#include "heapB.h"
#include "cronometro.h"

Grafo* criaGrafo(int max_v)
{
	Grafo* g = (Grafo*) malloc (sizeof(Grafo));
	
	g->arestasB = NULL;
	g->vertices = (Vertice*) malloc (max_v * sizeof(Vertice));
	g->nV = 0;
	g->nA = 0;

	return g;
}

void adicionaVertice(Grafo* g, int id, char* iata, char* city, char* country, Coordinate coordenada)
{
	Vertice v;

	v.id = id;
	v.cor = BRANCO;
	strcpy(v.iata, iata);
	strcpy(v.city, city);
	strcpy(v.country, country);
	v.coordenada = coordenada;
	v.d = 0;
	v.arestas = NULL;
	v.predecessor = NULL;
	
	g->vertices[g->nV] = v;
	g->nV++;
}

Vertice* getVertex(Grafo* g, char* iata)
{
	int i;
	
	for(i = 0; i < g->nV; i++)
	{
		if(strcmp(g->vertices[i].iata, iata) == 0) return &(g->vertices[i]);
	}
	return NULL;
}

Vertice* getVertexID(Grafo* g, int id)
{
	int i;
	
	for(i = 0; i < g->nV; i++)
	{
		if(g->vertices[i].id == id) return &(g->vertices[i]);
	}
	return NULL;
}

void adicionaAresta(Grafo* g, int u_id, int v_id)
{
	Vertice* u = getVertexID(g, u_id);
	Vertice* v = getVertexID(g, v_id);
	
	if(!u || !v) return;
	
	Aresta* aAdj = u->arestas;
	
	while(aAdj)
	{
		if(aAdj->dst == v) return;
		aAdj = aAdj->prox;
	}
	
	Aresta* a = (Aresta*) malloc(sizeof(Aresta));
	ArestaBellman* aB = (ArestaBellman*) malloc(sizeof(ArestaBellman));
	
	a->dst = v;
	a->distancia = distance(u->coordenada, v->coordenada);
	a->prox = u->arestas;
	u->arestas = a;

	aB->origem = u;
	aB->dst = v;
	aB->distancia = distance(u->coordenada, v->coordenada);
	aB->prox = g->arestasB;
	g->arestasB = aB;
	
	g->nA++;
}

void imprimeInformacoesGrafo(Grafo* g, Vertice* fonte, char* criterio, FILE* saida)
{
	printf("%s %s %d %d\n", fonte->iata, criterio, g->nV, g->nA);
	printf("# O grafo possui %d vertices e %d arestas.\n", g->nV, g->nA);
	printf("# Buscas de rotas feitas a partir do aeroporto %s.\n", fonte->iata);
	
	fprintf(saida, "%s %s %d %d\n", fonte->iata, criterio, g->nV, g->nA);
	
	if(strcmp(criterio, "DISTANCIA") == 0)
	{
		printf("# Tempo de execucao do algoritmo de Dijkstra %.3fs.\n", getTempo());
		fprintf(saida, "# Tempo de execucao do algoritmo de Dijkstra %.3fs.\n", getTempo());
	}
	else if(strcmp(criterio, "DIST_BELLMAN_FORD") == 0)
	{
		printf("# Tempo de execucao do algoritmo de Bellman-Ford %.3fs.\n", getTempo());
		fprintf(saida, "# Tempo de execucao do algoritmo de Bellman-Ford %.3fs.\n", getTempo());
	}
	
}

void imprimeInformacoes(Vertice* destino, FILE* saida)
{
	if(!destino->predecessor)
	{
		printf("%s NAO EXISTE CAMINHO\n", destino->iata);
		fprintf(saida, "%s NAO EXISTE CAMINHO\n", destino->iata);
		return;
	}
	
	printf("%s %d %d", destino->iata, destino->quantPredecessor, destino->d);
	
	fprintf(saida, "%s %d %d", destino->iata, destino->quantPredecessor, destino->d);
	
	imprimeCaminho(destino, saida);

	fprintf(saida, "\n");
	printf("\n");
}

void imprimeCaminho(Vertice* v, FILE* saida)
{
	if(v)
	{
		imprimeCaminho(v->predecessor, saida);
		printf(" %s", v->iata);
		fprintf(saida, " %s", v->iata);
	}
}

void buscaLargura(Grafo* g, Vertice* fonte)
{
	int i;
	int maxV = g->nV;
	
	if(maxV == 0) return;
	
	for(i = 0; i < maxV; i++)
	{
		g->vertices[i].cor = BRANCO;
		g->vertices[i].d = INFINITE;
		g->vertices[i].predecessor = NULL;
		g->vertices[i].quantPredecessor = 1;
	}
	fonte->cor = CINZA;
	fonte->d = 0;
	fonte->predecessor = NULL;
	
	Queue* q = inicializarFila();
	enqueue(q, fonte);
	
	while(filaVazia(q) == FALSE) //Fila Vazia
	{
		Vertice* v = dequeue(q);
		Aresta* a = v->arestas;
		while(a)
		{
			Vertice* vAdj = a->dst;
			if(vAdj->cor == BRANCO)
			{
				vAdj->cor = CINZA;
				vAdj->d = v->d + a->distancia;
				vAdj->predecessor = v;
				vAdj->quantPredecessor = v->quantPredecessor + 1;
				enqueue(q, vAdj);
			}
			a = a->prox;
		}
		v->cor = PRETO;
	}
}

void dijkstra(Grafo* g, Vertice* fonte)
{
	startClock();
	
	int qtdVertice = g->nV;
	if(qtdVertice == 0) return;
	
	Heap* h = inicializaHeap(qtdVertice); //fila com prioridade
	
	int i;
	for(i = 0; i < qtdVertice; i++)
	{
		g->vertices[i].d = INFINITE;
		g->vertices[i].predecessor = NULL;
		g->vertices[i].quantPredecessor = 1;	
		inseriHeap(h, &(g->vertices[i]));
	}
	
	fonte->d = 0;
	alteraDistancia(h, fonte->descritor);
	
	
	while(tamanhoHeap(h) > 0)
	{
		Vertice* v = extraiMenor(h);	
		Aresta* a = v->arestas;
		
		while(a)
		{
			if(relax(v, a->dst, a->distancia) == TRUE)
			{
				alteraDistancia(h, a->dst->descritor);
			}
			a = a->prox;
		}
	}
	
	stopClock();
}

int bellmanFord(Grafo* g, Vertice* fonte)
{
	startClock();
	
	if(g->nV == 0) return FALSE;
	
	int i;
	for(i = 0; i < g->nV; i++)
	{
		g->vertices[i].d = INFINITE;
		g->vertices[i].predecessor = NULL;
		g->vertices[i].quantPredecessor = 1;
	}
	
	fonte->d = 0;
	
	for(i = 0; i < g->nV-1; i++)
	{
		ArestaBellman* a = g->arestasB;
		while(a)
		{
			relax(a->origem, a->dst, a->distancia);
			a = a->prox;
		}
	}
	
	ArestaBellman* a = g->arestasB;
	
	while(a)
	{
		if(a->dst->d > a->origem->d + a->distancia) 
		{
			return FALSE;
		}
		a = a->prox;
	}
	
	stopClock();
	
	return TRUE;
}

int relax(Vertice* v, Vertice* dst, int distancia)
{
	if(dst->d > v->d + distancia) 
	{
		dst->d = v->d + distancia;
		dst->predecessor = v;
		dst->quantPredecessor = v->quantPredecessor + 1;
		return TRUE;
	}
	
	return FALSE;
}
