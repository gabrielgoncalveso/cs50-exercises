#include <stdio.h>
#include <cs50.h>

long obter_numero_cartao(void);
void validar_cartao(long numero_cartao);

int main(void)
{
    long numero_cartao = obter_numero_cartao();

    validar_cartao(numero_cartao);
}

long obter_numero_cartao(void)
{
    long n;
    do
    {
        n = get_long("Insira o número do cartão: ");
    }
    while (n <= 0);
    return n;
}

void validar_cartao(long numero_cartao)
{

    //American Express = 15 digitos e inicio em 34 ou 37
    //Master Card = 16 digitos e inicio em 51, 52, 53, 54 ou 55
    //Visa = 13 ou 16 digitos e inicio em 4
    long numero_cartao_editado = numero_cartao;
    int contador = 0;
    int soma_validacao_pares = 0;
    int soma_validacao_impares = 0;
    long first_two_digits;
    bool got_first_digits = false;

    while (numero_cartao_editado > 0)
    {
        long digito = numero_cartao_editado % 10;
        numero_cartao_editado /= 10;
        contador++;

        if (numero_cartao_editado > 0 && numero_cartao_editado < 99 && !got_first_digits)
        {
            first_two_digits = numero_cartao_editado;
            got_first_digits = true;
        }

        if (contador % 2 == 0)
        {
            int produto_digito = digito * 2;
            while (produto_digito > 0)
            {
                int novo_digito = produto_digito % 10;
                produto_digito /= 10;
                soma_validacao_pares += novo_digito;
            }
        }
        else
        {
            soma_validacao_impares += digito;
        }
    }

    if ((soma_validacao_impares + soma_validacao_pares) % 10 == 0)
    {
        if (first_two_digits >= 40 && first_two_digits < 50)
        {
            if (contador == 16 || contador == 13)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (first_two_digits > 50 && first_two_digits <= 55)
        {
            if (contador == 16)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (first_two_digits == 34 || first_two_digits == 37)
        {
            if (contador == 15)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}