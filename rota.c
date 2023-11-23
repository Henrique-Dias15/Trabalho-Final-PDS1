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

int main()
{
    int matrizDistancia[MAX][MAX];
    int matrizCriminalidade[MAX][MAX];
    int matrizTransito[MAX][MAX];
    FILE *distancia;
    FILE *crime;
    FILE *transito;

    distancia = fopen("distancia.txt", "r");
    crime = fopen("criminalidade.txt", "r");
    transito = fopen("transito.txt", "r");

    criarMatriz(distancia, matrizDistancia);
    criarMatriz(crime, matrizCriminalidade);
    criarMatriz(transito, matrizTransito);

    // Imprimindo as matrizes para teste
    printf("Matriz de Distancia: \n");
    ImprimirMatriz(matrizDistancia);
    printf("Matriz de Criminalidade: \n");
    ImprimirMatriz(matrizCriminalidade);
    printf("Matriz de Transito: \n");
    ImprimirMatriz(matrizTransito);

    return 0;
}