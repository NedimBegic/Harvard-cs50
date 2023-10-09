#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int allCharsThere(string key);

int main(int argc, string argv[])
{
    string key = argv[1];
    if (argc != 2)
    {
        printf("You must set 1 argument\n");
        return 1;
    }
    int keyLength = strlen(key);
    int allAlpha = 1;
    int keyUsed[26] = {0};
    // check if everything is a char and are there duplicates
    for (int i = 0; i < keyLength; i++)
    {
        if (!isalpha(key[i]))
        {
            allAlpha = 0;
        }

    }
    // check if there is 26  chars
    if (keyLength != 26)
    {
        printf("You must contain 26 characters!\n");
        return 1;
    }
    // return err if there is non alpha
    if (!allAlpha)
    {
        printf("Everything must be a char!\n");
        return 1;
    }
    // make everything lowercase
    string lowerKey = key;
    for (int i = 0; i < keyLength; i++)
    {
        lowerKey[i] = tolower(key[i]);
    }
    // check if there is every letter in the key
    int everyChar = allCharsThere(key);
    if (!everyChar)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    // ask for text
    string plainText = get_string("plaintext:");
    int textLength = strlen(plainText);
    string cipherText = plainText;
    // transfer the text
    for (int i = 0; i < textLength; i++)
    {
        // transfer only chars
        char c = plainText[i];
        if (isalpha(c))
        {
            // set it to lowercase
            c = tolower(c);
            int indexOfChar = c - 97;
            // return it with proper size
            if (islower(plainText[i]))
            {
                cipherText[i] = lowerKey[indexOfChar];
            }
            else
            {
                cipherText[i] = toupper(lowerKey[indexOfChar]);
            }
        }
    }
    printf("ciphertext: %s\n", cipherText);
    return 0;
}

int allCharsThere(string key)
{
    // make an array with 26 indexes to store if there is that number
    int isChar[26];
    int base = 97; // because 'a' is on 97 we need to be 0
    // subtrack every letter with the base to get in range of 0 - 25 (it will be there indexes)
    // if there is a letter set his value of his index to 1
    for (int i = 0; i < 26; i++)
    {
        int charNumber = key[i] - base;
        isChar[charNumber] = 1;
    }

    for (int i = 0; i < 26; i++)
    {
        if (isChar[i] != 1)
        {
            return 0;
        }
    }
    return 1;
}
