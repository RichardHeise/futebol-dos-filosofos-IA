#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "campo.h"
#include <math.h>

#define MAXSTR 512

void leEntrada(char infos[], char *p_meuLado, char *p_advLado, char *p_advMov, int *p_tam, char *p_campo) {
    sscanf(strtok(infos, " \n"), "%c", &(*p_meuLado));
    sscanf(strtok(NULL, " \n"), "%d", &(*p_tam));
    sscanf(strtok(NULL, " \n"), "%s", p_campo);
    sscanf(strtok(NULL, " \n"), "%c", &(*p_advLado));
    sscanf(strtok(NULL, " \n"), "%c", &(*p_advMov));

    /*
        printf("%c %d %s\n", lado_meu, tam_campo, campo);
        printf("%c %c", lado_adv, mov_adv);
    */
}

char* buscaMelhorJogada (char infos[]) {
    char lado_meu, lado_adv, mov_adv;
    int tam_campo;
    char campo[MAXSTR];

    leEntrada(infos, &lado_meu, &lado_adv, &mov_adv, &tam_campo, campo);
    /*
        printf("%c %d %s\n", lado_meu, tam_campo, campo);
        printf("%c %c", lado_adv, mov_adv);
    */
    int pos_bola;
    pos_bola = descobrePosicaoBola();

    for (int i = pos_bola + 1; i < tam_campo; i++) {
        campo_tmp = campo;
        if (campo[i] != 'f') {
            campo_tmp[i] = 'f';
            char *jogada;
            sprintf(jogada, "%c f %d", lado_meu, i);
        }

        int heuristica = h(campo_tmp);

        controlador.push_back(make_pair(jogada, heuristica));
    }

    sort (controlador);

    return controlador.front().first;

}

int main(int argc, char **argv) {
  char buf[MAXSTR];
  char *linha;
  
  campo_conecta(argc, argv);

  while(1) {
    campo_recebe(buf);
    //printf("%s", buf);
    linha = buscaMelhorJogada(buf);
    if(linha[0] == '0')
      break;
    sprintf(buf, "%s\n", linha);
    //free(linha);
    campo_envia(buf);
  }
}