/* @JUDGE_ID:	Daniel.Moreira	104		C	"Arbitrage"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>
#include <string.h>

#define N 20

double graph[N][N][N];
int caminho[N][N][N];

void imprimeCaminho(int i, int j, int s)
{
	if(s == 0) return;
	j = caminho[i][j][s];
	imprimeCaminho(i, j, s-1);
	printf("%d ", j+1);
}

int temLucro(int s, int n)
{
	int k;
	for(k = 0; k < n; k++)
	{
		if(graph[k][k][s] >= 1.01)
		{
			printf("%d ", k+1);
			imprimeCaminho(k, k, s);
			printf("%d\n", k+1);
			return 1;
		}
	}
	
	return 0;
}

void fW(int n)
{
	int i, j, k, s;
	int resp = 0;
	
	for(s = 1; s < n && resp == 0; s++)
	{
		for(k = 0; k < n; k++)
		{
			for(i = 0; i < n; i++)
			{
				for(j = 0; j < n; j++)
				{
					double max = graph[i][k][s-1]*graph[k][j][0];
					if(max > graph[i][j][s])
					{
						graph[i][j][s] = max;
						caminho[i][j][s] = k;
					}
				}
			}
		}
		resp = temLucro(s, n);
	}

	if(resp == 0) printf("no arbitrage sequence exists\n");
}

int main()
{
	int n;
	
	while(scanf("%d", &n) != EOF)
	{
		memset(graph, 0, sizeof(graph));
		memset(caminho, 0, sizeof(caminho));
		
		int i, j;
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < n; j++)
			{
				if(i == j) graph[i][j][0] = 1.0;
				else scanf("%lf", &graph[i][j][0]);
			}
		}
		
		fW(n);
	}
	
	return 0;
}

/* @END_OF_SOURCE_CODE */