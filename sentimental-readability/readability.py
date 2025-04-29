# get the text from user
import re
from cs50 import get_string
text = get_string("Text: ")

#count the words
#count the sentence
#count the letter

letters = len(re.findall(r"[a-zA-Z]",text))
sentences = len(re.findall("[.!?]",text))
words = len(re.findall(" ",text)) + 1

#Compute the Coleman-Liau index 0.0588 * L - 0.296 * S - 15.8
index = (100 * (0.0588 * letters - 0.296 * sentences)/words) - 15.8

#Print the grade level
index = round(index)
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print("Grade " + str(index))
