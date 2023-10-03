# Minh Tong
# tong0154
# CSCI 1133 Section 050
# Assignment 5

#==========================================
# Purpose: takes a base number to the power of every number up till the value n 
# Input Parameter(s): takes a base number and n value 
# Return Value(s): returns a list of numbers from 1 to base ** n
#==========================================

def nth_base_seq(base, n):
    if n == 0:
        return [1]
    return nth_base_seq(base, n - 1) + [base ** n]

print(nth_base_seq(4, 4))