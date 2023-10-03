#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct  2 19:48:30 2021

@author: minhtong
"""

# Minh Tong
# tong0154
# CSCI 1133 Section 050
# Assignment 2

def oral_exam_sign_up(start_time, end_time, lunch_time): 
    
    if 0 < end_time < 8:  #gets the amount of total iterations to run the for statement, cuts off at 8 because I thought start time could be either am or pm
        iterations_total = 4 * ((end_time + 12) - start_time) 
    elif end_time == 12 and end_time > start_time:
        iterations_total = 4 * (end_time - start_time) 
    elif 8 <= end_time < 12 and end_time > start_time:
        iterations_total = 4 * (end_time - start_time) 
    
    if 8 <= lunch_time <= 12:  #gets the number of iterations until lunch
        til_lunch = 4 * (lunch_time - start_time)
    elif 0 < lunch_time < 8:
        til_lunch = 4 * ((12 + lunch_time) - start_time)
    remaining_iterations = iterations_total - til_lunch  #gets the remaining iterations until the end of the day
    slots = iterations_total - 2 #requirement
    
    minutes = 0  #defining minutes and quarters, as in quarters of the hour
    quarter = 0
    
    for x in range(0, til_lunch):  #prints all the iterations until lunch time
            if quarter != 4:
                quarter += 1
                
                if quarter == 1:  #Any first quarter of an hour starts with x:00, must be different
                    first = str(start_time) + ':' + '00'
                    minutes += 10
                    print(first + "-" + str(start_time) + ':' + str(minutes))
                    minutes += 5
                    
                elif quarter > 1:  #runs three times for every hour, prints 3 time slots
                    second = str(start_time) + ':' + str(minutes) 
                    print(second + "-" + str(start_time) + ':', end='')
                    minutes += 10
                    print(str(minutes))
                    minutes += 5
        
            elif quarter == 4:  #dictactes what happends at the turn of every hour
                minutes = 0
                
                if start_time <= 11:  #adds hour every iteration 
                    start_time += 1
                    quarter = 0
                    
                    first = str(start_time) + ':' + '00'  #ensures no loss of iteration
                    minutes += 10
                    print(first + "-" + str(start_time) + ':' + str(minutes))
                    minutes += 5
                    quarter = 1
                    
                elif start_time >= 12:  #resets the clock
                    start_time = 0
                    start_time += 1
                    quarter = 0
                    
                    first = str(start_time) + ':' + '00'  #ensures no loss of iteration
                    minutes += 10
                    print(first + "-" + str(start_time) + ':' + str(minutes))
                    minutes += 5
                    quarter = 1
                     
    if lunch_time == 1: #resets the clock if lunch = 1
        start_time = 0
    start_time += 1  #accounts for lunch and sets all variables where they should be
    minutes = 30
    quarter = 2

    for x in range(0, remaining_iterations - 2):  #prints the rest of the iterations after lunch time, -2 to account for lunch slots
            if quarter != 4:
                quarter += 1
                
                if quarter == 1:  #Any first quarter of an hour starts with x:00, must be different
                    first = str(start_time) + ':' + '00'
                    minutes += 10
                    print(first + "-" + str(start_time) + ':' + str(minutes))
                    minutes += 5
                    
                elif quarter > 1:  #runs three times for every hour, prints 3 time slots
                    second = str(start_time) + ':' + str(minutes) 
                    print(second + "-" + str(start_time) + ':', end='')
                    minutes += 10
                    print(str(minutes))
                    minutes += 5
        
            elif quarter == 4:  #dictactes what happends at the turn of every hour
                minutes = 0
                
                if start_time <= 11:  #adds hour every iteration
                    start_time += 1
                    quarter = 0
                    
                    first = str(start_time) + ':' + '00'  #ensures no loss of iteration
                    minutes += 10
                    print(first + "-" + str(start_time) + ':' + str(minutes))
                    minutes += 5
                    quarter = 1
                    
                elif start_time >= 12:  #resets the clock
                    start_time = 0
                    start_time += 1
                    quarter = 0
                    
                    first = str(start_time) + ':' + '00'  #ensures no loss of iteration
                    minutes += 10
                    print(first + "-" + str(start_time) + ':' + str(minutes))
                    minutes += 5
                    quarter = 1
                    
    return slots
