# Minh Tong
# tong0154
# CSCI 1133 Section 050
# Assignment 5

#==========================================
# Purpose: takes a dictionary employees work hours with their names as keys and values as a list of their hours, then returns a new dictionary of their names with tuples that have their least and most hours worked.
# Input Parameter(s): takes a dictionary with employee names as keys, and values that are lists comprised of integers (representing work hours)
# Return Value(s): returns a new dictionary named my_dict
#==========================================
def min_max_hours(emp_diction):
    my_dict = {}
    for worker in emp_diction:
        if emp_diction[worker] == []:
            my_dict[worker] = (0,0)
        else:
            my_dict[worker] = (min(emp_diction[worker]), max(emp_diction[worker]))
    return my_dict
    
#min_max_hours({"Shana": [20], "Jody": [10, 20, 10, 5], "Mike": [40, 40]})
#min_max_hours({"Shana": [20, 20, 20, 60, 70, 5], "Jack": []})
#min_max_hours({})