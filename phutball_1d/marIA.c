  
/**
 * Autores:
 * Richard Fernando Heise Ferreira GRR20101053
 * Carlos Iago Bueno GRR20190171
 */
#include "marIAlib.h"
#include "campo.h"

// Main da nossa IA
int main(int argc, char **argv) {
  char *buffer = criaString();
  char *linha;
  
  campo_conecta(argc, argv);

  while(1) {
    campo_recebe(buffer);
    // chama o resolutor
    linha = resolve(buffer);

    if(linha[0] == '0')
        break;

    sprintf(buffer, "%s\n", linha);
    free(linha);
    campo_envia(buffer);
  }

  free(buffer);
}