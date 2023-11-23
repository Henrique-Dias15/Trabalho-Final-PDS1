#include <stdio.h>

#define MAX 20
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
void ImprimirMatriz(int matriz[MAX][MAX])
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
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

// Função para calcular melhor rota - Henrique
void calcularRota(int matriz[MAX][MAX])
{
    int valorRota[MAX];
    int menorValor = 999999;
    int indiceMenorValor[2];
    int contador = 0;
    int k = 0;

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (matriz[j][i] < menorValor && matriz[j][i] > 0)
            {
                menorValor = matriz[j][i];
                indiceMenorValor[1] = j;
                indiceMenorValor[2] = i;
            }
        }

        printf("Linha = %d \nColuna = %d \nMenor valor: %d\n", indiceMenorValor[1], indiceMenorValor[2], menorValor);
        menorValor = 99999999;

        for (int z = 0; z < MAX; z++)
        {
            matriz[indiceMenorValor[2]][z] = -1;
            matriz[z][indiceMenorValor[2]] = -1;
        }
        printf("\n");
        ImprimirMatriz(matriz);
        i = indiceMenorValor[1] - 1;
    }
}

int main()
{
    int matrizDistancia[MAX][MAX];
    int matrizCriminalidade[MAX][MAX];
    int matrizTransito[MAX][MAX];
    int matrizCusto[MAX][MAX];
    FILE *distancia;
    FILE *crime;
    FILE *transito;

    distancia = fopen("distancia.txt", "r");
    crime = fopen("criminalidade.txt", "r");
    transito = fopen("transito.txt", "r");

    criarMatriz(distancia, matrizDistancia);
    criarMatriz(crime, matrizCriminalidade);
    criarMatriz(transito, matrizTransito);

    // Imprimindo as matrizes para teste - Henrique
    printf("Matriz de Distancia: \n");
    ImprimirMatriz(matrizDistancia);
    printf("Matriz de Criminalidade: \n");
    ImprimirMatriz(matrizCriminalidade);
    printf("Matriz de Transito: \n");
    ImprimirMatriz(matrizTransito);

    // Criar matriz custo - Henrique
    criarMatrizCusto(matrizDistancia, matrizCriminalidade, matrizTransito, matrizCusto);

    // Imprimir matriz custo para teste - Henrique
    printf("Matriz custo: \n");
    ImprimirMatriz(matrizCusto);

    calcularRota(matrizCusto);

    return 0;
}