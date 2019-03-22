#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

// no da arvore
typedef struct estr {
        int chave;
        estr *esq;
	    estr *dir;
} NO; // no da arvore


// funcoes a implementar em trabalho.cpp


char *aluno1();
char *aluno2();
char *nrousp1();
char *nrousp2();
char *turma();

void excluirSubarvores(NO **raiz, int ch, int max);
