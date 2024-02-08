# Trabalho-Final-PDS1

## Rota de Menor Custo

Este programa em C calcula a rota de menor custo em um mapa, considerando distância, trânsito e criminalidade. O mapa é representado por matrizes, onde cada célula representa um ponto e o valor na célula representa o custo para chegar a esse ponto.

## Como funciona

O programa começa declarando matrizes para distância, criminalidade, trânsito e custo.

Em seguida, ele abre três arquivos de texto que contêm os dados para distância, criminalidade e trânsito.

O programa então chama a função criarMatriz para cada arquivo, que lê os dados do arquivo e preenche a matriz correspondente.

A função criarMatrizCusto é chamada para calcular a matriz de custo com base nas matrizes de distância, criminalidade e trânsito.

As matrizes são impressas no terminal para verificação.

A função rota é chamada para calcular a rota de menor custo usando a matriz de custo. Esta função usa um algoritmo de busca exaustiva, testando todas as possíveis rotas e mantendo a de menor custo.

Finalmente, a rota de menor custo é impressa no terminal.

## Pré-requisitos

Este código assume que os arquivos de entrada estão no formato correto e que não há erros nos dados. Se os arquivos não puderem ser abertos ou se houver um erro na leitura dos dados, o programa imprimirá uma mensagem de erro e terminará.

## Como executar

Para executar este programa, você precisa ter um compilador C instalado em seu sistema. Compile o arquivo rota.c e execute o binário gerado.

## Contribuindo

Pull requests são bem-vindos. Para mudanças importantes, por favor, abra uma issue primeiro para discutir o que você gostaria de mudar.

Por favor, certifique-se de atualizar os testes conforme apropriado.
