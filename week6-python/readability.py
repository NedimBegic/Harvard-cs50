# TODO
from cs50 import get_string

text = get_string("Write text: ")

chars = 0
words = 1
sentences = 0

for char in text:
    if char.isalpha():
        chars += 1
    if char in ["?", "!", "."]:
        sentences += 1

word_list = text.split()

words = len(word_list)

L = (chars / words) * 100
S = (sentences / words) * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
