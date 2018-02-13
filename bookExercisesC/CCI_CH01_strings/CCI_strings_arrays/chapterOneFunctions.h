/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   chapterOneFunctions.h
 * Author: housewife
 *
 * Created on February 4, 2018, 4:40 PM
 */

#ifndef CHAPTERONEFUNCTIONS_H
#define CHAPTERONEFUNCTIONS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

bool isUnique(string str) {
    //Here we implement either Unicode Maximum or ASCII Maximum
    //Assume 256 for now
    int max = 256;
    char * test = new char[max];
    int size = str.length();
    for (int i = 0; i < size; i++) {
        test[str[i]]++;
    }
    
    for (int i = 0; i < max; i++) { //No char can be more than 1
        if (test[i] > 1) {
            return false;
        }
    }
    
    return true;
}

bool permutation(string str1, string str2) {
    //Here we implement either Unicode Maximum or ASCII Maximum
    //Assume 256 for now
    int max = 256;
    char * test1 = new char[max];
    char * test2 = new char[max];
    int size1 = str1.length();
    int size2 = str2.length();
    
    //Sizes must be the same
    if (size1 != size2) {
        return false;
    }
    
    for (int i = 0; i < size1; i++) { 
        test1[str1[i]]++;
        test2[str2[i]]++;
    }
    
    for (int i = 0; i < max; i++) { //Make sure same number of each char
        if (test1[i] != test2[i]) {
            return false;
        }
    }
    
    return true;
}

void URLify(char* str, int tsize) {
    int spaceCount = 0;
    for (int i = 0; i < tsize; i++) {
        if (str[i] == ' ') {
            spaceCount++;
        }
    }
    int size = tsize + 2*spaceCount-1;
    
    for (int i = 0; i < tsize; i++) { //Start from end of string and work back
        if (str[tsize-i-1] == ' ') {
            str[size] = '0';
            str[size-1] = '2';
            str[size-2] = '%';
            size -= 2;
        } else {
            str[size] = str[tsize-1-i];
        }
        size--;
    }   
}

bool palindrome(string str) {
    //Assume ASCII 256 characters
    int max = 256;
    bool odd = false;
    int * test = new int[max];
    
    for (int i = 0; i < max; i++) {
        test[i] = 0;
    }
    
    int size = str.length();
    for (int i = 0; i < size; i++) {
        char c = tolower(str[i]);
        int x = toascii(c);
        if (c == ' ') {
            
        } else {
            test[x]++;
        }
    }
    for (int i = 0; i < max; i++) {
        if (test[i]%2 == 1) { //If more than 2 odds, not a palindrome
            if (odd == true) {
                return false;
            } else {
                odd = true;
            }
        }
    }
    
    
    
    return true;
}

bool checkOne(string str1, string str2, bool count) {
    //str1 is always assumed to be shorter than str2
    int size1 = str1.length();
    int size2 = str2.length();
    int index = 0;
    for (int i = 0; i < size1; i++) {
        if (str1[i] != str2[i+index])
            //If they're unequal length, and when shifted aren't equal
            //Then return false, otherwise shift by 1 and try again.
            if (count == true && (str1[i] != str2[i+1])) {
                return false;
            } else {
                if (size1 == size2) {
                    count = true;
                } else {
                    count = true;
                    index++;
                }
            }
    }
    
    return true;
}

bool oneAway(string str1, string str2) {
    int size1 = str1.length();
    int size2 = str2.length();
    bool count = false;
    int diff = size1 - size2; //if negative, then size2 is greater
    //If two characters away, false
    if (abs(diff) > 1) {
        return false;
    }
    
    if (size1 != size2) {
        count = true;
        if (diff > 0) {
            return checkOne(str2, str1, count);
        }
    }
    
    return checkOne(str1, str2, count);
}

#endif /* CHAPTERONEFUNCTIONS_H */

