# Minh Tong
# tong0154
# CSCI 1133 Section 050
# Assignment 5

#==========================================
# Purpose: takes a list of numbers, strings, lists, or tuples and recursively counts the amount of objects that aren't numbers
# Input Parameter(s): takes a list that can be filled withcomplex numbers, floats, integers, nested lists, nested tuples, or strings
# Return Value(s): returns a counting number
#==========================================

def count_non_numbers(input_list):
    if input_list == []:
        return 0
    else:
        #print(isinstance(input_list[0], int), isinstance(input_list[0], float), isinstance(input_list[0], list))
        #print(input_list)
        if isinstance(input_list[0], int) or isinstance(input_list[0], float) or isinstance(input_list[0], complex):
            return 0 + count_non_numbers(input_list[1:])
        elif isinstance(input_list[0], list):
            return 1 + count_non_numbers(input_list[0]) + count_non_numbers(input_list[1:])
        elif isinstance(input_list[0], tuple):
            return 1 + count_non_numbers(input_list[0]) + count_non_numbers(input_list[1:])
        else: 
            return 1 + count_non_numbers(input_list[1:])

#print(count_non_numbers([8, 'hello', 7, 8, 1.4, '124', 'wassup']))
