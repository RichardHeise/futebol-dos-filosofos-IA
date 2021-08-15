#ifndef DIREITA_H
#define DIREITA_H

#include "uteis.h"

int heuristicaDireita(char *p_campo, int tam, int pos_bola);

int testaFilosofosDireita(jogo_t *jogo, char *campo_tmp);

int testaChuteDireita(jogo_t *jogo, char *campo);

char* buscaMelhorJogadaDireita(jogo_t *jogo);

#endif