#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct  3 17:15:50 2022

@author: msayed
"""


    
def passphrase4(s):
    
    
    
    if len(s) != 1024:
        print('Incorrect Passphrase4')
        return
    
    string = ''
    
    string += chr(s[70])
    string += chr(s[140])
    string += chr(s[170])
    string += chr(s[168])
    string += chr(s[999])
    
    
    if string == 'peach':
        print('Correct Passphrase4')
    else:
        print('Incorrect Passphrase4')
           
        
        


def main():
    
    data = open("bowsers_junk.bin", "rb").read()
    
    passphrase4(data)
    
    
    
if __name__ == "__main__":
    main()