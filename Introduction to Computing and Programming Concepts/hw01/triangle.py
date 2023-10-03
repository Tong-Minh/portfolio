#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Sep 18 20:05:33 2021

@author: tong0154
"""

# Minh Tong
# tong0154
# CSCI 1133 Section 050
# Assignment 1

import math

side_b = float(input("Enter shorter side (b): "))    #defining variables
angle_a = float(input("Enter angle between sides in degrees (A): "))
side_c = float(input("Enter other side (c): "))    

angle_a /= (180 / math.pi)    #converting angle a to a radian
side_a = math.sqrt((side_b ** 2) + (side_c ** 2) - (2 * side_b * side_c) * ((math.cos(angle_a))))
angle_b = (math.asin(math.sin(angle_a) / side_a * side_b)) * (180 / math.pi)
angle_c = 180 - (angle_a * (180 / math.pi) + angle_b)

print("Angle B is", angle_b)
print("Side a is", side_a)
print("Angle C is", angle_c)
