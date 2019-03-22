/*********************************************************************/
/** ACH2024 - Algoritmos e Estruturas de Dados II					**/
/** EACH-USP - Segundo Semestre de 2013								**/
/** Turma: 02 - Flávio Luiz Coutinho								**/
/**																	**/
/** Primeiro Exercicio-Programa										**/
/** Arquivo: geodist.h												**/
/**																	**/
/** Nome: Daniel Augusto de Melo Moreira - Nº USP: 8122477			**/
/**																	**/
/** 10/12/2013														**/
/*********************************************************************/

#define RAD(a) ((a * M_PI) / 180.0)
#define EARTH_RADIUS 6371.009

typedef struct
{
	double x;
	double y;
	double z;
} Vector;

typedef struct
{
	double latitude;
	double longitude;
} Coordinate;

Coordinate coordinate(double latitude, double longitude);
Vector vector(Coordinate c);

double dot(Vector v1, Vector v2);
int distance(Coordinate c1, Coordinate c2);
