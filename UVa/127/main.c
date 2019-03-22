/* @JUDGE_ID:	Daniel.Moreira	127	C	"Accordian Patience"	*/
/* @BEGIN_OF_SOURCE_CODE */

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	char suit;
	char value;
} Card;

typedef struct
{
	Card carta[52];
	int topo;
} Stack;

int qtd(Stack* p)
{
	return p->topo+1;
}

void init(Stack* p)
{
	p->topo = -1;
}

Card novaCarta(char* carta)
{
	Card c;
	c.value = carta[0];
	c.suit = carta[1];
	
	return c;
}

void add(Stack* p, Card carta)
{
	p->topo++;
	Card* card = &p->carta[p->topo];
	
	card->suit = carta.suit;
	card->value = carta.value;
}

Card peek(Stack* p)
{
	return p->carta[p->topo];
}

Card removeCard(Stack* p)
{
	Card card = p->carta[p->topo];
	p->topo--;
	
	return card;
}

int comparaCartas(Card a, Card b)
{
	if(a.suit == b.suit || a.value == b.value) return 1;
	return 0;
}

void troca(Stack* dst, Stack *src)
{
	add(dst, removeCard(src));
}

void deslocaPilha(Stack* pilhas, int i, int n)
{
	for(; i < n; i++) pilhas[i] = pilhas[i+1];
	init(&pilhas[n]);
}

int main()
{
	int i;
	char leitura[3];
	Stack pilhas[52];
	
	while(scanf("%s", leitura) != EOF && leitura[0] != '#')
	{
		int n = 51;
		Card carta = novaCarta(leitura);
		
		init(&pilhas[0]);
		add(&pilhas[0], carta);
		
		for(i = 1; i < 52; i++)
		{
			scanf("%s", leitura);
			carta = novaCarta(leitura);
			init(&pilhas[i]);
			add(&pilhas[i], carta);
		}
		
		for(i = 1; i <= n; i++)
		{
			if(i-3 >= 0 && comparaCartas(peek(&pilhas[i-3]), peek(&pilhas[i])) == 1)
			{
				troca(&pilhas[i-3], &pilhas[i]);
				if(qtd(&pilhas[i]) == 0)
				{
					deslocaPilha(pilhas, i, n);
					n--;
				}
				i = 0;
			}
			else if(comparaCartas(peek(&pilhas[i-1]), peek(&pilhas[i])) == 1)
			{
				troca(&pilhas[i-1], &pilhas[i]);
				if(qtd(&pilhas[i]) == 0)
				{
					deslocaPilha(pilhas, i, n);
					n--;
				}
				i = 0;
			}
		}
		
		if(n == 0) printf("%d pile remaining: %d\n", n+1, qtd(&pilhas[0]));
		else
		{
			printf("%d piles remaining:", n+1);
			for(i = 0; i <= n; i++) printf(" %d", qtd(&pilhas[i]));
			printf("\n");
		}
	}
	
	return 0;
}

/* @END_OF_SOURCE_CODE */