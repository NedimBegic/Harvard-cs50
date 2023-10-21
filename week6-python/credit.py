from cs50 import get_string

n = get_string("Enter credit number: ")
odd_even_sum = 0

# Reverse the string because it starts from the second last to the first
reversedN = n[::-1]

for i, el in enumerate(reversedN):
    if (i + 1) % 2 == 0:
        doubled_digit = int(el) * 2
        if doubled_digit > 9:
            doubled_digit -= 9
        odd_even_sum += doubled_digit
    else:
        odd_even_sum += int(el)

# Check if the last digit of the sum is zero
isValid = odd_even_sum % 10 == 0


print(odd_even_sum)
# Check for card type validation

if isValid:
    if n[0] == '3' and len(n) == 15 and (n[1] == '4' or n[1] == '7'):
        print("AMEX")
    elif n[0] == '5' and len(n) == 16 and n[1] in ('1', '2', '3', '4', '5'):
        print("MASTERCARD")
    elif n[0] == '4' and (len(n) == 13 or len(n) == 16):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")

