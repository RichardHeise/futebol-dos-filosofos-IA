#include "inteligencia.h"

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

char* jogaChute(char* campo, int tam, int posBola, char** chutes, int tam_chutes) {
    char* jogada = criaVetor();
    return jogada;
}

int descobrePosicaoBola(char *p_campo, int tam) {
    
    for (int i = 0; i < tam; i++) {
        if (p_campo[i] == 'o') return i; 
    }
    return 0;
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
    char *melhorJogada = criaVetor();
    int melhorHeuristica = 500;

    printf("============ CHECANDO FILOSOFO =================\n");
    printf("pos bola: %d\n", jogo->pos_bola);

    // pra esquerda
    for (int i = jogo->pos_bola; i < jogo->tam_campo; i++) {

        //copiei o vetor temporário
        strcpy(campo_tmp, jogo->campo);

        if (campo_tmp[i] != 'f') {
            printf("i: %d\n", i);

            campo_tmp[i] = 'f';

            int h;

            char* campo_tmpAdv = criaVetor();

            for (int j = jogo->pos_bola-2; j >= 0; j--) {
                printf("j: %d\n", j);

                strcpy(campo_tmpAdv, campo_tmp);

                campo_tmpAdv[j] = 'f';

                h = heuristica(campo_tmpAdv, jogo->tam_campo, jogo->pos_bola);

                if (h < melhorHeuristica) {
                    melhorHeuristica = h;
                    sprintf(melhorJogada, "%c f %d", jogo->lado_meu, i+1);
                }

                printf("campo: %s, campo adv: %s\n", campo_tmp, campo_tmpAdv);
            }

            printf("campo: %s, heuristica: %d\n", campo_tmp, h);

        }

    }

    printf("============ CHECANDO CHUTE =================\n");
    // implementar jogaChute() e decobreChutes()
    
    int gol = 0;
    if (jogo->campo[jogo->pos_bola] == 'f') {

        //copiei o vetor temporário
        gol = 1;
        int contador = 0;
        int h;
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

                    for (int k = jogo->pos_bola-1; k < i; k++) {
                        campo_tmp[k] = '.';
                    }

                    campo_tmp[i] = 'o';
                    jogo->pos_bola = i;

                    h = heuristica(campo_tmp, jogo->tam_campo, jogo->pos_bola);

                    if (h < melhorHeuristica) {
                        melhorHeuristica = h;
                        sprintf(melhorJogada, "%c f %d", jogo->lado_meu, i+1);
                    }
                    printf("campo: %s, heuristica: %d\n", campo_tmp, h);
                }

            }

        }

    }
    if (gol) {
        sprintf(melhorJogada, "%c o 1 %d", jogo->lado_meu, 8); 
    }

    //freee nas variáveis
    free(campo_tmp);
    free(jogo->campo);
    free(jogo);

    printf("melhor jogada: %s\n", melhorJogada);
    return melhorJogada;
}