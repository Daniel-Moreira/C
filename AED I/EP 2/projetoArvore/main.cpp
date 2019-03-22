#include "arvore.h"

//====================================================================

NO *criar();

NO *criaArvore()
{
	NO * aux;
    NO * aux2;
    NO * aux3;
    NO * aux4;
    
    aux = criar();
    aux -> chave = 1;
    aux -> dir = NULL;
    aux -> esq = NULL;
    
    aux2 = criar();
    aux2 -> chave = 7;
    aux2 -> dir = aux;
    aux2 -> esq = NULL;
    
    aux = criar();
    aux -> chave = 4;
    aux -> dir = NULL;
    aux -> esq = NULL;
    
    aux3 = criar();
    aux3 -> chave = 8;
    aux3 -> dir = NULL;
    aux3 -> esq = aux;
    
    aux = criar();
    aux -> chave = 9;
    aux -> dir = aux3;
    aux -> esq = aux2;
    
    aux2 = criar();
    aux2 -> chave = 2;
    aux2 -> dir = NULL;
    aux2 -> esq = NULL;
    
    aux3 = criar();
    aux3 -> chave = 8;
    aux3 -> dir = aux2;
    aux3 -> esq = NULL;
    
    aux2 = criar();
    aux2 -> chave = 5;
    aux2 -> dir = NULL;
    aux2 -> esq = NULL;
    
    aux4 = criar();
    aux4 -> chave = 7;
    aux4 -> dir = aux3;
    aux4 -> esq = aux2;
    
    aux2 = criar();
    aux2 -> chave = 20;
    aux2 -> dir = aux4;
    aux2 -> esq = aux; 
    
    return aux2;
}

void printaArvore(NO *raiz)
{
	if(raiz)
	{
		printf("%d\n", raiz -> chave);
		printaArvore(raiz -> esq);
		printaArvore(raiz -> dir);
	}
}

int main() {

    NO *raiz = NULL;
    int ch, max;
    
    ch = 7;
    max = 2;

	raiz = criaArvore();
    // use esta area para inserir elementos em *raiz e testar seu EP

    // o EP será testado como no laco abaixo
    printaArvore(raiz);
    printf("\n");
    for(int i=1;i<=1;i++) {

         // crie valores de teste para int ch e int max aqui

         excluirSubarvores(&raiz, ch, max);
         printaArvore(raiz);
    }

    getch();
} // end main

