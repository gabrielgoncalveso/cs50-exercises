#include <stdio.h>
#include <cs50.h>

void imprimir_degraus(int n);

int obter_int_positivo(void);

int main(void)
{
    int numero_degraus = obter_int_positivo();

    imprimir_degraus(numero_degraus);
}

void imprimir_degraus(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = n; j > 0; j--)
        {
            if (j > i + 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}

int obter_int_positivo(void)
{
    int n;
    do
    {
        n = get_int("Insira o número de degraus (entre 1 e 8): ");
    }
    while (n < 1 || n > 8);
    return n;
}