#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Nov  2 21:18:08 2021

@author: tong0154
"""

# Minh Tong
# Tong0154
# CSCI 1133 Section 050
# Assignment 4

#====================================
# Purpose: returns a list of keys that repeat on a keyboard everytime you type them
# Input Parameters: Phrase = a string that contains anything, Limit = number of times a character must appear in a word to be added to the final list
# Return Values: a list called flagged_list that possibly includes numbers as strings, characters, punctuation, multiple white spaces, capitalized characters
#====================================
def flag_keys(phrase, limit=1):
    flagged_list = []
    split_phrase = phrase.split()
        
    for element in split_phrase:
        character_list = []
        
        for i in element:
            if i not in character_list:
                character_list += i
            
        for i in character_list:
            if element.count(i) > limit and i not in flagged_list:
                flagged_list += i
                
    print(flagged_list)
    return flagged_list

#flag_keys('Heeeellooo Wooorllld Wwwhaaaats uuuup', 2)  #test case returns ['e', 'o', 'l', 'a', 'u']
#flag_keys('Heeeellooo Wooorllld', 0)  #edge case returns ['H', 'e', 'l', 'o', 'W', 'r', 'd']
#flag_keys('', 12)  #edge case returns []