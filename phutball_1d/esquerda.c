#include "esquerda.h"

// to tentando espelhar as 3am dps de roubar o dinf segura o pai (deve tar errado corrige ae)
int heuristicaEsquerda(char *p_campo, int tam, int pos_bola) {
    //distancia da bola ate o fim do campo

    int dist = pos_bola-1;

    if(dist == 0)
        return 5;

    //indice e numero de passos até terminar o jogo
    int i = pos_bola-2, passos = 0;

    //checa a posicao adjacente da bola
    if(p_campo[i] != 'f')
        passos++; 

    //se é par, intera i em 1 e se é impar intera i em 2
    if(dist % 2 == 0)
        i--;
    else
        i-=2;

    //calcula o resto e dale
    for(; i >= 0 ; i-=2){
        if(p_campo[i] != 'f')
            passos++;
    }

    return passos+1;
}