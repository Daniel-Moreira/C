/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Primeiro Exercicio-Programa										**/
/** Arquivo: cronometro.c											**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 10/12/2013														**/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cronometro.h"

	clock_t tempoInicial;
	clock_t tempoFinal;
	
	void startClock()
	{
		tempoInicial = clock();
	}
	
	void stopClock()
	{
		tempoFinal = clock();
	}
	
	double getTempo()
	{
		return ((double)(tempoFinal - tempoInicial))/CLOCKS_PER_SEC;
	}