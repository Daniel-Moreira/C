/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Primeiro Exercicio-Programa										**/
/** Arquivo: fila.h													**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 10/12/2013														**/
/*********************************************************************/

typedef struct NoStruct
{
	Vertice* vertice;
	struct NoStruct* prox;
} No;

typedef struct
{
	No* inicio;
	No* fim;
} Queue;

Queue* inicializarFila();
void enqueue(Queue* q, Vertice* v);
Vertice* dequeue(Queue* q);
int filaVazia(Queue* q);
Vertice* getMenor(Queue* q);