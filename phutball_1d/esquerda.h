/**
 * Autores:
 * Richard Fernando Heise Ferreira GRR20101053
 * Carlos Iago Bueno GRR20190171
 */
#ifndef ESQUERDA_H
#define ESQUERDA_H

#include "uteis.h"

/**
 * Quantas jogadas sao necessarias para se fazer gol na esquerda
 * Recebe um campo, o tamanho do campo e a posicao da bola
 * Retorna o numero de jogadas necessarias para vencer.
 */
int heuristicaEsquerda(char *p_campo, int tam, int pos_bola);

/**
 * Testa a heuristicaEsquerda colocando filosofos na direita da bola
 * Recebe um ponteiro para o jogo e um campo
 * Retorna a heuristica para todas as jogadas possiveis de filosofos
 * na direita do campo.
 */
int testaFilosofosEsquerda(jogo_t *jogo, char *campo_tmp);

/**
 * Testa a heuristicaEsquerda chutes para a esquerda
 * Recebe um ponteiro para o jogo e um campo
 * Retorna a heuristica para todas as jogadas possiveis de chutes
 * para a esquerda do campo.
 */
int testaChuteEsquerda(jogo_t *jogo, char *campo);

/**
 * Busca a jogada que da menos chance do jogador da direita perder o jogo
 * Recebe um ponteiro jogo
 * Retorna uma string com a melhor jogada.
 */
char* buscaMelhorJogadaEsquerda (jogo_t *jogo);

#endif