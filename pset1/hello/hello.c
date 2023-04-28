#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string nome = get_string("Digite seu nome:\n");
    printf("Olá mundo! E olá %s\n", nome);
}