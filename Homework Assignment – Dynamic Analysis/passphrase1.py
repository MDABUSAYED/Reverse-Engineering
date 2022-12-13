#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Sep 27 02:18:28 2022

@author: msayed
"""



def passphrase1(s):
    
    
    if s == 'It\'s time for a Bowser Revolution!':
        print('Correct Passphrase1 ')
    else:
        print('Incorrect Passphrase1 ')
    



def main():
    
    s = input("Enter Passphrase1: ")
    passphrase1(s)
    
    
if __name__ == "__main__":
    main()