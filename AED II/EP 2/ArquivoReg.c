/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Segundo Exercicio-Programa										**/
/** Arquivo: ArquivoReg.c											**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 28/01/2013														**/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GeraIndice.h"
#include "ArquivoReg.h"


int registrosPorBloco()
{
	return TAMANHO_BLOCO/sizeof(Registro);
}

int indicesPorBloco()
{
	return TAMANHO_BLOCO/sizeof(EntradaIndice);
}

FILE* abreArqLeitura(char* arg)
{
	FILE* arq = fopen(arg, "rb");
	
	if(!arq)
	{
		printf( "Erro na abertura do arquivo");
		exit(0);
	}
	
	return arq;
}

FILE* abreArqEscrita(char* arg)
{
	FILE* arq = fopen(arg, "ab");
	
	return arq;
}

Registro leRegistroPos(char* arq, int pos, int* numBloco)
{
	int ultimaPosValida = 0;
	int blocoPos = pos/registrosPorBloco();
	long offset = blocoPos*TAMANHO_BLOCO;
	static int blocoAnterior;
	static Registro* reg;

	if(*numBloco == 0) reg = NULL;
	
	if(reg == NULL || blocoAnterior != blocoPos)
	{
		blocoAnterior = blocoPos;
		free(reg);
		reg = leBloco(arq, 1, &ultimaPosValida, &offset);
		*numBloco = *numBloco + 1;
	}
	
	return reg[pos-(blocoPos*registrosPorBloco())];
}

EntradaIndice leIndicePos(char* arq, int pos, int* numBloco)
{
	int ultimaPosValida = 0;
	int blocoPos = pos/indicesPorBloco();
	long offset = blocoPos*TAMANHO_BLOCO;
	static int blocoAnterior;
	static EntradaIndice* indice;

	if(*numBloco == 0) indice = NULL;
	
	if(indice == NULL || blocoAnterior != blocoPos)
	{
		blocoAnterior = blocoPos;
		indice = leBlocoIndice(arq, 1, &ultimaPosValida, &offset);
		*numBloco = *numBloco + 1;
	}
	
	return indice[pos-(blocoPos*indicesPorBloco())];
}

Registro* leBloco(char* arq, int qtdBlocos, int* ultimaPosValida, long* posAnterior)
{
	int totalRegistro = qtdBlocos*registrosPorBloco();
	
	Registro* reg = (Registro*)malloc(sizeof(Registro)*totalRegistro);
	FILE* temp = abreArqLeitura(arq);

	fseek(temp, *posAnterior, SEEK_SET);
	
	int i;
	int error = 0;
	
	error = fread(reg, sizeof(Registro), totalRegistro, temp);
	if(error != totalRegistro)
	{
		reg[error].id = INFINITO;
	}
	*ultimaPosValida = error;
	
	*posAnterior = ftell(temp);
	fclose(temp);
	
	return reg;
}

EntradaIndice* leBlocoIndice(char* arq, int qtdBlocos, int* ultimaPosValida, long* posAnterior)
{
	int totalRegistros = qtdBlocos*(TAMANHO_BLOCO/sizeof(EntradaIndice));
	
	EntradaIndice* indices = (EntradaIndice*)malloc(sizeof(EntradaIndice)*totalRegistros);
	FILE* temp = abreArqLeitura(arq);
	
	fseek(temp, *posAnterior, SEEK_SET);
	
	int i;
	int error = 0;
	
	error = fread(indices, sizeof(EntradaIndice), totalRegistros, temp);
	if(error != totalRegistros)
	{
		indices[error].id = INFINITO;
	}
	*ultimaPosValida = error;
	
	*posAnterior = ftell(temp);
	fclose(temp);
	
	return indices;
}

void escreveArq(Registro* reg, char* arq, int len)
{
	if (len == 0) return ;
	
	FILE* temp = abreArqEscrita(arq);
	
	fwrite(reg, sizeof(Registro), len, temp);
	
	fclose(temp);
}

void escreveArqIndice(EntradaIndice* indices, char* arq, int len)
{
	if (len == 0) return ;
	
	FILE* temp = abreArqEscrita(arq);
	
	fwrite(indices, sizeof(EntradaIndice), len, temp);
	
	fclose(temp);
}

void registroToIndice(Registro* reg, char* arq, int len, int numBloco)
{	
	FILE* temp = abreArqEscrita(arq);

	int i;
	for (i = 0; i < len; i++)
	{
		fwrite(&reg[i].id, sizeof(int32_t), 1, temp);
		
		int offsetBloco = numBloco*TAMANHO_BLOCO;
		int offset = i*sizeof(Registro) + offsetBloco;
		
		fwrite(&offset, sizeof(int32_t), 1, temp);
	}
	
	fclose(temp);
}

void escreveArqBusca(int id, Registro* reg, char* arq, int num, double tempo)
{
	FILE* temp = fopen(arq, "a");
	
	fprintf(temp, "%d ", id);
	if(reg)
	{
		fprintf(temp, "SIM ");
		fprintf(temp, "'%s' ", reg->conteudo);
	}
	else
	{
		fprintf(temp, "NAO ");
		fprintf(temp, "'' ");
	}
	fprintf(temp, "%d ", num);
	fprintf(temp, "%f\n", tempo);
	
	fclose(temp);
}

long tamanhoArq(char* arq)
{
    long tamanho;
 
	FILE* temp = abreArqLeitura(arq);
    
	fseek(temp, 0, SEEK_END);
    tamanho = ftell(temp);
 
	fclose(temp);
	
    return tamanho;
}