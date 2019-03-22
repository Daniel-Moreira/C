/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Primeiro Exercicio-Programa										**/
/** Arquivo: grafo_op.h												**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 10/12/2013														**/
/*********************************************************************/

#define FALSE 0
#define TRUE 1
#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define INFINITE 999999

typedef struct verticeStruct
{
	int id;
	char iata[4];
	char city[100];
	char country[100];
	Coordinate coordenada;
	int cor;
	int d;
	int descritor;
	int quantPredecessor;
	struct verticeStruct* predecessor;
	struct ArestaStruct* arestas;
} Vertice;

typedef struct ArestaStruct
{
	int distancia;
	Vertice* dst;
	struct ArestaStruct* prox;
} Aresta;

typedef struct ArestaB
{
	int distancia;
	Vertice* origem;
	Vertice* dst;
	struct ArestaB* prox;
} ArestaBellman;

typedef struct
{
	int nV, nA;
	Vertice* vertices;
	ArestaBellman* arestasB;
} Grafo;


Grafo* criaGrafo(int max_v);
Vertice* getVertex(Grafo* g, char* iata);
Vertice* getVertexID(Grafo* g, int id);

void adicionaVertice(Grafo* g, int id, char* iata, char* city, char* country, Coordinate coordenada);
void adicionaAresta(Grafo* g, int u_id, int v_id);
void imprimeInformacoesGrafo(Grafo* g, Vertice* fonte, char* criterio, FILE* saida);
void imprimeInformacoes(Vertice* destino, FILE* saida);
void imprimeCaminho(Vertice* v, FILE* saida);

void buscaLargura(Grafo* g, Vertice* fonte);
void dijkstra(Grafo* g, Vertice* fonte);
int bellmanFord(Grafo* g, Vertice* fonte);
int relax(Vertice* v, Vertice* dst, int distancia);
