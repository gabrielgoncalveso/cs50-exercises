#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>

int calculate_grade(string text);

int main(void)
{
    string text = get_string("Texto: ");

    int coleman_liau = calculate_grade(text);

    if (coleman_liau < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (coleman_liau > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", coleman_liau);
    }
}

int calculate_grade(string text)
{
    int word_count = 0;
    int sentence_count = 0;
    int letter_count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            sentence_count++;
        }

        if (text[i] >= 'A' && text[i] <= 'z')
        {
            letter_count++;
        }

        if (text[i] == ' ' || text[i + 1] == '\0')
        {
            word_count++;
        }
    }
    // printf("Letras: %i, Palavras: %i, Sentencas: %i\n", letter_count, word_count, sentence_count);
    float media_letras_por_palavra = (letter_count / (float) word_count) * 100;
    float media_sentencas_por_palavra = (sentence_count / (float) word_count) * 100;
    // printf("media letras: %f\nmedia sentencas: %f\n", media_letras_por_palavra, media_sentencas_por_palavra);
    return round(0.0588 * media_letras_por_palavra - 0.296 * media_sentencas_por_palavra - 15.8);


}