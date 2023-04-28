#include <stdio.h>
#include <cs50.h>
#include <math.h>

float obter_real_positivo(void);

int main(void)
{
    float reais = obter_real_positivo();
    int centavos = round(reais * 100);
    int quantidade_moedas = 0;
    while (centavos > 0)
    {
        if (centavos >= 25)
        {
            quantidade_moedas++;
            centavos -= 25;
        }
        else if (centavos >= 10)
        {
            quantidade_moedas++;
            centavos -= 10;
        }
        else if (centavos >= 5)
        {
            quantidade_moedas++;
            centavos -= 5;
        }
        else
        {
            quantidade_moedas++;
            centavos--;
        }
    }

    printf("%i\n", quantidade_moedas);
}

float obter_real_positivo(void)
{
    float n;
    do
    {
        n = get_float("Insira o valor a ser trocado: ");
    }
    while (n <= 0);
    return n;
}