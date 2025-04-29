from cs50 import get_int

while True:
    number = get_int("Height: ")
    if number <= 8 and number >= 1:
        break

for i in range(number):
    print(" " * (number - 1 - i), end='')
    print("#" * (i + 1), end='')
    print(" " * 2, end='')
    print("#" * (i + 1), end='')
    print("")  # 本质上就是换行了，如果里面写\n则换了两行
