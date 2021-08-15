#include "direita.h"
#include "esquerda.h"

int heuristicaDireita(char *p_campo, int tam, int pos_bola) {

    //distancia da bola ate o fim do campo

    int caso;
    int dist = tam - pos_bola;
    if(dist == 0)
        return 5;

    //indice e numero de passos até terminar o jogo
    int i = pos_bola, passos = 0;

    //checa a posicao adjacente da bola
    if(p_campo[i] != 'f')
        passos++; 

    //se é par, intera i em 1 e se é impar intera i em 2
    caso = dist % 2;
    if(caso == 0)
        i++;
    else
        i+=2;

    //calcula o resto e dale
    // caso par 
    if (caso == 0) {
        for(; i < tam ; i+=2){
            if(p_campo[i] != 'f' && p_campo[i+1] != 'f')
                passos++;
        }
    }
    else {
        //caso impar
        for(; i < tam ; i+=2){
            if(p_campo[i] != 'f' && p_campo[i-1] != 'f')
                passos++;
        }
    }


    return passos+1;
}

int testaFilosofosDireita(jogo_t *jogo, char *campo_tmp){

    int h, maiorHeuristica = 0;

    char* campo_tmpAdv = criaString();

    for (int j = jogo->pos_bola-2; j >= 0; j--) {

        strcpy(campo_tmpAdv, campo_tmp);

        if(campo_tmpAdv[j] != 'f'){
            
            campo_tmpAdv[j] = 'f';

            h = heuristicaDireita(campo_tmpAdv, jogo->tam_campo, jogo->pos_bola);

            if (h > maiorHeuristica) {
                maiorHeuristica = h;
            }

        }
    }

    free(campo_tmpAdv);
    return maiorHeuristica;
}

int testaChuteDireita(jogo_t *jogo, char *campo){

    if( heuristicaDireita(campo, jogo->tam_campo, jogo->pos_bola) == 1 ){
        if(jogo->lado_meu == 'd')
            return 34000;
        return 1;
    }

    int h, maiorHeuristica = 0;

    int contador = 0;

    for (int i = jogo->pos_bola+1; i < jogo->tam_campo; i++) {
        
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
                for (int k = jogo->pos_bola-1; k < i; k++) {
                    campo_tmp[k] = '.';
                }

                // chuta
                campo_tmp[i] = 'o';

                // analiso a heuristicaDireita do campo
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

char* buscaMelhorJogadaDireita (jogo_t *jogo) {

    jogo->pos_bola = descobrePosicaoBola(jogo->campo, jogo->tam_campo)+1;

    //declarei o vetor temporário
    char *campo_tmp = criaString();
    char *melhorJogada = criaString();
    int h, heu_chute, melhorHeuristica = 32000;

    // OTIMIZAR IGUAL A HEURISTICA!!!
    for (int i = jogo->pos_bola; i < jogo->tam_campo; i++) {

        //copiei o vetor temporário
        strcpy(campo_tmp, jogo->campo);

        if (campo_tmp[i] != 'f') {

            campo_tmp[i] = 'f';

            // comparando as jogadas atuais
            h = testaFilosofosDireita(jogo, campo_tmp);

            if (jogo->campo[jogo->pos_bola]  == 'f') {
                heu_chute = testaChuteDireita(jogo, campo_tmp);

                if(heu_chute > h)
                    h = heu_chute;
            }

            if (jogo->campo[jogo->pos_bola-2] == 'f') {
                heu_chute = testaChuteEsquerda(jogo, campo_tmp);

                if(heu_chute > h )
                    h = heu_chute;
            }

            //comparando com a jogada passada
            if( h < melhorHeuristica){
                melhorHeuristica = h;
                sprintf(melhorJogada, "%c f %d", jogo->lado_meu, i+1);
            }
        }
    }

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
                    jogo->pos_bola = i+1;

                    h = testaFilosofosDireita(jogo, campo_tmp);

                    if (campo_tmp[i+1]  == 'f') {
                        heu_chute = testaChuteDireita(jogo, campo_tmp);

                        if(heu_chute > h)
                            h = heu_chute;
                    }
                    if (campo_tmp[i-2] == 'f') {
                        heu_chute = testaChuteEsquerda(jogo, campo_tmp);

                        if(heu_chute > h )
                            h = heu_chute;
                    }

                    //comparando com a jogada passada
                    if( h < melhorHeuristica){
                        melhorHeuristica = h;
                        chuta(jogo, melhorJogada, chutes, qtdChutes, 0);
                    }

                }
            }
        }
    }
    
    if (gol) {
        chuta(jogo, melhorJogada, chutes, qtdChutes, gol);
    }

    //freee nas variáveis
    free(campo_tmp);
    free(jogo->campo);
    free(jogo);

    return melhorJogada;
}