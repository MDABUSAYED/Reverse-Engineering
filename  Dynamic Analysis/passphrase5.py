#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Oct  4 21:57:52 2022

@author: msayed
"""

def passphrase5():
    
    
    f = open("text.txt","w+") 
    
    f.write("mama mia")
    
    f.close()
    
    inp = input(' Manipulate text file and enter something. ')
    
    data = open("text.txt", "r").read()
    
    data = data.split(' ')
    
    if data[0].find('toadstinks') >= 0:
        print('Correct Passphrase5')
    else:
        print('Incorrect Passphrase5')
           
def main():
    
    passphrase5()
    
if __name__ == "__main__":
    main()