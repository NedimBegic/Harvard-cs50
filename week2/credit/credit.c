#include <cs50.h>
#include <stdio.h>

int getNumberLength(long long number)
{
    int length = 0;
    while (number != 0)
    {
        number /= 10;
        length++;
    }

    return length;
}

int main(void)
{
    long long creditNum = get_long_long("Enter your credit number: "); // Use get_long_long instead of get_int
    int even = 0;
    int odd = 0;
    int numberLength = getNumberLength(creditNum);
    long long copyCredit = creditNum;
    int position = numberLength;
    int sum = 0;
    // getting first two numbers
    int first = 0;
    int second = 0;
    for (int i = 0; i < numberLength; i++)
    {
        int digit = copyCredit % 10;
        // if numberLength == odd => multiply the odd digit
        if (numberLength % 2 != 0)
        {
            // multiply the odd
            if (position % 2 == 0)
            {
                // check if the number is two digits
                int current = digit * 2;
                int currentLength = getNumberLength(current);
                if (currentLength == 2)
                {
                    int firstNum = current / 10;
                    int secondNum = current % 10;
                    odd += firstNum + secondNum;
                }
                else
                {
                    even += current;
                }
            }
            else
            {
                even += digit;
            }
        }
        else
        {
            // multiply the even
            if (position % 2 == 0)
            {
                odd += digit;
            }
            else
            {
                // provjerit da li je broj dvocifren
                int current = digit * 2;
                int currentLength = getNumberLength(current);
                if (currentLength == 2)
                {
                    int firstNum = current / 10;
                    int secondNum = current % 10;
                    even += firstNum + secondNum;
                }
                else
                {
                    even += current;
                }
            }
        }

        // getting the first two digits for determining which card is it
        if (position == 2)
        {
            second = digit;
        }
        if (position == 1)
        {
            first = digit;
        }
        position--;
        copyCredit /= 10;
    }
    bool isValid;
    sum = odd + even;
    // checking if number is valid
    if (sum % 10 == 0)
    {
        isValid = true;
    }
    else
    {
        isValid = false;
    }
    // which credit card
    if (isValid == 1)
    {
        // for American Express
        if (numberLength == 15 && first == 3 && (second == 4 || second == 7))
        {
            printf("AMEX\n");
        }
        else if (numberLength == 16 && first == 5 && (second == 1 || second == 2 || second == 3 || second == 4 || second == 5))
        {
            printf("MASTERCARD\n");
        }
        else if ((numberLength == 13 || numberLength == 16) && first == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}