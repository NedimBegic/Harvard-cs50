#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int length = strlen(input);
    int lastIndex = length - 1;
    if (length == 0)
    {
        return 0;
    }
    // convert last element to nunber
    int lastChar = input[lastIndex] - '0';
    // push out the last element from string
    input[lastIndex] = '\0';
    return lastChar + 10 * convert(input);
    // 2 + 10 * 0
    // 3 + 10 * 2
    // 4 + 10 * 3
}