#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

int sizeOfWords = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert the input word to lowercase
    char lowercaseWord[LENGTH + 1];
    for (int i = 0; word[i] != '\0'; i++) {
        lowercaseWord[i] = tolower(word[i]);
    }
    lowercaseWord[strlen(word)] = '\0';

    // Determine the index of the word in the hash table
    int index = hash(lowercaseWord);

    // Loop through the linked list in that element of the hash table
    node *head = table[index];
    while (head != NULL)
    {
        if (strcmp(head->word, lowercaseWord) == 0)
        {
            return true;
        }
        // Go to the next linked list
        head = head->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Initial hash table elements to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    // Open and store dictionary file
    FILE *file;
    file = fopen(dictionary, "r");
    // Check if the file is opened correctly
    if (file == NULL)
    {
        printf("File couldn't open\n");
        return false;
    }
    // Read the words from the file and add them to the hash table
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Make memory for a node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Not enough memory\n");
            return false;
        }
        // Set the word to the node
        strcpy(n->word, word);
        // Set the pointer of the word to null
        n->next = NULL;
        // Set the position of the word in the hash table
        int position = hash(word);
        // Set the pointer of the new node to the previous hash table position
        if (table[position] == NULL)
        {
            table[position] = n;
        }
        else
        {
            // Set the next pointer of n to the first element of the table position
            n->next = table[position];
            // Set the table to be the pointer to n
            table[position] = n;
        }

        // Count the size of words
        sizeOfWords++;
    }
    fclose(file);  // Close the dictionary file

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return the sizeOfWords
    return sizeOfWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO: Implement unloading logic
    // go to every element in array
    for (int i = 0; i < N; i++)
    {
        // delete every node in that element of arrayc
        while (table[i] != NULL)
        {
            node *temp = table[i];
            table[i] = table[i]->next;
            free(temp);
        }
    }
    return true;
}
