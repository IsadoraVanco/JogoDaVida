# Jogo da Vida

O Jogo da Vida (_The Game of Life_ - John Conway/1970) é um exemplo de “_zero-player game_” (ou jogo de simulação). O jogo consiste de um quadro bi-dimensional com dimensões infinitas, esse quadro é dividido em células, cada célula pode apresentar status de “viva” ou “morta” em cada geração. O jogo apresenta regras que determinam o status de cada célula na próxima geração. Sua função é descrever o status de cada célula em uma sequência de gerações.

O status da célula em sua próxima geração é determinado pelo status das céluas vizinhas na geração atual. Considere um quadro com dimensões 30x30. O conjunto de regras é descrito a seguir:

* Uma célula viva com menos que dois vizinhos vivos, morre na próxima geração;
* Uma célula viva com mais de três vizinho vivos também morre;
* Uma célula viva com exatamente dois ou três vizinhos vivos, também vive;
* Uma célula morta com exatamente 3 vizinho vivos, torna-se viva.

Como estamos trabalhando em um espaço finito, uma célula posicionada fora do quadro é considerada morta.

1. Considerando 1 como vivo e 0 como morto, faça a leitura de um arquivo texto com a mesma dimensão do quadro (30x30), e a leitura da quantidade de gerações a serem simuladas. 
2. Realize a simulação da quantidade de gerações, fazendo um intervalo de tempo entre cada uma.
3. O nome do arquivo texto e a quantidade de gerações são parâmetros de entrada do programa.
4. Utilizar funções e ponteiros em seu código.