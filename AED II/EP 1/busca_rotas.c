/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Primeiro Exercicio-Programa										**/
/** Arquivo: busca_rotas.c											**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 10/12/2013														**/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "geodist.h"
#include "grafo_op.h"
#include "cronometro.h"

#define TAMANHO_STRING 50
#define QTD_VERTICE 9999

int campoValido(char* teste)
{
	if(teste == NULL) return FALSE;
	if(strcmp(teste, "\\N") == FALSE || strcmp(teste, "") == FALSE) return FALSE;
	
	return TRUE;
}

int strdelc(char *s, char c)
{
	int qtdRemovido = 0;
	
	while(*s)
	{
		if (*s == c)
		{
			strcpy(s, s + 1); //pula caracter
			qtdRemovido++;
		}
		else s++; //mantém caracter
	}
	
	return qtdRemovido;
}

char* strtokModificado(char* s)
{
	int aspa = 0;
	static char* comeco;
	char* token;
	
	if (s == NULL) s = comeco;
	while (*s == ',') s++;
	if (*s == '\0') return NULL;
	token = s;
	while (*s != ',' || aspa == 1)
	{
		if (*s == '"')
		{
			aspa = (aspa+1)%2;
		}
		s++;
	}
	*s = '\0';
	comeco = s + 1;
	
	return token;
}

int main(int argSize, char* args[])
{
	if(argSize < 2) return 0;
	
	Grafo* g = criaGrafo(QTD_VERTICE);
	
	FILE* arquivo = NULL;
	FILE* saida;
	FILE* arquivoVertice = NULL;
	FILE* arquivoAresta = NULL;

	char baseDadosVertices[TAMANHO_STRING];
	char baseDadosArestas[TAMANHO_STRING];
	char criterio[TAMANHO_STRING];
	char origem[4];
	int qtdDestino = 0; 
	
	arquivo = fopen(args[1], "r");
	
	if(!arquivo)
	{
		printf( "Erro na abertura do arquivo");
		exit(0);
	}

	fscanf(arquivo, "%s", baseDadosVertices);
	fscanf(arquivo, "%s", baseDadosArestas);
	fscanf(arquivo, "%s", criterio);
	fscanf(arquivo, "%s", origem);
	fscanf(arquivo, "%d", &qtdDestino);
	
	char destino[qtdDestino][4];
	
	int ind;
	
	for(ind = 0; ind < qtdDestino; ind++)
	{
		fscanf(arquivo, "%s", destino[ind]);
	}

	arquivoVertice = fopen(baseDadosVertices, "r");
	
	if(!arquivoVertice)
	{
		printf( "Erro na abertura do arquivo");
		exit(0);
	}
	
	do
	{
		int id = 0;
		char iata[4];
		char city[100];
		char country[100];
		float longitude = 0;
		float latitude = 0;
		char teste[500];
		char* partes;
		int entradaValida = 0;
		
		teste[0] = '\0';
		fgets(teste, 500, arquivoVertice);
		if(teste[0] == '\0' || teste[0] == '\n') break; 
		partes = (char*)strtokModificado(teste);
		
		int i;
		for(i = 0; i < 8; i++)
		{
			strdelc(partes, '"');
			
			if (campoValido(partes) == TRUE)
			{
				if(i == 0)
				{
					id = atoi(partes);
					entradaValida++;
				}
				else if(i == 2)
				{
					strcpy(city, partes);
					entradaValida++;
				}
				else if(i == 3)
				{
					strcpy(country, partes);
					entradaValida++;
				}
				else if(i == 4)
				{
					strcpy(iata, partes);
					entradaValida++;
				}
				else if(i == 6)
				{
					latitude = atof(partes);
					entradaValida++;
				}
				else if(i == 7) 
				{
					longitude = atof(partes);
					entradaValida++;
				}
			}
			partes = (char*)strtokModificado(NULL);
		}
	
		if(entradaValida == 6) adicionaVertice(g, id, iata, city, country, coordinate(latitude, longitude));
	}while(!feof(arquivoVertice));
	
	arquivoAresta = fopen(baseDadosArestas, "r");
	
	if(!arquivoAresta)
	{
		printf( "Erro na abertura do arquivo");
		exit(0);
	}
	
	do
	{
		int sourceID = 0;
		int destinationID = 0;
		char teste[200];
		char* partes;
		int entradaValida = 0;
		
		fgets(teste, 200, arquivoAresta);
		if(teste[0] == '\n') break; 
		partes = (char*)strtok(teste, ",");
  
		int i;
		for(i = 0; i < 6; i++)
		{
			if (campoValido(partes) == TRUE)
			{
				if(i == 3)
				{
					sourceID = atoi(partes);
					entradaValida++;
				}
				else if(i == 5)
				{
					destinationID = atoi(partes);
					entradaValida++;
				}
			}
			partes = (char*)strtok(NULL, ",");
		}
		if(entradaValida == 2) adicionaAresta(g, sourceID, destinationID);
	}while(!feof(arquivoAresta));
	
	saida = fopen(args[2], "w");
		
	if (strcmp(criterio, "DISTANCIA") == 0)
	{
		dijkstra(g, getVertex(g, origem));
	}
	else if(strcmp(criterio, "ESCALAS") == 0)
	{
		buscaLargura(g, getVertex(g, origem));
	}
	else if(strcmp(criterio, "DIST_BELLMAN_FORD") == 0)
	{
		int a = bellmanFord(g, getVertex(g, origem));
		if(a == FALSE) return 0;
	}
	
	imprimeInformacoesGrafo(g, getVertex(g, origem), criterio, saida);
	
	for(ind = 0; ind < qtdDestino; ind++)
	{
		Vertice* v = getVertex(g, destino[ind]);
		if(v) imprimeInformacoes(v, saida);
	}
	
	fclose(saida);
	fclose(arquivo);
	fclose(arquivoVertice);
	fclose(arquivoAresta);
	
	return 0;
}
