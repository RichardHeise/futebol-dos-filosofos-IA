#include "inteligencia.h"

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
    return 0;
}

int heuristica(char *p_campo, int tam, int pos_bola) {

    //distancia da bola ate o fim do campo

    int dist = tam - pos_bola;

    //indice e numero de passos até terminar o jogo
    int i = pos_bola, passos = 0;

    //checa a posicao adjacente da bola
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

//calcula os chutes necessários pra fazer o gol
void fazerGol(jogo_t *jogo, char *melhorJogada, int* chutes, int qtdChutes){

    char* tmp = criaString();
    sprintf(melhorJogada, "%c o %d", jogo->lado_meu, qtdChutes+1);

    for (int i = 0; i < qtdChutes; i++) {
        sprintf(tmp, " %d", chutes[i]+1);
        strcat(melhorJogada, tmp);
    }

    sprintf(tmp, " %d", jogo->tam_campo+1);
    strcat(melhorJogada, tmp);

    sprintf(tmp, "\n");
    strcat(melhorJogada, tmp);

    free(tmp);
}

int testaFilosofosAdv(jogo_t *jogo, char *campo_tmp){

    int h, maiorHeuristica = 0;

    char* campo_tmpAdv = criaString();

    for (int j = jogo->pos_bola-2; j >= 0; j--) {

        strcpy(campo_tmpAdv, campo_tmp);

        if(campo_tmpAdv[j] != 'f'){
            
            campo_tmpAdv[j] = 'f';

            h = heuristica(campo_tmpAdv, jogo->tam_campo, jogo->pos_bola);

            if (h > maiorHeuristica) {
                maiorHeuristica = h;
            }

        }
    }

    printf("campo: %s, heuristica: %d\n", campo_tmp, h);
    free(campo_tmpAdv);
    return maiorHeuristica;
}

int testaChuteDireita(jogo_t *jogo, char *campo_tmp){

    int gol = 1, h, maiorHeuristica = 0;

    int contador = 0;

    for (int i = jogo->pos_bola+1; i < jogo->tam_campo; i++) {
        
        if (campo_tmp[i] == 'f') {
            contador = 0;

        } else {
            contador++;

            if ( contador == 2) {
                gol = 0;
                break;
            } else {

                strcpy(campo_tmp, jogo->campo);

                // limpa os filosofos do chute
                for (int k = jogo->pos_bola-1; k < i; k++) {
                    campo_tmp[k] = '.';
                }

                // chuta
                campo_tmp[i] = 'o';
                jogo->pos_bola = i;

                // analiso a heuristica do campo
                h = heuristica(campo_tmp, jogo->tam_campo, jogo->pos_bola);

                if (h > maiorHeuristica) {
                    maiorHeuristica = h;
                }
            }
        }
    }

    if(gol){
        if(jogo->lado_meu == 'e')
            return 0;
        return 34000;
    }

    return maiorHeuristica;
}

char* buscaMelhorJogada (char *buffer) {

    //crio a struct
    jogo_t *jogo;
    jogo = criaJogo();

    //le entrada e descobre posicao da bola
    leEntrada(buffer, jogo);
    jogo->pos_bola = descobrePosicaoBola(jogo->campo, jogo->tam_campo)+1;

    //declarei o vetor temporário
    char *campo_tmp = criaString();
    char *melhorJogada = criaString();
    int h, heu_fil, heu_chute, melhorHeuristica = 32000;

    printf("============ CHECANDO FILOSOFO =================\n");
    printf("pos bola: %d\n", jogo->pos_bola);

    // OTIMIZAR IGUAL A HEURISTICA!!!
    for (int i = jogo->pos_bola; i < jogo->tam_campo; i++) {

        //copiei o vetor temporário
        strcpy(campo_tmp, jogo->campo);

        if (campo_tmp[i] != 'f') {

            campo_tmp[i] = 'f';

            // comparando as jogadas atuais
            heu_fil = testaFilosofosAdv(jogo, campo_tmp);
            h = heu_fil;

            if (jogo->campo[jogo->pos_bola]  == 'f') {
                heu_chute = testaChuteDireita(jogo, campo_tmp);

                if(heu_fil > heu_chute)
                    h = heu_chute;
            }

            //if (jogo->campo[jogo->pos_bola-2] == 'f') {            }

            
            //comparando com a jogada passada
            if( h < melhorHeuristica){
                melhorHeuristica = h;
                sprintf(melhorJogada, "%c f %d", jogo->lado_meu, i+1);
            }
        }
    }

    printf("melhor jogada: %s, heuristica: %d\n", melhorJogada, melhorHeuristica);

    printf("============ CHECANDO CHUTE =================\n");
    // implementar jogaChute() e decobreChutes()
    
    int* chutes = criaVetor();
    int qtdChutes = 0;
    int gol = 0;

    if (jogo->campo[jogo->pos_bola] == 'f') {

        gol = 1;
        int contador = 0;

        for (int i = jogo->pos_bola+1; i < jogo->tam_campo; i++) {
            
            if (campo_tmp[i] == 'f') {
                contador = 0;

            } else {
                contador++;

                if ( contador == 2) {
                    gol = 0;
                    break;
                } else {
                    chutes[qtdChutes] = i;
                    qtdChutes++;

                    strcpy(campo_tmp, jogo->campo);

                    for (int k = jogo->pos_bola-1; k < i; k++) {
                        campo_tmp[k] = '.';
                    }

                    campo_tmp[i] = 'o';
                    jogo->pos_bola = i;
                }
            }
        }
    }
    
    if (gol) {
        fazerGol(jogo, melhorJogada, chutes, qtdChutes);
    }

    //freee nas variáveis
    free(campo_tmp);
    free(jogo->campo);
    free(jogo);

    printf("melhor jogada: %s\n", melhorJogada);
    return melhorJogada;
}