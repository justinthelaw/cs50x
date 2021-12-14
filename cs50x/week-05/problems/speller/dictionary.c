// Implements a dictionary's functionality

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

#define LENGTH 45
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of words in the dictionary
int count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int length = strlen(word);
    char *copy = malloc(length);

    for (int i = 0; i <= length; i++)
    {
        copy[i] = word[i];
    }

    int tableRow = hash(copy);
    node *cursor = table[tableRow];

    while (cursor != NULL)
    {
        if (strcasecmp(copy, cursor->word) == 0)
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
    return tolower(word[0]) - 96;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(input, "%s\n", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        n->next = NULL;
        strcpy(n->word, word);

        int hashedWord = hash(word);
        if (table[hashedWord] == NULL)
        {
            table[hashedWord] = n;
        }
        else
        {
            n->next = table[hashedWord];
            table[hashedWord] = n;
        }

        count++;
    }

    fclose(input);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    return true;
}
