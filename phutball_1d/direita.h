/**
 * Autores:
 * Richard Fernando Heise Ferreira GRR20101053
 * Carlos Iago Bueno GRR20190171
 */
#ifndef DIREITA_H
#define DIREITA_H

#include "uteis.h"

/**
 * Quantas jogadas sao necessarias para se fazer gol na direita
 * Recebe um campo, o tamanho do campo e a posicao da bola
 * Retorna o numero de jogadas necessarias para vencer.
 */
int heuristicaDireita(char *p_campo, int tam, int pos_bola);

/**
 * Testa a heuristicaEsquerda colocando filosofos na esquerda da bola
 * Recebe um ponteiro para o jogo e um campo
 * Retorna a heuristica para todas as jogadas possiveis de filosofos
 * na esquerda do campo.
 */
int testaFilosofosDireita(jogo_t *jogo, char *campo_tmp);

/**
 * Testa a heuristicaEsquerda chutes para a direita
 * Recebe um ponteiro para o jogo e um campo
 * Retorna a heuristica para todas as jogadas possiveis de chutes
 * para a direita do campo.
 */
int testaChuteDireita(jogo_t *jogo, char *campo);

/**
 * Busca a jogada que da menos chance do jogador da esquerda perder o jogo
 * Recebe um ponteiro jogo
 * Retorna uma string com a melhor jogada.
 */
char* buscaMelhorJogadaDireita(jogo_t *jogo);

#endif