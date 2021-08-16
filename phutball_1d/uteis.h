/**
 * Autores:
 * Richard Fernando Heise Ferreira GRR20101053
 * Carlos Iago Bueno GRR20190171
 */

#ifndef RESOLVEDOR_H
#define RESOLVEDOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "campo.h"
#include <math.h>

#define MAXSTR 512
#define MAXINT 16

// Struct jogo 
typedef struct tipo_jogo
{
    char lado_meu, lado_adv, mov_adv;
    int tam_campo, pos_bola;
    char *campo;
    
}jogo_t;

/**
 * Testa se o alocamento funcionou
 * Retorna um erro caso não tenha funcionado.
 */
void testaMalloc(void *ptr);

/**
 * Cria um vetor de char (string)
 * Retorna a string criado.
 */
char *criaString();

/**
 * Inicializa a struct jogo.
 */
jogo_t *criaJogo();

/**
 * Cria um vetor de inteiro (string)
 * Retorna o vetor criado.
 */
int *criaVetor();

/**
 * Descobre a posicao da bola
 * Recebe uma string do campo e o tamanho do campo
 * Retorna um inteiro que é a posicao da bola.
 */
int descobrePosicaoBola(char *p_campo, int tam);

/**
 * Le o que veio do buffer e aloca na struct de jogo
 * Recebe o buffer e um ponteiro para a struct jogo.
 */
void leEntrada(char *buffer, jogo_t *jogo);

/**
 * Chuta a bola
 * Recebe uma struct jogo, a string jogada em que será escrito o chute,
 * o vetor de possiveis chutes, a quantidade de chutes possiveis e se o chute
 * foi ou não um gol.
 */
void chuta(jogo_t *jogo, char *melhorJogada, int* chutes, int qtdChutes, int gol);

#endif