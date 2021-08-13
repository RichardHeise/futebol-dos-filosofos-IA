#ifndef RESOLVEDOR_H
#define RESOLVEDOR_H

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

char *criaVetor();

jogo_t *criaJogo();

void leEntrada(char *buffer, jogo_t *jogo);

int descobrePosicaoBola(char *p_campo, int tam);

int heuristica(char *p_campo, int tam, int pos_bola);

char* buscaMelhorJogada (char *buffer);

#endif