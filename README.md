# Trabalho Final PDS1

Este é um programa em C que realiza o cálculo da rota de menor custo em um sistema de transporte urbano. O programa lê três arquivos de entrada: `distancia.txt`, `criminalidade.txt` e `transito.txt`, que contêm informações sobre a distância entre os pontos, o nível de criminalidade e o nível de trânsito de cada rota, respectivamente.

## Funcionalidades

O programa possui as seguintes funcionalidades:

- Leitura dos arquivos de entrada e criação das matrizes de distância, criminalidade, trânsito e custo.
- Impressão das matrizes no terminal.
- Cálculo da rota de menor custo.

## Como executar

1. Certifique-se de ter um compilador C instalado em seu sistema.
2. Abra o terminal e navegue até o diretório onde se encontra o arquivo `trabalho_final.c`.
3. Compile o programa executando o seguinte comando: `gcc trabalho_final.c -o trabalho_final`.
4. Execute o programa com o comando: `./trabalho_final`.

## Arquivos de entrada

Os arquivos de entrada devem estar no mesmo diretório do programa e seguir o seguinte formato:

- `distancia.txt`: cada linha contém três valores separados por vírgula: linha, coluna e valor da distância.
- `criminalidade.txt`: cada linha contém três valores separados por vírgula: linha, coluna e valor da criminalidade.
- `transito.txt`: cada linha contém três valores separados por vírgula: linha, coluna e valor do trânsito.

## Resultado

O programa imprimirá no terminal as matrizes de distância, criminalidade, trânsito e custo, além da rota de menor custo encontrada.

