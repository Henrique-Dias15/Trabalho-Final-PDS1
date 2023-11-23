#include <stdio.h>

#define MAX 20
// Deixei uma função só pra criar as 3 matrizes - Henrique
void criarMatriz(FILE *arquivo, int matrizdistancia[MAX][MAX])
{
    int linha;
    int coluna;
    int valor;

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            matrizdistancia[i][j] = -1;
        }
    }

    if (arquivo != NULL)
    {
        while (fscanf(arquivo, "%d,%d,%d", &linha, &coluna, &valor) == 3)
        { // Aqui tava mei estranho nem sei o que tu tava fazendo mas corrigi colocando na variavel valor que tu criou --kiki
            matrizdistancia[linha][coluna] = valor;
        }
    }
    else
    {
        printf("Não foi possivel abrir o arquivo.");
    }
    fclose(arquivo);
}

int main()
{
    // Criei a matriz na main pra poder mexer com ela mais tarde em outras funções -kiki
    int matrizdistancia[MAX][MAX];
    int matrizcriminalidade[MAX][MAX];
    int matriztransito[MAX][MAX];
    FILE *distancia;
    FILE *crime;
    FILE *transito;

    distancia = fopen("distancia.txt", "r");
    crime = fopen("criminalidade.txt", "r");
    transito = fopen("transito.txt", "r");

    criarMatriz(distancia, matrizdistancia);
    criarMatriz(crime, matrizcriminalidade);
    criarMatriz(transito, matriztransito);

    // printando so pra conferir se a matriz ta certa -kiki
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%d ", matrizdistancia[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    // printando so pra conferir se a matriz ta certa -kiki
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%d ", matrizcriminalidade[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    // printando so pra conferir se a matriz ta certa -kiki
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%d ", matriztransito[i][j]);
        }
        printf("\n");
    }

    return 0;
}