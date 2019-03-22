/********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Primeiro Exercicio-Programa										**/
/** Arquivo: heapB.h												**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 10/12/2013														**/
/*********************************************************************/

typedef struct
{
	Vertice** array;
	int tamanho;
} Heap;

Heap* inicializaHeap(int tamanho);
void minimizaHeap(Heap* h, int i);
Vertice* extraiMenor(Heap* h);
int tamanhoHeap(Heap* h);
void alteraDistancia(Heap* h, int i);
void inseriHeap(Heap* h, Vertice* inserido);