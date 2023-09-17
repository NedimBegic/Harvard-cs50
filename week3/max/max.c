// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
    return 0;
}

// TODO: return the max value
int max(int array[], int n)
{
    /7 set the first element to hightst
    int highest = array[0];
    // start from 1 because we used the first element in previous variable
    for (int i = 1; i < n; i++)
    {
        if (array[i] > highest)
        {
            highest = array[i];
        }
    }
    return highest;
}
