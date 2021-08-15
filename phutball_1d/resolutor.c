#include "marIA.h"
#include "campo.h"

int main(int argc, char **argv) {
  char *buffer = criaString();
  char *linha;
  
  campo_conecta(argc, argv);

  while(1) {
    campo_recebe(buffer);
    //printf("%s", buffer);
    linha = resolve(buffer);
    if(linha[0] == '0')
      break;
      
    printf("linha: %s\n", linha);

    sprintf(buffer, "%s\n", linha);
    free(linha);
    campo_envia(buffer);
  }

  free(buffer);
}