import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Please enter the files.")
        quit()

    # TODO: Read database file into a variable and Read DNA sequence file into a variable
#    with open(argc[1]) as database:
    with open(sys.argv[1]) as database_file, open(sys.argv[2]) as sequences_file:
        database = csv.DictReader(database_file)
        STRnumber = len(database.fieldnames) - 1  # to check how many STR to search totally
        sequence = sequences_file.read()

        # TODO: Find longest match of each STR in DNA sequence and
        strdata = {}
        for i in range(1, STRnumber + 1, 1):
            strdata[database.fieldnames[i]] = longest_match(sequence, database.fieldnames[i])

        # TODO: Check database for matching profiles
        for row in database:
            check = True
            # Check every STR for every person in the database (if one different,quit)
            for head in database.fieldnames:
                if head == "name":  # to jump the first line
                    continue
                if int(row[head]) != int(strdata[head]):
                    check = False
                    break

            if check == True:
                print(row["name"])
                quit()
        else:
            print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
