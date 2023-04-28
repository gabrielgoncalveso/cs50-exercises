// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
#define N 26

// Hash table
node *table[N];

//dictionary size
int dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    int index = hash(word);

    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO

    int index = word[0];

    //convert lowercase to upppercase
    if (index >= 97 && index <= 122)
    {
        index -= 32;
    }

    if (index < 65 || index > 90)
    {
        return 25;
    }

    //subtract value from "a" from ascii table

    return index - 65;

    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *f = fopen(dictionary, "r");

    if (f == NULL)
    {
        printf("Couldn't open dictionary!\n");
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(f, "%s", word) != EOF)
    {

        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
        {
            return false;
        }

        strcpy(new_node->word, word);

        int index = hash(word);

        new_node->next = table[index];

        table[index] = new_node;

        dictionary_size++;

    }

    fclose(f);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *scout_cursor = table[i];

        while (scout_cursor != NULL)
        {
            node *deleter_cursor = scout_cursor;
            scout_cursor = scout_cursor->next;
            free(deleter_cursor);
        }

        if (scout_cursor == NULL && i == N - 1)
        {
            return true;
        }
    }

    return false;
}
