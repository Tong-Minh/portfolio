# Minh Tong
# tong0154
# CSCI 1133 Section 050
# Assignment 3

def triples(num_list, target):
    combos = 0
    proven_combos = []
    final_combos = []
    num_list.sort()

    for one in num_list:  #first int
        possible_combos = []
        possible_combos.append(one)

        for two in num_list:  #second int
            possible_combos = [one]
            possible_combos.append(two)

            for three in num_list:  #third int
                possible_combos = [one, two]
                possible_combos.append(three)

                if sum(possible_combos) == target and len(possible_combos) == 3:
                    proven_combos.append(possible_combos)

    for i in proven_combos:  #weeding through the huge list of all combos
        i.sort()
        if i not in final_combos and (i[0] != i[1] != i[2]):
            final_combos.append(i)
            combos += 1
    
    for i in final_combos:  #printing formatting
        print(str(i[0]) + " + " + str(i[1]) + " + " + str(i[2]) + " = " + str(target))
    return combos