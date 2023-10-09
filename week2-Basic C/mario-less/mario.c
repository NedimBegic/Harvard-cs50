#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Give a positive height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++)
    {
        // making spaces
        for (int j = 1; j <= height - i; j++)
        {
            printf(" ");
        }
        // making #
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}


