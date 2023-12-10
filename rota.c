#include <stdio.h>

#define MAX 20
#define NOT_VISITED -1
#define INFINITY 99999

// Função para gerar as matrizes dos arquivos .txt
void criarMatriz(FILE *arquivo, int matriz[MAX][MAX])
{
    int linha, coluna, valor;

    // Preenche a matriz com -1
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            matriz[i][j] = NOT_VISITED;
        }
    }

    // Analisa se o arquivo foi aberto ou não
    if (arquivo != NULL)
    {
        // Cria a matriz partindo dos valores no arquivo .txt seguindo a lógica (linha, coluna, valor)
        while (fscanf(arquivo, "%d,%d,%d", &linha, &coluna, &valor) == 3)
        {
            matriz[linha][coluna] = valor;
        }
    }
    else
    {
        printf("Não foi possível abrir o arquivo.");
    }
    fclose(arquivo);
}

// Função para imprimir no terminal as matrizes
void ImprimirMatriz(int matriz[MAX][MAX])
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%4d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para criar a matriz custo partindo das matrizes distancia, transito e criminalidade
void criarMatrizCusto(int matrizD[MAX][MAX], int matrizCr[MAX][MAX], int matrizT[MAX][MAX], int matrizC[MAX][MAX])
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            // Ignora as rotas inexistentes, que valem -1
            if (matrizD[i][j] != NOT_VISITED && matrizT[i][j] != NOT_VISITED && matrizCr[i][j] != NOT_VISITED)
            {
                // Calculo em ordem de prioridade: distancia, transito e criminalidade
                matrizC[i][j] = (3 * (matrizD[i][j])) + (3 * (matrizCr[i][j])) + (2 * (matrizT[i][j]));
            }
            else
            {
                matrizC[i][j] = NOT_VISITED;
            }
        }
    }
}

// Função para calcular a rota de menor curso partindo da matriz custo
void rota(int matriz[MAX][MAX])
{
    int contadorExterno = 0;
    int linha = 0;
    int proxLinha = 0;
    int menor = INFINITY;
    int valoresTemp[MAX - 1];
    int valores[MAX - 1];
    int contadorInterno = 0;
    int pontosTemp[MAX];
    int pontos[MAX];
    int somaTemp = 0;
    int soma = 0;
    int matrizTemp[MAX][MAX];

    // Cria uma matriz temporaria igual a matriz custo original
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            matrizTemp[i][j] = matriz[i][j];
        }
    }

    // While para testar possiblidades partindo de todos os pontos
    while (contadorExterno < MAX)
    {
        printf("\nCalculando melhor rota partindo do ponto %2d...\n", contadorExterno + 1);

        // Avança a linha inicial
        linha = contadorExterno;

        // Reseta a matriz a ser analisada
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                matriz[i][j] = matrizTemp[i][j];
            }
        }

        // While para varrer a matriz inteira
        while (contadorInterno < MAX - 1)
        {
            // Roda por todos os valores em uma linha
            for (int i = 0; i < MAX; i++)
            {
                // Acha o menor valor daquela linha e armazena, além de armazenar o valor da coluna desse valor, que será a proxima linha a ser analisada
                if (matriz[linha][i] != NOT_VISITED && matriz[linha][i] < menor)
                {
                    menor = matriz[linha][i];
                    proxLinha = i;
                }
            }

            // Descarta o ponto já utilizado igualando todos seus valores a -1
            for (int i = 0; i < MAX; i++)
            {
                matriz[linha][i] = matriz[i][linha] = NOT_VISITED;
            }

            // Armazena os pontos passados para gerar a rota
            pontosTemp[contadorInterno] = linha;
            if (contadorInterno == MAX - 2)
            {
                pontosTemp[contadorInterno + 1] = proxLinha;
            }

            // Armazena o menor valor
            valoresTemp[contadorInterno] = menor;

            // Gera o custo total temporario da rota
            somaTemp += menor;

            // Usa o valor da coluna com o menor valor para passar na proxima linha, gerando assim uma rota consecutiva de pontos
            linha = proxLinha;

            // Reseta o valor "menor" e aumenta o contador interno
            menor = INFINITY;
            contadorInterno++;
        }

        // Imprimir os valores do ultimo teste
        printf("Tamanho da menor rota partindo de %d: %d\n", contadorExterno + 1, somaTemp);
        printf("Valores da menor rota partindo de %d: ", contadorExterno + 1);
        for (int i = 0; i < MAX - 1; i++)
        {
            printf("%3d ", valoresTemp[i] + 1);
        }
        printf("\nPontos da menor rota partindo de %d: ", contadorExterno + 1);
        for (int i = 0; i < MAX; i++)
        {
            printf("%2d ", pontosTemp[i] + 1);
        }
        printf("\n");

        // Aumenta o contador externo e reseta o interno
        contadorExterno++;
        contadorInterno = 0;

        // Confere se essa rota foi mais eficiente que a anterior e, caso seja, tranforma na atual melhor rota
        if (somaTemp < soma || soma == 0)
        {
            soma = somaTemp;
            for (int i = 0; i < MAX - 1; i++)
            {
                valores[i] = valoresTemp[i];
            }
            for (int i = 0; i < MAX; i++)
            {
                pontos[i] = pontosTemp[i];
            }
        }

        // Reseta o custo temporario
        somaTemp = 0;
    }

    // Imprime os resultados da melhor rota encontrada
    printf("\nCalculado rota de menor custo: \n");
    printf("Custo: %d\n", soma);
    printf("Valores: ");
    for (int i = 0; i < MAX - 1; i++)
    {
        printf("%3d ", valores[i] + 1);
    }
    printf("\nRota: ");
    for (int i = 0; i < MAX; i++)
    {
        printf("%2d ", pontos[i] + 1);
    }
}

int main()
{
    // Declarar as matrizes que vão ser usadas
    int matrizDistancia[MAX][MAX];
    int matrizCriminalidade[MAX][MAX];
    int matrizTransito[MAX][MAX];
    int matrizCusto[MAX][MAX];

    // Abrir os arquivos .txt necessarios
    FILE *distancia;
    FILE *crime;
    FILE *transito;

    distancia = fopen("distancia.txt", "r");
    crime = fopen("criminalidade.txt", "r");
    transito = fopen("transito.txt", "r");

    // Criar as matrizes distancia, crime e transito
    criarMatriz(distancia, matrizDistancia);
    criarMatriz(crime, matrizCriminalidade);
    criarMatriz(transito, matrizTransito);
    criarMatrizCusto(matrizDistancia, matrizCriminalidade, matrizTransito, matrizCusto);

    // Imprimir as matrizes no terminal
    printf("Matriz de Distancia: \n");
    ImprimirMatriz(matrizDistancia);
    printf("Matriz de Criminalidade: \n");
    ImprimirMatriz(matrizCriminalidade);
    printf("Matriz de Transito: \n");
    ImprimirMatriz(matrizTransito);
    printf("Matriz custo: \n");
    ImprimirMatriz(matrizCusto);

    // Calcular a rota
    rota(matrizCusto);

    // Encerrar programa
    return 0;
}
