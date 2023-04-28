#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string encrypt_caesar(string plaintext, int secret_key);

int main(int argc, string argv[])
{
    //verifica se input é valido
    if (argc != 2)
    {
        printf("Use: ./caesar key\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Use: ./caesar key");
            return 1;
        }
    }

    string plaintext = get_string("plaintext: ");
    int key = atoi(argv[1]);
    string cyphertext = encrypt_caesar(plaintext, key);

    // printf("plaintext: %s\n", plaintext);
    printf("ciphertext: %s\n", cyphertext);
}

string encrypt_caesar(string text, int secret_key)
{
    int new_key = secret_key;

    while (new_key >= 26)
    {
        new_key -= 26;
    }

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            //Se valor numerico da nova letra ultrapassar o valor de z em ascii, retornar a letra a e adicionar valor da chave
            if ((int)(text[i] + new_key) > 'Z')
            {
                text[i] = text[i] - 'Z' + 'A' - 1 + new_key;
            }
            else
            {
                text[i] += new_key;
            }
        }
        else if (text[i] >= 'a' && text[i] <= 'z')
        {
            //Se valor numerico da nova letra ultrapassar o valor de z em ascii, retornar a letra a e adicionar valor da chave
            if ((int)(text[i] + new_key) > 'z')
            {
                text[i] = text[i] - 'z' + 'a' - 1 + new_key;
            }
            else
            {
                text[i] += new_key;
            }
        }
    }

    return text;
}