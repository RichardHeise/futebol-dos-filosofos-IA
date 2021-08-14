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
    return 0;
}

char* jogaChute(char* campo, int tam, int posBola, char** chutes, int tam_chutes) {
    char* jogada = criaVetor();
    return jogada;
}

char* descobreChutes(char* campo, int posBola, int tam, int* tam_chutes) {
    char* chutes_possiveis = criaVetor();
    return chutes_possiveis;
}

//ta certo agora meno
int heuristica(char *p_campo, int tam, int pos_bola) {

    //distancia da bola ate o fim do campo
    //printf("tamanho: %d, pos bola: %d\n", tam, pos_bola);

    int dist = tam - pos_bola;

    //printf("dist: %d\n", dist);

    //indice e numero de passos até terminar o jogo
    int i = pos_bola, passos = 0;

    //checa a posicao adjacente da bola
    //printf("posicao: %c\n", p_campo[i]);
    if(p_campo[i] != 'f')
        passos++; 

    //se é par, intera i em 1 e se é impar intera i em 2
    if(dist % 2 == 0)
        i++;
    else
        i+=2;

    //calcula o resto e dale
    for(; i < tam ; i+=2){
        if(p_campo[i] != 'f')
            passos++;
    }

    return passos+1;
}

// copia o vetor origem no vetor destino
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

    jogo->pos_bola = descobrePosicaoBola(jogo->campo, jogo->tam_campo)+1;

    //declarei o vetor temporário
    char *campo_tmp = criaVetor();
    char *jogada = criaVetor();
    char *melhorJogada = criaVetor();
    int melhorHeuristica = 500;

    printf("pos bola+1: %d\n", jogo->pos_bola+1);
    for (int i = jogo->pos_bola; i < jogo->tam_campo; i++) {

        //copiei o vetor temporário
        strcpy(campo_tmp, jogo->campo);

        if (campo_tmp[i] != 'f') {
            printf("i: %d\n", i);

            campo_tmp[i] = 'f';

            sprintf(jogada, "%c f %d", jogo->lado_meu, i+1);

            int h = heuristica(campo_tmp, jogo->tam_campo, jogo->pos_bola);
            printf("campo: %s, jogada: %s, heuristica: %d\n", campo_tmp, jogada, h);

            if (h < melhorHeuristica) {
                melhorHeuristica = h;
                strcpy(melhorJogada, jogada);
            }

        }

    }

    // implementar jogaChute() e decobreChutes()
    
    if (campo_tmp[jogo->pos_bola+1] == 'f') {
        strcpy(campo_tmp, jogo->campo);
        char *chutes = criaVetor(); 
        int qtdChutes = 0;

        chutes = descobreChutes(campo_tmp, jogo->pos_bola, jogo->tam_campo, &qtdChutes);
        
        for (int i = 0; i < qtdChutes; i++) {
            jogada = jogaChute(jogo->campo, jogo->tam_campo, jogo->pos_bola, &chutes, qtdChutes);

            int h = heuristica(campo_tmp, jogo->tam_campo, jogo->pos_bola);

            if (h < melhorHeuristica) {
                melhorHeuristica = h;
                strcpy(melhorJogada, jogada);
            }
        }
    }
    

    //freee nas variáveis
    free(campo_tmp);
    free(jogo->campo);
    free(jogo);
    free(jogada);

    printf("melhor jogada: %s\n", melhorJogada);
    return melhorJogada;
}