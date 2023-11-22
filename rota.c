#include <stdio.h>

#define MAX 20

void lerDistancia()
{
    int linha;
    int coluna;
    int valor;
    int matriz[MAX][MAX];
    FILE *distancia;

    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            matriz[i][j] = -1;
        }
    }


    distancia = fopen("distancia.txt", "r");

    if (distancia != NULL)
    {
        while (fscanf(distancia, "%d, %d, %d", & &distanciaVetor) == 3)
        {
            printf("%d", distanciaVetor);
        }
    }
    else
    {
        printf("Not able to open the file.");
    }
    fclose(distancia);
}

int main()
{
    lerDistancia();

    return 0;
}