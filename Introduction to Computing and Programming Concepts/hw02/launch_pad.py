#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Oct  3 15:08:31 2021

@author: minhtong
"""
# Minh Tong
# tong0154
# CSCI 1133 Section 050
# Assignment 2 
    
def launch_rocket(current_state, button):  #defining the function/if statements for choices

    if current_state == "IDLE" and button == "start_btn":  
        current_state = "READY"
        print(current_state)
        return "READY"
                
    elif current_state == "READY" and button == "safe_btn":
        current_state = "SAFE"
        print(current_state)
        return "SAFE"
                
    elif current_state == "SAFE" and button == "launch_btn":
        current_state = "LAUNCH"
        print(current_state)
        return "LAUNCH"
    
    else:
        current_state = "IDLE"
        print(current_state)
        return "IDLE"
                

        


          
    

    
