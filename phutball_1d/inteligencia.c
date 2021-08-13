#include "inteligencia.h"
#include <stddef.h>
#include <stdio.h>

void testaMalloc(void *ptr){
    if(!ptr){
        fprintf(stderr, "ERRO MALLOC");
        exit(1);
    }
}

char *criaVetor(){
    char *vetor = malloc(sizeof(char) * MAXSTR);
    testaMalloc(vetor);

    return vetor;
}

jogo_t *criaJogo(){
    jogo_t *jogo = malloc(sizeof(jogo_t));
    testaMalloc(jogo);

    jogo->campo = criaVetor();

    return jogo;
}

void leEntrada(char *buffer, jogo_t *jogo) {
    sscanf(strtok(buffer, " \n"), "%c", &(jogo->lado_meu));
    sscanf(strtok(NULL, " \n"), "%d", &(jogo->tam_campo));
    sscanf(strtok(NULL, " \n"), "%s", jogo->campo);
    sscanf(strtok(NULL, " \n"), "%c", &(jogo->lado_adv));
    sscanf(strtok(NULL, " \n"), "%c", &(jogo->mov_adv));
}

int descobrePosicaoBola(char *p_campo, int tam) {
    
    for (int i = 0; i < tam; i++) {
        if (p_campo[i] == 'o') return i; 
    }
    return 1;
}

//CONFERE AÍ RICHARD ACHO QUE TÁ CERTO MAS NAO CONSEGUI TESTAR :)
int heuristica(char *p_campo, int tam, int pos_bola) {

    //distancia da bola ate o fim do campo
    int dist = tam - pos_bola;

    //indice e numero de passos até terminar o jogo
    int i = dist+1, passos = 0;

    //checa a posicao adjacente da bola
    if(p_campo[i] == 'f')
        passos++; 

    //se é par, intera i em 1 e se é impar intera i em 2
    if(dist % 2 == 0)
        i++;
    else
        i+=2;

    //calcula o resto e dale
    for(;;i+=2){
        if(p_campo[i] == 'f')
            passos++;
    }

    return passos;
}

void copiaVetor(char *vetor_dest, char *vetor_orig, int tam){
    int i;
    for(i = 0; i < tam; i++){
        vetor_dest[i] = vetor_orig[i];
    }
}

char* buscaMelhorJogada (char *buffer) {

    //crio a struct
    jogo_t *jogo;
    jogo = criaJogo();

    leEntrada(buffer, jogo);

    /*
        printf("%c %d %s\n", lado_meu, tam_campo, campo);
        printf("%c %c\n", lado_adv, mov_adv);
    */

    jogo->pos_bola = descobrePosicaoBola(jogo->campo, jogo->tam_campo);

    //declarei o vetor temporário
    char *campo_tmp = criaVetor();
    for (int i = jogo->pos_bola + 1; i < jogo->tam_campo; i++) {

        //copiei o vetor temporário
        copiaVetor(campo_tmp, jogo->campo, jogo->tam_campo);

        if (campo_tmp[i] != 'f') {

            campo_tmp[i] = 'f';

            char *jogada;
            sprintf(jogada, "%c f %d", jogo->lado_meu, i);
        }

        int h = heuristica(campo_tmp, jogo->tam_campo, jogo->pos_bola);

        //controlador.push_back(make_pair(jogada, heuristica));
    }

    //return controlador.front().first;
    
    //freee nas variáveis
    free(campo_tmp);
    free(jogo->campo);
    free(jogo);

    char *tmp = "abc";
    return tmp;
}