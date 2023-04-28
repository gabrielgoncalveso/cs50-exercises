from cs50 import get_string


def main():
    card_number = get_card_number()

    first_digits = card_number[0:2]

    sum_second = 0
    index = len(card_number) - 2

    while index >= 0:
        digit = int(card_number[index]) * 2
        for i in str(digit):
            sum_second += int(i)

        index -= 2

    index = len(card_number) - 1

    while index >= 0:
        sum_second += int(card_number[index])
        index -= 2

    if sum_second % 10 == 0:

        if int(first_digits) >= 40 and int(first_digits) < 50:

            if len(card_number) == 16 or len(card_number) == 13:
                print("VISA")
            else:
                print("INVALID")

        elif int(first_digits) > 50 and int(first_digits) <= 55:

            if len(card_number) == 16:
                print("MASTERCARD")
            else:
                print("INVALID")

        elif int(first_digits) == 34 or int(first_digits) == 37:

            if len(card_number) == 15:
                print("AMEX")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")


def get_card_number():
    while True:
        card_number = get_string("Insira o número do cartão: ")
        if card_number.isnumeric():
            break

    return card_number.strip()


main()