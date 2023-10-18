# TODO
from cs50 import get_int

n = get_int("Enter height: ");

while n < 1 or n > 8:
        n = get_int("Enter height: ")

for i in range(n):
    piramid = "#" * (i + 1)
    space = " " *( n - i - 1)
    middle = "  "
    print(space + piramid + middle + piramid);
