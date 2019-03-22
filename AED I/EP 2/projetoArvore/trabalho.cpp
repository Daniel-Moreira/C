#include "arvore.h"

NO *criar() {
    NO *aux = (NO*) malloc(sizeof(NO));
    return(aux);
}

// NAO ALTERE ESTA FUNCAO - uso: destruir(p);
void destruir(NO *p) {
     free(p);
}

void exclui(NO *raiz)
{
	if (raiz)
	{
		exclui(raiz -> esq);
		exclui(raiz -> dir);
		destruir(raiz);
	}
}

int tamanhoSub(NO *raiz)
{
	int r = 0;
	if (raiz)
	{
		r += tamanhoSub(raiz -> esq) + 1;
		r += tamanhoSub(raiz -> dir) + 1;
		return r;
	}
	return r-1;
	
}

bool andaArvore(NO *raiz, int ch, int max)
{
	if(raiz)
	{
		if(raiz -> chave == ch && tamanhoSub(raiz) <= max)
		{
			exclui(raiz);
			return true;
		}	
		if (andaArvore(raiz -> esq, ch, max))raiz -> esq = NULL;
		if (andaArvore(raiz -> dir, ch, max))raiz -> dir = NULL;
	}
	return false;
}

// o EP consiste em implementar esta funcao
void excluirSubarvores(NO **raiz, int ch, int max) {
	if (*raiz)
	{
		if(andaArvore(*raiz, ch, max))*raiz = NULL;
	}
}
