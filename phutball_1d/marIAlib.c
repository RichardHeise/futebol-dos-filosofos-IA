#include "marIAlib.h"

char* resolve(char* buffer) {
    //crio a struct
    jogo_t *jogo;
    jogo = criaJogo();

    //le entrada e descobre posicao da bola
    leEntrada(buffer, jogo);
    
    if (jogo->lado_meu == 'e') {
        return buscaMelhorJogadaDireita(jogo);
    }
    if (jogo->lado_meu == 'd') {
        return buscaMelhorJogadaEsquerda(jogo);
    }

    return "0";
}

