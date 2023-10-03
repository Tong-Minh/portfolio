#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Nov  2 22:41:07 2021

@author: tong0154
"""

# Minh Tong
# Tong0154
# CSCI 1133 Section 050
# Assignment 4

#====================================
# Purpose: take a csv and a name, search the csv for the name and the # of miles associated with the name, adding them together, and returning it. errors with files return -1
# Input Parameters: a csv file and a name 
# Return Values: All real numbers if the file name is right, -1 if its not, 0 if the name isn't on the list
#====================================

def miles_run(file_name, member):
    try:
        fp = open(file_name, 'r') #opening file
        fpread = fp.read()
        fpread = fpread.split('\n')
        fp.close()
            
        for i in range(0,len(fpread)):  #splitting stuff up
            fpread[i] = (fpread[i].split(','))
        del fpread[0]
            
        miles_run = 0
        for i in fpread:   #adding up miles
            if member == i[0]:
                miles_run += int(i[1])
        
        return miles_run
    
    except:
        return -1

#miles_run("/Users/minhtong/Documents/GitHub/repo-tong0154/homeworks/hw04/hw04_supplementary/week3.csv", 'Minh')  #returns 0
#miles_run("/Users/minhtong/Documents/GitHub/repo-tong0154/homeworks/hw04/hw04_supplementary/week3.csv", 'Chandler') #returns 18