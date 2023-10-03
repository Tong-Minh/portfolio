# Minh Tong
# tong0154
# CSCI 1133 Section 050
# Assignment 3

def base_five(num):
    remainders = []
    new_remainders = []

    while num != 0:
        remainders.append(num % 5)
        num = num // 5
    remainders.reverse()

    for i in remainders:
        new_remainders.append(str(i))

    x = "".join(new_remainders)
    return x