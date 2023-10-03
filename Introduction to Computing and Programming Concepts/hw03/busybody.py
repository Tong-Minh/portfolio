# Minh Tong
# tong0154
# CSCI 1133 Section 050
# Assignment 3

def busybody(list_of_clubs):
    students = []
    busybody = []
    for club in list_of_clubs:
        for member in club:
            students.append(member)
    for i in students:
        if (i not in busybody) and (students.count(i) == len(list_of_clubs)):
            busybody.append(i)
    return busybody