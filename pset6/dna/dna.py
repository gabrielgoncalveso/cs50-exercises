import sys
import csv


def main():

    if len(sys.argv) != 3:
        print("Usage: pyhton dna.py data.csv sequence.txt")
        sys.exit()

    dna_csv = open(sys.argv[1])
    dna_db_dict = csv.DictReader(dna_csv)

    with open(sys.argv[2]) as dna_sequence_txt:
        dna_sequence = dna_sequence_txt.read()

    max_sum_agatc = 0
    max_sum_aatg = 0
    max_sum_tatc = 0

    was_agatc = False
    was_aatg = False
    was_tatc = False
    count_consecutive = 0

    index = 0
    while index < len(dna_sequence):
        if index + 4 < len(dna_sequence):
            dna_sequence[index:index + 4]
            dna_sequence[index+4:index + 8]
            if dna_sequence[index:index + 4] == "AATG":
                if was_aatg:
                    count_consecutive += 1
                else:
                    count_consecutive = 1
                    was_aatg = True
                    was_tatc = False
                    was_agatc = False

                if count_consecutive > max_sum_aatg:
                    max_sum_aatg = count_consecutive

                index += 3

            elif dna_sequence[index:index + 4] == "TATC":
                if was_tatc:
                    count_consecutive += 1
                else:
                    count_consecutive = 1
                    was_aatg = False
                    was_tatc = True
                    was_agatc = False

                if count_consecutive > max_sum_tatc:
                    max_sum_tatc = count_consecutive

                index += 3
            else:
                was_aatg = False
                was_tatc = False

        if index + 5 < len(dna_sequence):
            if dna_sequence[index:index + 5] == "AGATC":
                if was_agatc:
                    count_consecutive += 1
                else:
                    count_consecutive = 1
                    was_aatg = False
                    was_tatc = False
                    was_agatc = True

                if count_consecutive > max_sum_agatc:
                    max_sum_agatc = count_consecutive

                index += 4
            else:
                was_agatc = False

        index += 1

    found_item = False

    for item in dna_db_dict:
        dict_item = dict(item)
        if int(dict_item["AGATC"]) == max_sum_agatc and int(dict_item["TATC"]) == max_sum_tatc and int(dict_item["AATG"]) == max_sum_aatg:
            found_item = True
            print(dict_item["name"])
            break

    if not found_item:
        print("No match")

    dna_csv.close()


main()