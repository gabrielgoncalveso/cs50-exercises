from cs50 import get_string


def main():
    text = get_string("Text: ")

    coleman_liau = calculate_grade(text)

    if coleman_liau < 1:
        print("Before Grade 1")
    elif coleman_liau > 16:
        print("Grade 16+")
    else:
        print(f"Grade {coleman_liau}")


def calculate_grade(text):
    word_count = 0
    sentence_count = 0
    letter_count = 0

    i = 0

    while i < len(text):

        if text[i] == "!" or text[i] == "?" or text[i] == ".":
            sentence_count += 1

        if text[i].isalpha():
            letter_count += 1

        if text[i] == " " or i == len(text) - 1:
            word_count += 1

        i += 1

    average_letters_per_words = (letter_count / word_count) * 100
    average_sentences_per_words = (sentence_count / word_count) * 100

    return round(0.0588 * average_letters_per_words - 0.296 * average_sentences_per_words - 15.8)


main()