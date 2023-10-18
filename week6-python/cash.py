from cs50 import get_float

# Prompt the user for a non-negative amount of change
while True:
    n = get_float("Change owed: ")
    if n >= 0:
        break

# Convert dollars to cents
n = int(n * 100)

# Initialize variables to keep track of the number of coins
quarters = 0
dimes = 0
nickels = 0
pennies = 0

# Calculate the number of each type of coin
quarters = n // 25
n %= 25

dimes = n // 10
n %= 10

nickels = n // 5
n %= 5

pennies = n

# Calculate the total number of coins
total_coins = quarters + dimes + nickels + pennies

# Print the minimum number of coins
print("Minimum number of coins:", total_coins)
print("Quarters:", quarters)
print("Dimes:", dimes)
print("Nickels:", nickels)
print("Pennies:", pennies)
