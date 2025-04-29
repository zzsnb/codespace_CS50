import csv

with open("databases/small.csv") as file:
    read = csv.DictReader(file)
    print(read)
    for row in read:
        print(row)
