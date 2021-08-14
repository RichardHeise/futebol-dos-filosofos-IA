#include "inteligencia.h"

int main(int argc, char **argv) {
  char *buffer = criaVetor();
  char *linha;
  
  campo_conecta(argc, argv);

  while(1) {
    campo_recebe(buffer);
    //printf("%s", buf);
    linha = buscaMelhorJogada(buffer);
    if(linha[0] == '0')
      break;
    sprintf(buffer, "%s\n", linha);
    //free(linha);
    campo_envia(buffer);
  }

  free(buffer);
}