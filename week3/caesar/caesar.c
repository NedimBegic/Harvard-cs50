#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check for the correct number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check if the provided key (argv[1]) is a valid positive integer
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert the key from a string to an integer
    int k = atoi(argv[1]);

    string plainText = get_string("plaintext:  ");
    int lengthOfText = strlen(plainText);

    char cipherText[lengthOfText + 1]; // +1 for the null terminator

    // Process each character in the input text
    for (int i = 0; i < lengthOfText; i++)
    {
        char c = plainText[i];

        // Only convert alphabetical characters
        if (isalpha(c))
        {
            // Determine the base character ('A' for uppercase, 'a' for lowercase)
            char base = isupper(c) ? 'A' : 'a';

            // Apply the Caesar cipher shift and ensure it stays within the range of letters
            cipherText[i] = (char)(((c - base + k) % 26 + 26) % 26 + base);
        }
        else
        {
            // Non-alphabetical characters remain unchanged
            cipherText[i] = c;
        }
    }

    // Null-terminate the ciphertext string
    cipherText[lengthOfText] = '\0';

    printf("ciphertext:  %s\n", cipherText);
    return 0;
}
