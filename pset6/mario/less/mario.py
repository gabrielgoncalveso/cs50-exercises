from cs50 import get_int


def main():
    height = get_positive_int("Height: ")

    for i in range(height):
        j = height-1
        while j >= 0:
            if i < j:
                print(" ", end="")
            else:
                print("#", end="")
            j -= 1
        print()


def get_positive_int(message):
    while True:
        value = get_int(message)
        if value > 0 and value < 9:
            break

    return value


main()
