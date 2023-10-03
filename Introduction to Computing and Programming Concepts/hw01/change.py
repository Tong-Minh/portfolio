#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Sep 18 19:49:48 2021

@author: tong0154
"""

# Minh Tong
# tong0154
# CSCI 1133 Section 050
# Assignment 1

change = int(input('Enter the number of cents: '))

half_dollars = change // 50       #setting each variable to the modulus of the previous variable then integer dividing by the current variables value (starts at 50)
quarters = change % 50 // 25
dimes = change % 50 % 25 // 10
nickels = change % 50 % 25 % 10 // 5
pennies = change % 50 % 25 % 10 % 5 // 1

print(half_dollars, 'half dollars')
print(quarters, 'quarters')
print(dimes, 'dimes')
print(nickels, 'nickels')
print(pennies, 'pennies')