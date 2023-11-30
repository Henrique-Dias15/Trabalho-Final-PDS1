#include <stdio.h>

#define MAX 20
#define NOT_VISITED -1
#define INFINITY 99999

void criarMatriz(FILE *arquivo, int matriz[MAX][MAX]) {
    int linha, coluna, valor;

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matriz[i][j] = NOT_VISITED;
        }
    }

    if (arquivo != NULL) {
        while (fscanf(arquivo, "%d,%d,%d", &linha, &coluna, &valor) == 3) {
            matriz[linha][coluna] = valor;
        }
    } else {
        printf("Não foi possível abrir o arquivo.");
    }
    fclose(arquivo);
}

void ImprimirMatriz(int matriz[MAX][MAX]) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void criarMatrizCusto(int matrizD[MAX][MAX], int matrizCr[MAX][MAX], int matrizT[MAX][MAX], int matrizC[MAX][MAX]) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (matrizD[i][j] != NOT_VISITED && matrizT[i][j] != NOT_VISITED && matrizCr[i][j] != NOT_VISITED) {
                matrizC[i][j] = ((matrizD[i][j]) * (matrizD[i][j])) + matrizT[i][j] + (2 * (matrizCr[i][j]));
            } else {
                matrizC[i][j] = NOT_VISITED;
            }
        }
    }
}

void rota(int matriz[MAX][MAX]) {
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

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matrizTemp[i][j] = matriz[i][j];
        }
    }

    while (contadorExterno < MAX) {
        linha = contadorExterno;
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                matriz[i][j] = matrizTemp[i][j];
            }
        }

        while (contadorInterno < MAX - 1) {
            for (int i = 0; i < MAX; i++) {
                if (matriz[linha][i] != NOT_VISITED && matriz[linha][i] < menor) {
                    menor = matriz[linha][i];
                    proxLinha = i;
                }
            }

            for (int i = 0; i < MAX; i++) {
                matriz[linha][i] = matriz[i][linha] = NOT_VISITED;
            }

            pontosTemp[contadorInterno] = linha;
            if (contadorInterno == MAX - 2) {
                pontosTemp[contadorInterno + 1] = proxLinha;
            }

            linha = proxLinha;
            valoresTemp[contadorInterno] = menor;
            somaTemp += menor;
            menor = INFINITY;
            contadorInterno++;
        }

        contadorExterno++;
        contadorInterno = 0;
        if (somaTemp < soma || soma == 0) {
            soma = somaTemp;
            for (int i = 0; i < MAX - 1; i++) {
                valores[i] = valoresTemp[i];
            }
            for (int i = 0; i < MAX; i++) {
                pontos[i] = pontosTemp[i];
            }
        }
        somaTemp = 0;
    }

    printf("Soma: %d\n", soma);
    printf("Valores: ");
    for (int i = 0; i < MAX - 1; i++) {
        printf("%d ", valores[i] + 1);
    }
    printf("\nRota: ");
    for (int i = 0; i < MAX; i++) {
        printf("%d ", pontos[i] + 1);
    }
}

int main() {
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

    printf("Matriz de Distancia: \n");
    ImprimirMatriz(matrizDistancia);
    printf("Matriz de Criminalidade: \n");
    ImprimirMatriz(matrizCriminalidade);
    printf("Matriz de Transito: \n");
    ImprimirMatriz(matrizTransito);

    criarMatrizCusto(matrizDistancia, matrizCriminalidade, matrizTransito, matrizCusto);

    printf("Matriz custo: \n");
    ImprimirMatriz(matrizCusto);

    rota(matrizCusto);

    fclose(distancia);
    fclose(crime);
    fclose(transito);

    return 0;
}
