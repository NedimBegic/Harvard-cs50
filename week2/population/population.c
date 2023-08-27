#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startingSize;
    do
    {
        startingSize = get_int("Enter starting number: ");
    }
    while (startingSize < 9);
    // TODO: Prompt for end size
    int endingSize;
    do
    {
        endingSize = get_int("Enter ending number: ");
    }
    while (endingSize < startingSize);
    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    int currentSize = startingSize;
    while (currentSize < endingSize)
    {
        currentSize += currentSize / 3 - currentSize / 4;
        years++;
    };
    // TODO: Print number of years
    printf("Years: %i\n", years);
    return 0;
}
