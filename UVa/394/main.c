/* @JUDGE_ID:	Daniel.Moreira	394	C	"Mapmaker"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	char nome[15];
	int* arrayC;
	int dimension;
} Endereco;

int calculaC(int i, int d, int size, int* L, int* U, int* arrayC)
{
	scanf("%d %d", &L[i-1], &U[i-1]);
	if(i < d)
	{
		arrayC[i] = calculaC(i+1, d, size, L, U, arrayC) * (U[i]-L[i]+1);
		return arrayC[i];
	}
	
	arrayC[i] = size;
	return size;
}

int main ()
{
    int n, m, i, n2;
	scanf("%d %d", &n, &m);
	
	Endereco e[n];
	n2 = n;
	while(n > 0)
	{
		n--;
		int base, dimension, size; 
		scanf("%s %d %d %d", &e[n].nome, &base, &size, &dimension);
		
		int lowerBound[dimension];
		int upperBound[dimension];
		int* arrayC = (int*) malloc(sizeof(int)*(dimension+1));
		calculaC(1, dimension, size, lowerBound, upperBound, arrayC);
		
		int sum = 0;
		for(i = 1; i < dimension+1; i++) sum += arrayC[i]*lowerBound[i-1];
		arrayC[0] = base-sum;
		
		e[n].dimension = dimension;
		e[n].arrayC = arrayC;
	}
	
	while(m > 0)
	{
		m--;
		char nome[15];
		scanf("%s", &nome);
		
		for(i = 0; i < n2; i++)	if (strcmp(e[i].nome, nome) == 0) break;
		
		if (i < n2)
		{
			int tamanho = e[i].dimension;
			unsigned int resp = e[i].arrayC[0];
			int j;
			
			printf("%s[", nome);
			for(j = 1; j <= tamanho; j++)
			{
				int valor;
				scanf("%d", &valor);
				resp += e[i].arrayC[j]*valor;
				if (j != tamanho) printf("%d, ", valor);
				else printf("%d] = %d\n", valor, resp);
			}
		}
	}
	
	return 0;
}

/* @END_OF_SOURCE_CODE */