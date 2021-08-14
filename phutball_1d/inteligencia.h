#ifndef RESOLVEDOR_H
#define RESOLVEDOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "campo.h"
#include <math.h>

#define MAXSTR 512
#define MAXINT 16

// fiz a struct do jogo
typedef struct tipo_jogo
{
    char lado_meu, lado_adv, mov_adv;
    int tam_campo, pos_bola;
    char *campo;
    
}jogo_t;

// passei as funcoes que a gente fez pra ca

void testaMalloc(void *ptr);

int *criaVetor();

char *criaString();

jogo_t *criaJogo();

int descobrePosicaoBola(char *p_campo, int tam);

void leEntrada(char *buffer, jogo_t *jogo);

int heuristica(char *p_campo, int tam, int pos_bola);

char* buscaMelhorJogada (char *buffer);

#endif