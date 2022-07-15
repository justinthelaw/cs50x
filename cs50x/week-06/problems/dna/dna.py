import sys
import csv

# STRs in the small db
smallDB = ["AGATC", "AATG", "TATC"]
# STRs in the large db
largeDB = ["AGATC", "TTTTTTCT", "AATG", "TCTAG", "GATA", "TATC", "GAAA", "TCTG"]


def main():
    if len(sys.argv) != 3:  # check for correct number of arguments
        print("Usage: python dna.py data.csv sequence.txt")
        return 1

    selectedSize = largeDB  # default to the large size sequence database
    if "small" in sys.argv[1]:  # check for small databse size
        selectedSize = smallDB

    # read DNA databases, with name and counts of highest number of consecutive STRs
    db = readDB(selectedSize)

    # read the sample sequence into memory
    sample = ""
    with open(sys.argv[2]) as file:
        sample = (file.readlines())[0]

    # count highest number of consecutive STRs in sample DNA sequence
    count = consecutiveRepeatCounter(sample, selectedSize)

    # compare the count against the database to find matching person
    result = sequenceMatcher(count, db, selectedSize)
    print(result)


def readDB(selectedSize):
    db = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            for STR in selectedSize:
                row[STR] = int(row[STR])  # transform every sequence count to an integer
            db.append(row)  # add to the db array
    return db


def sequenceMatcher(count, db, selectedSize):
    result = "No match"
    for i in range(0, len(db)):
        correctPerson = False
        # check every person's sequence counts to the sample sequence's
        for STR in selectedSize:
            if db[i][STR] == count[STR]:
                correctPerson = True
            else:
                correctPerson = False
                break
        if correctPerson:
            result = db[i]["name"]
    return result


def consecutiveRepeatCounter(sample, selectedSize):
    count = {}
    # initialize all STRs in count dictionary
    for STR in selectedSize:
        count[STR] = 0

    # find most consecutive STR occurances in sample sequence
    for STR in selectedSize:
        tempSTR = STR
        while tempSTR in sample:
            tempSTR += STR
        count[STR] = tempSTR.count(STR) - 1
    return count


if __name__ == "__main__":
    main()
