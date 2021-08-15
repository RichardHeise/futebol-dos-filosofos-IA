#ifndef ESQUERDA_H
#define ESQUERDA_H

#include "uteis.h"

int heuristicaEsquerda(char *p_campo, int tam, int pos_bola);

int testaFilosofosEsquerda(jogo_t *jogo, char *campo_tmp);

int testaChuteEsquerda(jogo_t *jogo, char *campo);

char* buscaMelhorJogadaEsquerda (jogo_t *jogo);

#endif