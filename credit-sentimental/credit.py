import cs50

# get the number with string(用正则表达式)


def main():
    number = cs50.get_int("Number: ")
    strnumber = str(number)
    cardtype = check_number(strnumber)
    if check_luhn(strnumber):
        print(cardtype)
    else:
        print("INVALID")


def check_number(strnumber):
    # check the length of the string and check the first several numbers
    if len(strnumber) == 15:
        if strnumber[:2] in ["34", "37"]:
            return "AMEX"
        else:
            print("INVALID")
            exit()
    elif len(strnumber) == 13:
        if int(strnumber[:1]) == 4:
            return "VISA"
        else:
            print("INVALID")
            exit()
    elif len(strnumber) == 16:
        if int(strnumber[:1]) == 4:
            return "VISA"
        elif int(strnumber[:2]) in [51, 52, 53, 54, 55]:
            return "MASTERCARD"
        else:
            print("INVALID")
            exit()
    else:
        print("INVALID")
        exit()


def check_luhn(strnumber):
    # take out every 2 number and add their number up
    sum_number = 0
    for i in range(len(strnumber) - 2, -1, -2):
        # take out the number and plus 2
        number = str(int(strnumber[i]) * 2)
        # add every number
        sum_number += sum(int(digit) for digit in number)

    # take out the other numbers and add them up
    for i in range(len(strnumber) - 1, -1, -2):
        sum_number += int(strnumber[i])

    # judge the card whether is legal
    if sum_number % 10 == 0:
        return True
    else:
        return False


main()
