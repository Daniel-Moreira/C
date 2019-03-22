/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Segundo Exercicio-Programa										**/
/** Arquivo: Busca.h												**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 28/01/2014														**/
/*********************************************************************/

void buscaSeq(char* arq, char* arqSaida, int id);
void buscaBin(char* arq, char* arqSaida, int id);
void buscaInd(char* arq, char* arqTopo, char* arqBase, char* arqSaida, int id);
EntradaIndice buscaBinIndice(char* arq, int* blocosLidos, int inicio, int fim, int id);