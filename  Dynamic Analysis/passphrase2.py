#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Sep 27 02:18:28 2022

@author: msayed
"""



def passphrase2(s):
    
    
    for i in range(len(s)):
        if s[i] == ' ':
            break
    if i + 1 == len(s):
        print('Incorrect Passphrase2')
        return
    
    var_12 = s[-1]
    var_11 = s[-2] 
    
    var_c = int(s[0: i])
    var_10 = int(s[i + 1: -2])
    
    #print(var_c, var_10, var_11, var_12)
    
    if var_11 == 'b':
        if var_12 == 'd':
            if var_c == 12 and var_c % 10 == var_10:
                print('Correct Passphrase2 ')
                return
            if var_c == 234 and var_c % 10 == var_10:
                print('Correct Passphrase2 ')
                return
        if var_12 == 'r':
            if var_c == 11 and var_c % 10 == var_10:
                print('Correct Passphrase2 ')
                return
            if var_c == 21 and var_c == var_10:
                print('Correct Passphrase2 ')
                return
            if var_c == 32 and var_c - 42 == var_10:
                print('Correct Passphrase2 ')
                return
    if var_11 == 'd':
        if var_c == 2 and var_12 == 'r' and var_10 == var_c + 20:
            print('Correct Passphrase2 ')
            return
        if var_c == 5 and var_12 == 'n' and var_10 == var_c + 10:
            print('Correct Passphrase2 ')
            return
    print('Incorrect Passphrase2')



def main():
    
    s = input("Enter Passphrase2: ")
    passphrase2(s)
    
    
if __name__ == "__main__":
    main()