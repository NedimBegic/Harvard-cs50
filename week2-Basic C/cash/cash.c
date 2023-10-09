#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // TODO
    int input;
    do
    {
        input = get_int("Insert cents: ");
    }
    while (input < 1);
    return input;
}

int calculate_quarters(int cents)
{
    // TODO
    int quarters;
    if (cents >= 25)
    {
        quarters = cents / 25;
    }
    else
    {
        quarters = 0;
    }
    return quarters;
}

int calculate_dimes(int cents)
{
    // TODO
    int dimes;
    if (cents >= 10)
    {
        dimes = cents / 10;
    }
    else
    {
        dimes = 0;
    }
    return dimes;
}

int calculate_nickels(int cents)
{
    // TODO
    int nickels;
    if (cents >= 5)
    {
        nickels = cents / 5;
    }
    else
    {
        nickels = 0;
    }
    return nickels;
}

int calculate_pennies(int cents)
{
    // TODO
    return cents;
}
