#include "uteis.h"

void testaMalloc(void *ptr){
    if(!ptr){
        fprintf(stderr, "ERRO MALLOC");
        exit(1);
    }
}

char *criaString(){
    char *vetor = malloc(sizeof(char) * MAXSTR);
    testaMalloc(vetor);

    return vetor;
}

int *criaVetor(){
    int *vetor = malloc(sizeof(int) * MAXSTR);
    testaMalloc(vetor);

    return vetor;
}

jogo_t *criaJogo(){
    jogo_t *jogo = malloc(sizeof(jogo_t));
    testaMalloc(jogo);

    jogo->campo = criaString();

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
    return -1;
}

//calcula os chutes necessários pra fazer o gol
void chuta(jogo_t *jogo, char *melhorJogada, int* chutes, int qtdChutes, int gol){

    char* tmp = criaString();
    sprintf(melhorJogada, "%c o %d", jogo->lado_meu, qtdChutes + ((gol) ? 1 : 0));

    for (int i = 0; i < qtdChutes; i++) {
        sprintf(tmp, " %d", chutes[i]+1);
        strcat(melhorJogada, tmp);
    }


    if (gol) {
        if (jogo->lado_meu == 'e') {
            sprintf(tmp, " %d", jogo->tam_campo+1);
            strcat(melhorJogada, tmp);
        } else {
            sprintf(tmp, " %d", 0);
            strcat(melhorJogada, tmp);
        }
    }

    free(tmp);
}