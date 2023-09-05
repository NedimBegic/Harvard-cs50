#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Function to replace vowels with numbers
void replace(char word[]);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <word>\n", argv[0]);
        return 1;
    }

    char word[50];
    strcpy(word, argv[1]);

    replace(word);

    printf("Replaced: %s\n", word);

    return 0;
}

void replace(char word[])
{
    for (int i = 0; i < strlen(word); i++)
    {
        switch (word[i])
        {
        case 'a':
            word[i] = '6';
            break;

        case 'e':
            word[i] = '3';
            break;

        case 'i':
            word[i] = '1';
            break;

        case 'o':
            word[i] = '0';
            break;
        }
    }
}
