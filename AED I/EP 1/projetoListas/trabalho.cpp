#include "listas.h"

// crie neste arquivo as funcoes solicitadas e todas as demais rotinas necessarias para sua execucao
// tendo em mente que apenas o que esta implementado neste arquivo sera testado para fins de avaliacao
// do seu trabalho. Nao modifique as assinaturas destas funcoes, nem o conteudo de listas.h, ou seu
// programa nao passara nos testes.

char *aluno1()  { return ("Daniel Augusto de Melo Moreira"); } // escreva aqui o seu nome 
char *nrousp1() { return ("8122477"); }      // escreva aqui o seu nro USP 
char *aluno2()  { return ("Jose Roberto Ventaja"); } // escreva aqui o seu nome 
char *nrousp2() { return ("7972290"); }      // escreva aqui o seu nro USP 
char *turma() {return("02");}

// NAO ALTERE ESTA FUNCAO - uso:   NO *p = criar();
NO *criar() {
    NO *aux = (NO*) malloc(sizeof(NO));
    return(aux);
}

// NAO ALTERE ESTA FUNCAO - uso: destruir(p);
void destruir(NO *p) {
     free(p);
}


// O EP CONSISTE EM IMPLEMENTAR ESTA FUNCAO
void removerK(NO **inicio, int k) {
    // implemente a exclusao do K-esimo elemento aqui
    // usando as funcoes criar e destruir se necessario.
    // Nao esqueca de atualizar *inicio apos a exclusao
    // e percorrer a lista resultante em main() para ter
    // certeza de que funciona. 
	NO *imediatoAnt = NULL;
	NO *ant = *inicio;
	NO *atual = *inicio;
	int i = 0;
	if(k <= 0) return;
	while (i < k)
	{
		if(!atual) return;
		atual = atual -> prox;
		i++;
	}
	while(atual)
	{			
		imediatoAnt = ant;
		ant = ant -> prox;
		atual = atual -> prox;
	}
	if (ant == *inicio)
	{
		*inicio = ant -> prox;
	}
	else
	{
		imediatoAnt -> prox = ant -> prox; 
	}
	destruir(ant);
	return;
}
