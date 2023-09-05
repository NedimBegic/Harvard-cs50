#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number, and symbol\n");
    }
}

bool valid(string password)
{
    bool hasLower = false;
    bool hasUpper = false;
    bool hasNumber = false;
    bool hasSymbol = false;

    for (int i = 0, n = strlen(password); i < n; i++)
    {
        char c = password[i];

        if (islower(c))
        {
            hasLower = true;
        }
        else if (isupper(c))
        {
            hasUpper = true;
        }
        else if (isdigit(c))
        {
            hasNumber = true;
        }
        else if (ispunct(c) || isspace(c))
        {
            hasSymbol = true;
        }
    }

    // Check if all required conditions are met
    return hasLower && hasUpper && hasNumber && hasSymbol;
}
