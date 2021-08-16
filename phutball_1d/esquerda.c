/**
 * Autores:
 * Richard Fernando Heise Ferreira GRR20101053
 * Carlos Iago Bueno GRR20190171
 */
#include "esquerda.h"
#include "direita.h"

int heuristicaEsquerda(char *p_campo, int tam, int pos_bola) {

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

    return passos+1;
}

int testaFilosofosEsquerda(jogo_t *jogo, char *campo_tmp) {

    int h, maiorHeuristica = 0;

    char* campo_tmpAdv = criaString();

    // caminha para a direita depois da bola
    for (int j = jogo->pos_bola; j < jogo->tam_campo; j++) {

        strcpy(campo_tmpAdv, campo_tmp);

        if(campo_tmpAdv[j] != 'f'){
            
            // colcoa filosofo
            campo_tmpAdv[j] = 'f';

            // testa a heuristica pra esquerda
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

    // se nosso oponente pode marcar um gol, desistimos
    if( heuristicaEsquerda(campo, jogo->tam_campo, jogo->pos_bola) == 1 ){
        if(jogo->lado_meu == 'e')
            return 34000;
        return 1;
    }

    int h, maiorHeuristica = 0;

    int contador = 0;

    // caminha para a esquerda
    for (int i = jogo->pos_bola-2; i >= 0; i--) {
        
        if (campo[i] == 'f') {
            contador = 0;

        } else {
            contador++;

            if ( contador == 2) {
                // se encontramos dois espacos vazios em sequencia, saimos
                break;
            } else {

                // copia para um vetor temporario
                char *campo_tmp = criaString();
                strcpy(campo_tmp, campo);

                // limpa os filosofos do chute
                for (int k = jogo->pos_bola-1; k > i; k--) {
                    campo_tmp[k] = '.';
                }

                // chuta
                campo_tmp[i] = 'o';

                // testa a heuristica para o lado que nos interessa
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

    // vetor temporario 
    char *campo_tmp = criaString();
    char *melhorJogada = criaString();
    int h, heu_chute, melhorHeuristica = 32000;

    // andamos para a esquerda da bola
    for (int i = jogo->pos_bola-2; i >= 0; i--) {

        // copiamos o vetor temporário
        strcpy(campo_tmp, jogo->campo);

        if (campo_tmp[i] != 'f') {
            
            // jogamos o filosofo
            campo_tmp[i] = 'f';

            // testando jogadas do oponente
            h = testaFilosofosEsquerda(jogo, campo_tmp);

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

            // comparando com a jogada passada
            if( h < melhorHeuristica){
                melhorHeuristica = h;
                sprintf(melhorJogada, "%c f %d", jogo->lado_meu, i+1);
            }
        }
    }
    
    int* chutes = criaVetor();
    int qtdChutes = 0;
    int gol = 0;

    // olha para a esquerda da bola, se tem um filosofo o chute eh possivel
    if (jogo->campo[jogo->pos_bola-2] == 'f') {

        gol = 1;
        int contador = 0;

        for (int i = jogo->pos_bola-3; i >= 0; i--) {
            
            if (campo_tmp[i] == 'f') {
                contador = 0;

            } else {
                contador++;

                if ( contador == 2) {
                    // se encontramos dois espacos vazios em sequencia, saimos
                    // se saimos por break, nao fizemos um gol
                    gol = 0;
                    break;

                } else {
                    // guarda os possiveis chutes
                    chutes[qtdChutes] = i;
                    qtdChutes++;

                    strcpy(campo_tmp, jogo->campo);

                    // desloca a bola
                    for (int k = jogo->pos_bola-1; k >= i; k--) {
                        campo_tmp[k] = '.';
                    }

                    // acerta a bola
                    campo_tmp[i] = 'o';
                    // nova posicao da bola
                    jogo->pos_bola = i+1;

                    // testa jogadas do oponente
                    h = testaFilosofosEsquerda(jogo, campo_tmp);

                    // comparando com a jogada passada
                    if( h < melhorHeuristica){
                        melhorHeuristica = h;
                        chuta(jogo, melhorJogada, chutes, qtdChutes, 0);
                    }
                }
            }
        }
    }
    
    // se foi gol, colocamos o gol na melhor jogada
    if (gol)
        chuta(jogo, melhorJogada, chutes, qtdChutes, gol);

    //freee nas variáveis
    free(campo_tmp);
    free(jogo->campo);
    free(jogo);

    return melhorJogada;
}