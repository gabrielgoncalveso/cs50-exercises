#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string encrypt_substitution(string plaintext, string secret_key);

int main(int argc, string argv[])
{
    //verifica se input é valido
    if (argc != 2)
    {
        printf("Uso: ./substitution chave_de_substituicao \n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("A chave deve conter 26 caracteres.\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("A chave deve conter apenas caracteres  do alfabeto.\n");
            return 1;
        }
        for (int y = i; y < n; y++)
        {
            if (argv[1][y] == argv[1][i] && i!=y)
            {
                printf("A chave contem caracteres repetidos.\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext: ");

    string cyphertext = encrypt_substitution(plaintext, argv[1]);

    // printf("plaintext: %s\n", plaintext);
    printf("ciphertext: %s\n", cyphertext);
}

string encrypt_substitution(string text, string secret_key)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        for (int y = 0; y < 26; y++)
        {
            if (text[i] == ALPHABET[y])
            {
                text[i] = toupper(secret_key[y]);
                break;
            }
            else if (text[i] == tolower(ALPHABET[y]))
            {
                text[i] = tolower(secret_key[y]);
                break;
            }
        }
    }

    return text;
}