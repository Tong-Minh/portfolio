#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Nov  2 22:42:03 2021

@author: tong0154
"""

# Minh Tong
# Tong0154
# CSCI 1133 Section 050
# Assignment 4

#====================================
# Purpose: main function calls all helper functions and returns a winner, helper functions send values back to the main function of either None, or the winning character
# Input Parameters: a nested list in the form of a tic tac toe board
# Return Values: Draw, a character, or bad list
#====================================

def find_winner(board):
    try:
        total_list, character_list = [], []  #assigns player one and two a character each
        for i in board:
            for character in i:
                total_list += character
        for character in total_list:
            if character not in character_list:
                character_list += character
        player1 = character_list[0]
        player2 = character_list[1]
        
        def vertical(board):
            column1, column2, column3 = [], [], []   #making lists out of verticals
            column1 += board[0][0], board[1][0], board[2][0]
            column2 += board[0][1], board[1][1], board[2][1]
            column3 += board[0][2], board[1][2], board[2][2]
    
            if column1.count(player1) == 3 or column2.count(player1) == 3 or column3.count(player1) == 3: #returns winning character if theres a vertical win
                return player1
            elif column1.count(player2) == 3 or column2.count(player2) == 3 or column3.count(player2) == 3:
                return player2
        
        def horizontal(board): #returns winning character if theres a horizontal win
            for i in board:
                if i.count(player1) == 3:
                    return player1
                elif i.count(player2) == 3:
                    return player2
    
        def diagonal(board):
            diagonal_LR, diagonal_RL, index, index_reverse = [],[], 0, 2 #making lists out of diagonals
            for i in board:
                diagonal_LR += i[index]
                index += 1
            for i in board:
                diagonal_RL += i[index_reverse]
                index_reverse -= 1
    
            if diagonal_LR.count(player1) == 3 or diagonal_RL.count(player1) == 3: #returns winning character if theres a diagonal win
                return player1
            elif diagonal_LR.count(player2) == 3 or diagonal_RL.count(player2) == 3:
                return player2
        
        Hori = horizontal(board)  #calling all the helper functions and putting the returns into a list
        Diag = diagonal(board)
        Vert = vertical(board)
        winners_list = [Hori, Diag, Vert]
        
        for i in winners_list:  #checking the list for winners and if theres a draw
            if i != None:
                winner = i
                print(winner)
                return winner
            elif winners_list.count(None) == 3:
                print("Draw")
                return 'Draw'
            
    except:
        print("Bad list")
        return "Bad list"
    
#find_winner([['a', 'B', 'a'], #returns a
             #['a', 'B', 'B'],
             #['a', 'a', 'B']])
#find_winner([['2', '2', '@'], #returns 2
             #['2', '2', '@'],
             #['@', '@', '2']])
#find_winner([['X', 'O', 'X'], #returns Draw
             #['X', 'X', 'O'],
             #['O', 'X', 'O']])
#find_winner([['a', 'B', 'a'], #returns B
             #['B', 'B', 'B'],
             #['a', 'a', 'B']])
#find_winner([1,2,3]) #returns Bad list
