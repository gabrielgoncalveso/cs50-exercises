from cs50 import get_float


def main():
    cash = get_positive_float("Insira o valor a ser trocado: ")

    cents = round(cash * 100)

    coin_counter = 0

    while cents > 0:
        if cents >= 25:
            coin_counter += 1
            cents -= 25
        elif cents >= 10:
            coin_counter += 1
            cents -= 10
        elif cents >= 5:
            coin_counter += 1
            cents -= 5
        else:
            coin_counter += 1
            cents -= 1

    print(coin_counter)


def get_positive_float(msg):
    while True:
        value = get_float(msg)
        if value > 0:
            break

    return value


main()
