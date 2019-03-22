/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Segundo Exercicio-Programa										**/
/** Arquivo: ArquivoReg.h											**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 28/01/2014														**/
/*********************************************************************/

#include <stdint.h>

#define TRUE 1
#define QTD_BLOCOS 2000
#define INFINITO 999999999
#define TAMANHO_BLOCO 4096
#define TAMANHO_CONTEUDO 124

typedef struct
{
	int32_t id;
	char conteudo[TAMANHO_CONTEUDO];
	
} Registro;

int indicesPorBloco();
int registrosPorBloco();
long tamanhoArq(char* arq);
FILE* abreArqLeitura(char* arg);
FILE* abreArqEscrita(char* arg);
Registro leRegistroPos(char* arq, int pos, int* numBloco);
EntradaIndice leIndicePos(char* arq, int pos, int* numBloco);
Registro* leBloco(char* arq, int qtdBlocos, int* ultimaPosValida, long* posAnterior);
EntradaIndice* leBlocoIndice(char* arq, int qtdBlocos, int* ultimaPosValida, long* posAnterior);
void escreveArq(Registro* reg, char* arq, int len);
void escreveArqIndice(EntradaIndice* reg, char* arq, int len);
void registroToIndice(Registro* reg, char* arq, int len, int numBloco);
void escreveArqBusca(int id, Registro* reg, char* arq, int num, double tempo);