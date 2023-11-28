#include <stdio.h>
#include <math.h>

#define MAX 20
#define PONTOS 5

// Deixei uma função só pra criar as 3 matrizes - Henrique
void criarMatriz(FILE *arquivo, int matriz[MAX][MAX])
{
    int linha;
    int coluna;
    int valor;

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            matriz[i][j] = -1;
        }
    }

    if (arquivo != NULL)
    {
        while (fscanf(arquivo, "%d,%d,%d", &linha, &coluna, &valor) == 3)
        { // Aqui tava mei estranho nem sei o que tu tava fazendo mas corrigi colocando na variavel valor que tu criou --kiki
            matriz[linha][coluna] = valor;
        }
    }
    else
    {
        printf("Não foi possivel abrir o arquivo.");
    }
    fclose(arquivo);
}

// Função para imprimir as matrizes e evitar muitas linhas de código na main - Henrique
void ImprimirMatriz(int n, int matriz[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para gerar a matriz custo - Henrique
void criarMatrizCusto(int matrizD[MAX][MAX], int matrizCr[MAX][MAX], int matrizT[MAX][MAX], int matrizC[MAX][MAX])
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (matrizD[i][j] != -1 && matrizT[i][j] != -1 && matrizCr[i][j] != -1)
            {
                // Formula do professor - Henrique
                matrizC[i][j] = ((matrizD[i][j]) * (matrizD[i][j])) + matrizT[i][j] + (2 * (matrizCr[i][j]));
            }
            else
            {
                // Quando não existe rota - Henrique
                matrizC[i][j] = -1;
            }
        }
    }
}

// Função para gerar a matriz só com os pontos da rota - Henrique
void criarMatrizPontos(int pontos[PONTOS], int matrizCusto[MAX][MAX], int matrizRota[PONTOS][PONTOS])
{
    for (int i = 0; i < PONTOS; i++)
    {
        for (int j = 0; j < PONTOS; j++)
        {
            matrizRota[i][j] = matrizCusto[pontos[i - 1]][pontos[j - 1]];
        }
    }
}

// Função para calcular melhor rota - Henrique
void calcularRota(int matriz[PONTOS][PONTOS], int valorRota[PONTOS - 1], int rota[PONTOS])
{
    int menorValor = 999999;
    int indiceMenorValor[2];
    int contador = 0;
    int contador2 = 0;
    int soma1 = 0;
    int soma2 = 0;
    int matrizReserva[PONTOS][PONTOS];
    int valorRotaTemp[PONTOS - 1];
    int rotaTemp[PONTOS];

    // Deixa a matriz reserva igual a matriz original para trocar no futuro
    for (int i = 0; i < PONTOS; i++)
    {
        for (int j = 0; j < PONTOS; j++)
        {
            matrizReserva[i][j] = matriz[i][j];
        }
    }

    printf("Calculando melhor rota...\n");

    while (contador2 < PONTOS)
    {
        // Deixa a matriz a ser analisada igual a matriz original usando a reserva
        for (int i = 0; i < PONTOS; i++)
        {
            for (int j = 0; j < PONTOS; j++)
            {
                matriz[i][j] = matrizReserva[i][j];
            }
        }

        ImprimirMatriz(PONTOS, matriz);

        // Pega um ponto inicial i, que começa no 0 e sobe 1 a cada while
        for (int i = contador2; i < PONTOS; i++)
        {
            // Roda por todos os valores da linha
            for (int j = 0; j < PONTOS; j++)
            {
                // Acha o menor valor, armazena ele e os indices
                if (matriz[j][i] < menorValor && matriz[j][i] > 0)
                {
                    menorValor = matriz[j][i];
                    indiceMenorValor[0] = j;
                    indiceMenorValor[1] = i;
                }
            }

            // Armazena o valor do primeiro custo
            valorRotaTemp[contador] = menorValor;
            if (contador != PONTOS - 2)
            {
                rotaTemp[contador] = indiceMenorValor[0];
            }
            else
            {
                rotaTemp[contador] = indiceMenorValor[0];
                rotaTemp[contador + 1] = indiceMenorValor[1];
            }

            // Reseta o menorValor
            menorValor = 99999;

            // Apaga os valores do ponto já utilizado
            for (int z = 0; z < PONTOS; z++)
            {
                matriz[indiceMenorValor[1]][z] = -1;
                matriz[z][indiceMenorValor[1]] = -1;
            }

            ImprimirMatriz(PONTOS, matriz);

            // Coloca que a proxima coluna é o valor da ultima linha
            i = indiceMenorValor[0] - 1;

            // Para parar quando tiver rodado a quantidade suficiente
            contador++;
            if (contador == PONTOS - 1)
            {
                i = PONTOS;
            }
        }

        // Soma os valores dos custos
        for (int i = 0; i < PONTOS - 1; i++)
        {
            soma1 += valorRotaTemp[i];
        }

        printf("Soma: %d\n\n", soma1);

        // Substitui se for o novo menor
        if (soma1 < soma2 || soma2 == 0)
        {
            soma2 = soma1;
            for (int i = 0; i < PONTOS - 1; i++)
            {
                valorRota[i] = valorRotaTemp[i];
            }
            for (int i = 0; i < PONTOS; i++)
            {
                rota[i] = rotaTemp[i];
            }
        }

        // Reseta o soma1
        soma1 = 0;
        // Aumenta o contador do while
        contador2++;

        // Reseta o contador do for
        contador = 0;
    }
    printf("Soma: %d\n", soma2);
}

int main()
{
    int matrizDistancia[MAX][MAX];
    int matrizCriminalidade[MAX][MAX];
    int matrizTransito[MAX][MAX];
    int matrizCusto[MAX][MAX];
    int valorRota[PONTOS - 1];
    int rota[PONTOS];
    int pontos[PONTOS] = {1, 2, 3, 4, 5};
    int matrizRota[PONTOS][PONTOS];
    FILE *distancia;
    FILE *crime;
    FILE *transito;

    distancia = fopen("distancia.txt", "r");
    crime = fopen("criminalidade.txt", "r");
    transito = fopen("transito.txt", "r");

    // Criar matrizes - Henrique
    criarMatriz(distancia, matrizDistancia);
    criarMatriz(crime, matrizCriminalidade);
    criarMatriz(transito, matrizTransito);
    criarMatrizCusto(matrizDistancia, matrizCriminalidade, matrizTransito, matrizCusto);
    criarMatrizPontos(pontos, matrizCusto, matrizRota);

    // Imprimindo as matrizes para teste - Henrique
    printf("Matriz de Distancia: \n");
    ImprimirMatriz(MAX, matrizDistancia);
    printf("Matriz de Criminalidade: \n");
    ImprimirMatriz(MAX, matrizCriminalidade);
    printf("Matriz de Transito: \n");
    ImprimirMatriz(MAX, matrizTransito);
    printf("Matriz Custo: \n");
    ImprimirMatriz(MAX, matrizCusto);
    printf("Matriz Rota: \n");
    ImprimirMatriz(PONTOS, matrizRota);

    calcularRota(matrizRota, valorRota, rota);

    printf("Rota: ");
    for (int i = 0; i < PONTOS ; i++)
    {
        printf(" %d", rota[i]);
    }
    
    return 0;
}