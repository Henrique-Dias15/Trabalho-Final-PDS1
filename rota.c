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
        printf("Não foi possivel abrir o arquivo.");
    }
    fclose(distancia);

}
//So copiei o de cima e mudei o nome pra ler a criminalidade -kiki
void lerCrime(int matriz[MAX][MAX])
{
    int linha;
    int coluna;
    int valor;
    FILE *criminalidade;

    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            matriz[i][j] = -1;
        }
    }

    criminalidade = fopen("criminalidade.txt", "r");

    if (criminalidade != NULL)
    {
        while (fscanf(criminalidade, "%d,%d,%d", &linha, &coluna, &valor) == 3){ 
            matriz[linha][coluna] = valor;
        }
    }
    else
    {
        printf("Não foi possivel abrir o arquivo.");
    }
    fclose(criminalidade);

}
//so copiei o de cima e mudei o nome pra ler o transito -kiki
void lertransito(int matriz[MAX][MAX])
{
    int linha;
    int coluna;
    int valor;
    FILE *transito;

    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            matriz[i][j] = -1;
        }
    }

    transito = fopen("transito.txt", "r");

    if (transito != NULL)
    {
        while (fscanf(transito, "%d,%d,%d", &linha, &coluna, &valor) == 3){ 
            matriz[linha][coluna] = valor;
        }
    }
    else
    {
        printf("Não foi possivel abrir o arquivo.");
    }
    fclose(transito);

}



int main(){
    //Criei a matriz na main pra poder mexer com ela mais tarde em outras funções -kiki
    int matrizdistancia[MAX][MAX];
    int matrizcriminalidade[MAX][MAX];
    int matriztransito[MAX][MAX];

    lerDistancia(matrizdistancia);
    lerCrime(matrizcriminalidade);
    lertransito(matriztransito);

    //printando so pra conferir se a matriz ta certa -kiki
    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++)
        {
            printf("%d ", matrizdistancia[i][j]);
        }
        printf("\n");
    }



    return 0;
}