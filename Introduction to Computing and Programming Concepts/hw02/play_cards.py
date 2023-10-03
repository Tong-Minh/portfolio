#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Oct  3 13:15:36 2021

@author: minhtong
"""

# Minh Tong
# tong0154
# CSCI 1133 Section 050
# Assignment 2 

import random

def play_cards():  #defining the function
    insignificant = 0  #placeholder cause index starts at 0
    a = 0  #for human
    b = 0
    c = 0
    d = 0  #for computer
    e = 0
    f = 0
    
    while a == b or b == c or a == c:  #drawing cards f/human
        a = random.randint(1, 10)
        b = random.randint(1, 10)
        c = random.randint(1, 10)
    
    while d == e or e == f or f == d:  #drawing cards f/computer
        d = random.randint(1, 10)
        e = random.randint(1, 10)
        f = random.randint(1, 10)
        
    card_index = [insignificant, a, b, c]  #indexing human/computer cards
    computer_index = [insignificant, d, e, f]
    
    player_wins = 0  #defining player/computer wins
    computer_wins = 0
    
    print("Game Starts!")
    print("Player's cards: " + str(a) + ", " + str(b) + ", " + str(c))
    
    x = "100"  #variables set to use later
    y = "101"
    z = "102"
    computer_choice = 0
    rounds = 0
    
    while rounds <=2:  #while statement makes it so you can't pick the same card
            rounds += 1  #adding a round each iteration until three
            computer_choice += 1  #computer choosing its cards in the order drawn
            print("Round " + str(rounds) +  ":")
            player_choice = int(input("\tEnter player card index: "))
    
            if player_choice < 1 or player_choice > 3:  #if statement makes selections not 1-3 invalid
                print("\tInvalid your cards selection can only be (1-3)")
                return

            player_card = card_index[player_choice]  #using these _card variables to call the index assignment
            computer_card = computer_index[computer_choice]
            
            if rounds == 1:  #more repeating card preventions
                x = player_choice
            elif rounds == 2:
                y = player_choice
            elif rounds == 3:
                z = player_choice
            
            if x == y or y == z or z == x:  #more repeating card preventions
                print("Invalid you cannot play the same card twice")
                return
          
            if player_choice == 1:  #nested if statements for scoring and turns
                print("\tYou Played: " + str(player_card) + ", Computer Played: " + str(computer_card))
                if player_card > computer_card:
                    player_wins += 1
                    print("\tScore: Player " + str(player_wins) + ", Computer " + str(computer_wins))
                elif player_card < computer_card:
                    computer_wins += 1
                    print("\tScore: Player " + str(player_wins) + ", Computer " + str(computer_wins))
                elif player_card == computer_card:
                    print("\tScore: Player " + str(player_wins) + ", Computer " + str(computer_wins))
                    
            elif player_choice == 2:  #nested if statements for scoring and turns
                print("\tYou Played: " + str(player_card) + ", Computer Played: " + str(computer_card))
                if player_card > computer_card:
                    player_wins += 1
                    print("\tScore: Player " + str(player_wins) + ", Computer " + str(computer_wins))
                elif player_card < computer_card:
                    computer_wins += 1
                    print("\tScore: Player " + str(player_wins) + ", Computer " + str(computer_wins))
                elif player_card == computer_card:
                    print("\tScore: Player " + str(player_wins) + ", Computer " + str(computer_wins))
                    
            elif player_choice == 3:  #nested if statements for scoring and turns
                print("\tYou Played: " + str(player_card) + ", Computer Played: " + str(computer_card))
                if player_card > computer_card:
                    player_wins += 1
                    print("\tScore: Player " + str(player_wins) + ", Computer " + str(computer_wins))
                elif player_card < computer_card:
                    computer_wins += 1
                    print("\tScore: Player " + str(player_wins) + ", Computer " + str(computer_wins))
                elif player_card == computer_card:
                    print("\tScore: Player " + str(player_wins) + ", Computer " + str(computer_wins))
        
            
    if player_wins > computer_wins:  #endgame mechanism that tells you who won
        print("Winner: Player")
    elif player_wins < computer_wins:
        print("Winner: Computer")
    elif player_wins == computer_wins:
        print("No Winner: Tie")
    
    