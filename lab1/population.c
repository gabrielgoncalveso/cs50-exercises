#include <stdio.h>
#include <cs50.h>

int main(void)
{

    // TODO: Solicite o valor inicial ao usuário

    int populacao_inicial;
    do
    {
        populacao_inicial = get_int("Start size: ");
    }
    while (populacao_inicial < 9);

    // TODO: Solicite o valor final ao usuário

    int populacao_final;
    do
    {
        populacao_final = get_int("End size: ");
    }
    while (populacao_final < populacao_inicial);

    // TODO: Calcule o número de anos até o limite
    int anos = 0;
    while (populacao_inicial < populacao_final)
    {
        int novas = (int) populacao_inicial / 3;
        int mortes = (int) populacao_inicial / 4;
        int crescimento = novas - mortes;

        populacao_inicial += crescimento;
        anos++;
    }

    // TODO: Imprima o número de anos
    printf("Years: %i\n", anos);

}