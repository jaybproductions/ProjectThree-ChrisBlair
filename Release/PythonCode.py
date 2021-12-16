import re
import string


def printsomething():
    print("Hello from Python!")


def ItemFreq():
    # open the file
    file = open("GroceryList.txt", "r")
    # initilize a dictionary
    items = dict()

    # loop through each line in the file
    for line in file:
        # get just the word 
        line = line.strip()

        word = line.lower()
        # if the word already exists, increment the value by 1
        if word in items:
            items[word] = items[word] + 1
        # else set the value to 1
        else:
            items[word] = 1

    # print all the key value pairs
    for key in list(items.keys()):
        print(key.capitalize(), ":", items[key])

    # close the file
    file.close()



def CountItemFreq(searchTerm):
    # open the file
    file = open("GroceryList.txt", "r")
    
    # initilize a counter to 0
    count = 0

    # loop through each line
    for line in file:
        # get just the word        
        line = line.strip()

        word = line.lower()

        # if the word equals the search term increment the count
        # also make it case insensitive 
        if word.lower() == searchTerm.lower():
            count += 1
    # close the file
    file.close()

    # return the count 
    return count


def CreateDatFile():
    # open the text file to read
    file = open("GroceryList.txt", "r")
    # open the dat file to write
    newFile = open("frequency.dat", "w")
    # create an empty dict
    items = dict()

    # loop through each line in the file
    for line in file:
        # get just the word
        line = line.strip()

        word = line.lower()
        # if the item already exists in the dict add 1 to its value
        if word in items:
            items[word] = items[word] + 1
        # if not set the value to 1
        else: 
            items[word] = 1

    # loop through each key/value pair and write it to the dat file
    for key in list(items.keys()):
        newFile.write(str(key.capitalize()) + " " + str(items[key]) + "\n")

    # close both files
    file.close()
    newFile.close()

