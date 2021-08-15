#ifndef DIREITA_H
#define DIREITA_H

#include "inteligencia.h"

void fazerGol(jogo_t *jogo, char *melhorJogada, int* chutes, int qtdChutes);

int heuristica(char *p_campo, int tam, int pos_bola);

int testaFilosofosAdv(jogo_t *jogo, char *campo_tmp);

int testaChuteDireita(jogo_t *jogo, char *campo);

char* buscaMelhorJogada (char *buffer);

#endif