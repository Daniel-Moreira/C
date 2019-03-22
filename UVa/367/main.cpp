/* @JUDGE_ID:	Daniel.Moreira	367	C	"Halting Factor Replacement Systems"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
	unsigned long long left;
	unsigned long long right;
	no *next;
}RULE;

void criaRegra(RULE **inicio, RULE **sentinela)
{
	RULE *aux = (RULE*)malloc(sizeof(RULE));
	scanf("%llu", &(aux->left));
	scanf("%llu", &(aux->right));
	aux -> next = NULL;
	if (!(*inicio))
	{
		*inicio = aux;
		*sentinela = aux;
		return ;
	}
	(*sentinela) -> next = aux;
	*sentinela = aux;
}

unsigned long long applyRules(RULE **inicio, unsigned long long n)
{
	RULE *aux = *inicio;
	while(aux)
	{
		
		if(n % aux -> left == 0)
		{
			n = (n/aux -> left) * aux -> right;
			aux = *inicio;
		}
		else
		{
			aux = aux -> next;
		}
	}
	return n;
}

int main()
{
	int n; 
	int FRSi = 1;
	scanf("%d", &n);
	while(n != 0)
	{
		printf("FRS #%d:\n", FRSi);
		int i;
		int nE;
		unsigned long long nT;
		RULE *inicio = NULL;
		RULE *sentinela = NULL;
		for(i = 0; i < n; i++)
		{
			criaRegra(&inicio, &sentinela);
		}
		scanf("%d", &nE);
		for(i = 0; i < nE; i++)
		{
			scanf("%llu", &nT);
			printf("     %llu becomes %llu\n", nT, applyRules(&inicio, nT));
		}
		FRSi++;
		scanf("%d", &n);
		printf("\n");
	}
	return 0;
}

/* @END_OF_SOURCE_CODE */
