from cs50 import get_int

n = get_int("Enter height: ")

while n < 1 or n > 8:
    n = get_int("Enter height: ")

for i in range(n):
    spaces = " " * (n - i - 1)
    hashes = "#" * (i + 1)
    print(spaces + hashes)