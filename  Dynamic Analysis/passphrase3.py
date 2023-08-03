#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Sep 27 02:18:28 2022

@author: msayed
"""



def passphrase3(s):
    
    nums = s.split(' ')
    nums = [int(num) for num in nums]
    if len(nums) != 6:
        print('Incorrect Passphrase3')
        return
    if nums[0] != 120:
        print('Incorrect Passphrase3')
        return
    
    for var_c in range(1,6):
        prev = nums[var_c - 1]
        ecx = nums[var_c]
        eax = prev * 3435973837
        edx = eax // 4294967296 # FFFFFFFFh + 1
        edx = edx // 4
        eax = var_c - 1
        eax *= edx
        eax *= 8
        eax += 35
        if ecx != eax:
            print('Incorrect Passphrase3')
            return
    
    print('Correct Passphrase3')
        



def main():
    
    s = input("Enter Passphrase3: ")
    passphrase3(s)
    
    
if __name__ == "__main__":
    main()