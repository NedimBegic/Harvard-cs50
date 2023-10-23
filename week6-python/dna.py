import csv
import sys

def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    database_filename = sys.argv[1]
    database = []
    with open(database_filename, "r") as database_file:
        csv_reader = csv.DictReader(database_file)
        for row in csv_reader:
            database.append(row)

    # Read DNA sequence file into a variable
    sequence_filename = sys.argv[2]
    with open(sequence_filename, "r") as sequence_file:
        dna_sequence = sequence_file.read()

    # Find the longest match of each STR in the DNA sequence
    str_counts = {}
    for row in database:
        for key in row.keys():
            if key != "name":
                str_counts[key] = longest_match(dna_sequence, key)

    # Check the database for matching profiles
    for row in database:
        match = True
        for key in row.keys():
            if key != "name" and int(row[key]) != str_counts[key]:
                match = False
                break

        if match:
            print(row["name"])
            return

    print("No match")

def longest_match(sequence, subsequence):
    """Returns length of the longest run of subsequence in sequence."""
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0
        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        longest_run = max(longest_run, count)

    return longest_run

if __name__ == "__main__":
    main()
