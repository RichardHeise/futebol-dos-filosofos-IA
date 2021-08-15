#include "esquerda.h"
#include "direita.h"

int heuristicaEsquerda(char *p_campo, int tam, int pos_bola) {

    //printf("======================================\n");
    //printf("Capo da heuristica pra esquerda: %s\n pos da bola: %d\n\n", p_campo, pos_bola);
    //distancia da bola ate o fim do campo

    int caso;
    int dist = pos_bola-1;

    if(dist == 0)
        return 5;

    //indice e numero de passos até terminar o jogo
    int i = pos_bola-2, passos = 0;

    //checa a posicao adjacente da bola
    if(p_campo[i] != 'f')
        passos++; 

    //se é par, intera i em 1 e se é impar intera i em 2
    caso = dist % 2;

    if (caso == 0) {
        for(i = i - 1; i >= 0 ; i-=2){

            if ( (i-1) >= 0) {
                if(p_campo[i] != 'f' && p_campo[i-1] != 'f')
                    passos++;

            } else {
                if(p_campo[i] != 'f')
                    passos++;
            }
        }
    }
    else {
        //caso impar
        for(i = i - 2; i >= 0 ; i-=2){
            if(p_campo[i] != 'f')
                passos++;
        }
    }

    //printf("heuristica do campo da heuristica pra esquerda é de: %d\n", passos+1);
    //printf("======================================\n");
    return passos+1;
}

int testaFilosofosEsquerda(jogo_t *jogo, char *campo_tmp) {

    int h, maiorHeuristica = 0;

    char* campo_tmpAdv = criaString();

    for (int j = jogo->pos_bola; j < jogo->tam_campo; j++) {

        strcpy(campo_tmpAdv, campo_tmp);

        if(campo_tmpAdv[j] != 'f'){
            
            campo_tmpAdv[j] = 'f';

            h = heuristicaEsquerda(campo_tmpAdv, jogo->tam_campo, jogo->pos_bola);

            if (h > maiorHeuristica) {
                maiorHeuristica = h;
            }

        }
    }

    free(campo_tmpAdv);
    return maiorHeuristica;
}

int testaChuteEsquerda(jogo_t *jogo, char *campo) {

    if( heuristicaEsquerda(campo, jogo->tam_campo, jogo->pos_bola) == 1 ){
        if(jogo->lado_meu == 'e')
            return 34000;
        return 1;
    }

    int h, maiorHeuristica = 0;

    int contador = 0;

    for (int i = jogo->pos_bola-2; i >= 0; i--) {
        
        if (campo[i] == 'f') {
            contador = 0;

        } else {
            contador++;

            if ( contador == 2) {
                break;
            } else {
                char *campo_tmp = criaString();
                strcpy(campo_tmp, campo);

                // limpa os filosofos do chute
                for (int k = jogo->pos_bola-1; k > i; k--) {
                    campo_tmp[k] = '.';
                }

                // chuta
                campo_tmp[i] = 'o';

                if (jogo->lado_meu == 'd')
                    h = heuristicaEsquerda(campo_tmp, jogo->tam_campo, i+1);
                else
                    h = heuristicaDireita(campo_tmp, jogo->tam_campo, i+1);

                if (h > maiorHeuristica) {
                    maiorHeuristica = h;
                }

            }
        }
    }

    return maiorHeuristica;
}

char* buscaMelhorJogadaEsquerda (jogo_t *jogo) {

    jogo->pos_bola = descobrePosicaoBola(jogo->campo, jogo->tam_campo)+1;

    //declarei o vetor temporário
    char *campo_tmp = criaString();
    char *melhorJogada = criaString();
    int h, heu_chute, melhorHeuristica = 32000;

    printf("============ CHECANDO FILOSOFO =================\n");
    printf("\n");
    printf("pos bola: %d\n", jogo->pos_bola);
    printf("\n");

    // OTIMIZAR IGUAL A HEURISTICA!!!
    for (int i = jogo->pos_bola-2; i >= 0; i--) {

        //copiei o vetor temporário
        strcpy(campo_tmp, jogo->campo);

        if (campo_tmp[i] != 'f') {

            printf("campo antes:\n");
            printf("%s\n", campo_tmp);
            printf("\n");

            campo_tmp[i] = 'f';

            printf("campo depois:\n");
            printf("%s\n", campo_tmp);
            printf("\n");

            // comparando as jogadas atuais
            h = testaFilosofosEsquerda(jogo, campo_tmp);

            printf("heuristica filosofos: %d\n", h);
            printf("\n");

            if (jogo->campo[jogo->pos_bola]  == 'f') {
                heu_chute = testaChuteDireita(jogo, campo_tmp);

                printf("heuristica chute pra direita: %d\n", heu_chute);
                if(heu_chute > h)
                    h = heu_chute;
            }
            printf("\n");

            if (jogo->campo[jogo->pos_bola-2] == 'f') {
                heu_chute = testaChuteEsquerda(jogo, campo_tmp);

                printf("heuristica chute pra esquerda: %d\n", heu_chute);    
                if(heu_chute > h )
                    h = heu_chute;
            }
            printf("\n");

            //comparando com a jogada passada
            if( h < melhorHeuristica){
                melhorHeuristica = h;
                sprintf(melhorJogada, "%c f %d", jogo->lado_meu, i+1);
            }


            printf("Colocamos um filosofo na posicao %d, a melhor heuristica foi: %d e a melhor jogada %s\n", i+1, melhorHeuristica, melhorJogada);
        }
    }
    printf("\n");

    printf("melhor jogada só com filósofo: %s\n", melhorJogada);

    printf("============ CHECANDO CHUTE =================\n");
    
    int* chutes = criaVetor();
    int qtdChutes = 0;
    int gol = 0;

    if (jogo->campo[jogo->pos_bola-2] == 'f') {

        printf("ta entrano? thats what she said\n\n");
        gol = 1;
        int contador = 0;

        for (int i = jogo->pos_bola-3; i >= 0; i--) {
            
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

                    printf("campo antes:\n");
                    printf("%s\n", campo_tmp);
                    printf("\n");

                    strcpy(campo_tmp, jogo->campo);


                    for (int k = jogo->pos_bola-1; k >= i; k--) {
                        campo_tmp[k] = '.';
                    }

                    campo_tmp[i] = 'o';
                    jogo->pos_bola = i+1;

                    printf("campo depois:\n");
                    printf("%s\n", campo_tmp);
                    printf("\n");

                    h = testaFilosofosEsquerda(jogo, campo_tmp);
                    printf("heuristica filosofos: %d\n", h);
                    printf("\n");

                    //comparando com a jogada passada
                    if( h < melhorHeuristica){
                        melhorHeuristica = h;
                        chuta(jogo, melhorJogada, chutes, qtdChutes, 0);
                    }

                    printf("Chutamos a bola para a posicao %d, a melhor heuristica foi: %d e a melhor jogada %s\n", i+1, melhorHeuristica, melhorJogada);
                }
            }
        }
    }
    
    if (gol)
        chuta(jogo, melhorJogada, chutes, qtdChutes, gol);

    //freee nas variáveis
    free(campo_tmp);
    free(jogo->campo);
    free(jogo);

    printf("O que chegou no final foi a jogada: %s\n\n", melhorJogada);
    return melhorJogada;
}