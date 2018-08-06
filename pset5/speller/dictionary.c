// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

#define HASHTABLESIZE 143091


typedef struct el
{
    char word[LENGTH];
    struct el *next;
} node;
node *hashTable[HASHTABLESIZE] = {NULL};


void addNode(char word[]);
unsigned int stringToKey(const char* word);
int searchNode(char nword[]);
void deleteRow(node *head);


// Returns true if word is in dictionary else false
bool check(const char *word)
{

    char temp[LENGTH + 1];

    strncpy(temp, word, LENGTH);
    temp[strlen(word)] = '\0';
    int i = 0;
    while (temp[i] != '\0')
    {
        temp[i] = tolower(temp[i]);
        i++;
    }


    int ascii = stringToKey(temp);

    node *n;
    for (n = hashTable[ascii]; n != NULL; n = n->next)
    {
        if (strcmp(n->word, temp) == 0)
        {
            return true;
        }
    }
    return false;
}

int numberOfWords = 0;
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    FILE *ptr = fopen(dictionary, "r");
    if (ptr == NULL)
    {
        unload();
        return false;
    }

    char word[LENGTH];

    while (fscanf(ptr, " %45s", word) == 1)
    {
        addNode(word);
        numberOfWords++;
        fscanf(ptr, "%*[^\n]\n", NULL);
    }

    fclose(ptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return numberOfWords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < HASHTABLESIZE; i++)
    {
        deleteRow(hashTable[i]);
    }
    return true;
}


void addNode(char word[])
{

    int ascii;
    node *n;
    ascii = stringToKey(word);
    n = (node *) malloc(sizeof(node));
    strcpy(n->word, word);
    n->next = hashTable[ascii];
    hashTable[ascii] = n;
}

/*
* Adapted by Neel Mehta from
 * http://stackoverflow.com/questions/2571683/djb2-hash-function.
 */
unsigned int stringToKey(const char* word)
 {
     unsigned long hash = 5381;

     for (const char* ptr = word; *ptr != '\0'; ptr++)
     {
         hash = ((hash << 5) + hash) + tolower(*ptr);
     }

     return hash % HASHTABLESIZE;
 }


int searchNode(char nword[])
{

    int ascii = stringToKey(nword);
    for (node *n = hashTable[ascii]; n != NULL; n = n->next)
    {
        if (strcmp(n->word, nword) == 0)
        {
            return ascii;
        }
    }
    return -1;
}

void deleteRow(node *head)
{
    if (head == NULL)
    {
        return;
    }

    deleteRow(head->next);
    free(head);
}