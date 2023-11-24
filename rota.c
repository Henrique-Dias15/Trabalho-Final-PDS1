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
void calcularRota(int matriz[MAX][MAX], int valorRota[MAX - 1])
{
    int menorValor = 999999;
    int indiceMenorValor[2];
    int contador = 0;
    int contador2 = 0;
    int soma1 = 0;
    int soma2 = 0;
    int matrizReserva[MAX][MAX];

    // Deixa a matriz reserva igual a matriz original para trocar no futuro
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            matrizReserva[i][j] = matriz[i][j];
        }        
    }

    while (contador2 < MAX)
    {
        // Deixa a matriz a ser analisada igual a matriz original usando a reserva
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                matriz[i][j] = matrizReserva[i][j];
            }
        }

        // Pega um ponto inicial i, que começa no 0 e sobe 1 a cada while
        for (int i = contador2; i < MAX; i++)
        {
            // Roda por todos os valores da linha
            for (int j = 0; j < MAX; j++)
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
            valorRota[contador] = menorValor;

            // Reseta o menorValor
            menorValor = 99999;

            // Apaga os valores do ponto já utilizado
            for (int z = 0; z < MAX; z++)
            {
                matriz[indiceMenorValor[1]][z] = -1;
                matriz[z][indiceMenorValor[1]] = -1;
            }

            // Coloca que a proxima coluna é o valor da ultima linha  
            i = indiceMenorValor[0] - 1;

            // Para parar quando tiver rodado a quantidade suficiente
            contador++;
            if (contador == MAX - 1)
            {
                i = 20;
            }
        }

        // Soma os valores dos custos
        for (int i = 0; i < MAX; i++)
        {
            soma1 += valorRota[i];
        }

        // Substitui se for o novo menor
        if (soma1 < soma2 || soma2 == 0)
        {
            soma2 = soma1;
        }
            printf("if");


        // Reseta o soma1
        soma1 = 0;
        // Aumenta o contador do while
        contador2 ++;

        // Reseta o contador do for
        contador = 0;
    }
    printf("PAROU O WHILE!!!\n");
    printf("Soma: %d\n", soma2);
}

int main()
{
    int matrizDistancia[MAX][MAX];
    int matrizCriminalidade[MAX][MAX];
    int matrizTransito[MAX][MAX];
    int matrizCusto[MAX][MAX];
    int valorRota[MAX - 1];
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

    calcularRota(matrizCusto, valorRota);

    printf("Valor rota: ");
    for (int i = 0; i < MAX - 1; i++)
    {
        printf("%d ", valorRota[i]);
    }
    printf("\n");

    return 0;
}