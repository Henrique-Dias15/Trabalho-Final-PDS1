#include <stdio.h>

#define MAX 20
//Caso a gente for mexer com a matriz acho dhr a gente pedir ela na main pra ficar uma matriz na main pra gente poder mexer nas funcoes depois -kiki
void lerDistancia(int matrizdistancia[MAX][MAX])
{
    int linha;
    int coluna;
    int valor;
    FILE *distancia;

    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            matrizdistancia[i][j] = -1;
        }
    }

    //O arquivo txt tem que estar na mesma pasta que o exe, o meu vscode gera ele na pasta output. -kiki
    distancia = fopen("distancia.txt", "r");

    if (distancia != NULL)
    {
        while (fscanf(distancia, "%d,%d,%d", &linha, &coluna, &valor) == 3)
        {   //Aqui tava mei estranho nem sei o que tu tava fazendo mas corrigi colocando na variavel valor que tu criou --kiki
            matrizdistancia[linha][coluna] = valor;
        }
    }
    else
    {
        printf("Not able to open the file.");
    }
    fclose(distancia);

}



int main(){
    //Criei a matriz na main pra poder mexer com ela mais tarde em outras funções -kiki
    int matrizdistancia[MAX][MAX];

    lerDistancia(matrizdistancia);

    //printando so pra conferir se a matriz ta certa -kiki
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%d ", matrizdistancia[i][j]);
        }
        printf("\n");
    }

    return 0;
}