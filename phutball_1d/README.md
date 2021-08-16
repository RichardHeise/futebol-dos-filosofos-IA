# Jogador automático do jogo futebol dos filósofos unidimensional (Inteligência Artifical)

## Aviso:
- Recomendo ler esse README.md usando uma ferramenta de leitura de MarkDown (https://stackedit.io/app#, por exemplo). Se desejar, também pode ler diretamente de meu github em https://github.com/RichardHeise/futebol-dos-filosofos-IA, que estará público após o dia 15/08/2021 para evitar possíveis problemas com plágio. Boa leitura.

## Descrição:
 - Este trabalho se propõe acriar um jogador automático que joga de ambos os lados (esquerdo e direito) em uma partida de futebol de filósofos em um campo de uma dimensão.

## O Problema
 - Devido a natureza do jogo ser simples, porém com um alto número de possibilidade, implementamos uma IA que segue os padrões MINMAX a fim de minimizar a chance de nosso oponente chegar no máximo de sua chance de vitória. 

## Código
 ### O código fonte possui cinco bibliotecas locais: esquerda.h, direita.h, uteis.h, campo.h e marIAlib.h. 
 - Em esquerda.h você encontrará as funções que lidam com a porção esquerda da bola no campo.
 - Em direita.h você encontrará as funções que lidam com a porção direita da bola no campo.
 - Em uteis.h você encontrará as funções úteis, que servem para nos ajudar a resolver um estado do jogo.
 - Em campo.h você encontrará funções de conexão ao servidor redis.
 - Em marIAlib.h você encontrará as funções que decidem o que deve ser chamado para jogar a partida. 

 ### Anatomia do código
 - marIA.c possui as implementações da IA.
 - uteis.c possui as implementações úteis para o problema.
 - marIAlib.c possui as implementações a decisão de qual jogador jogará.
 - esquerda.c possui as implementações referentes à esquerda do campo em relação a bola.
 - direita.c possui as implementações referentes à direita do campo em relação a bola.
 - marIA.c é somente nossa main.
 - Makefile é o arquivo de configuração make, para compilar o código.
 - README.md este arquivo.

## Fluxo
 - É passado para nós uma string com o campo e informações úteis para que possamos interpretar o campo. Pegamos essas informações e fazemos a decomposição do que foi recebido. Em seguinda, verificamos se estamos na direita ou na esquerda e jogamos de acordo com o lado. 
 - Tudo que vale para um lado vale, também, para o outro.
 - Primeiramente fazemos uma jogada, em seguidaa, executamos todas as jogadas possíveis de nosso oponente, tanto filósofos quanto chutes, a fim de descobrir qual jogada do nosso oponente nos deixará mais distante da vitória. Ou seja, passamos cada campo alterado pela nossa jogada e pela jogada do oponente para uma heurística que nos diz quão longe ficaremos de ganhar. Selecionamos a jogada que nos deixa mais perto da vitória considerando que o oponente fará a melhor jogada possível de acordo com nossa heurística.

## Heurística 
  - Simplesmente verificamos quantas jogadas estamos de ganhar se nosso oponente "não fizer nada". Isto é, em dada posição, quantos filósofos e chutes precisamos fazer para chegar na vitória. Temos uma heurística para cada lado que funciona de forma espelhada.

## Considerações finais
  - Use o comando make para compilar, make clean limpa os .o e make purge limpa todo executável e .o gerado.
  - É preciso ter o redis instalado na sua máquina, bem como a libhiredis-dev e libreadline-dev.
  - É rotineiro o servidor acabar contaminado com jogadas anteriores, tome cuidado para garantir que o que está sendo jogado está condizente.
  - Nas máquinas que testamos, acabou acontecendo um bug em relação ao server que não nos deixou jogar nossa IA contra ela mesma mais de uma vez (ou seja, tinhamos que reiniciar o servidor sempre que queríamos testar os lances).

## Para rodar
  - Basta usar o comando make, fazer _./marIA_ **e** ou _./marIA_ **d** com o controlador de pé e o servidor rodando.

#### Autor
 - Feito com carinho, esforço e força de vontade por Richard Fernando Heise Ferreira (rfhf19@inf.ufpr.br) e Carlos Iago Bueno (cib19@inf.ufpr.br) para a disciplina de Inteligência Artifical, ministrada durante o ERE de 2021 devido à pandemia. Espero que goste :) CCQL
