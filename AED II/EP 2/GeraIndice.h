/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Segundo Exercicio-Programa										**/
/** Arquivo: GeraIndice.h											**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 28/01/2014														**/
/*********************************************************************/

#include <stdint.h>

typedef struct
{
	int32_t id;
	int32_t offset;
	
} EntradaIndice;

void geraIndice(char* arq, char* arqTopo, char* arqBase);
void ordenaIndice(char* arq, char* arqTopo, char* arqSaida);
int compareIndice(const void* a, const void* b);