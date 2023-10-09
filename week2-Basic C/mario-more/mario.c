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
        // Making left one
        for (int j = 1; j <= height - i; j++)
        {
            printf(" ");
        }
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        // Making space between
        printf(" ");
        // Making right one
        for (int a = 1; a <= i; a++)
        {
            printf("#");
        }
        for (int b = 1; b <= height - 1; b++)
        {
            printf(" ");
        }
        // Go to next row
        printf("\n");
    }
    return 0;
}
