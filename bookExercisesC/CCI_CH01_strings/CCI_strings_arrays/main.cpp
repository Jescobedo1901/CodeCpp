/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: housewife
 * Purpose: Cracking the Coding Interview Chapter One Sample Problems
 * Created on February 4, 2018, 4:27 PM
 */

//Includes
#include "chapterOneFunctions.h"
using namespace std;

//Unit Test declarations
void unitTestisUnique();
void unitTestPermutation();
void unitTestURLify();
void unitTestPalindrome();
void unitTestOneAway();

/*
 * 
 */
int main(int argc, char** argv) {

    /*
     * 1.1 Is Unique
     * Implement an algorithm to determine if a string has all unique characters
     * What if you cannot use additional data structures?
     */
    unitTestisUnique();
    unitTestPermutation();
    unitTestURLify();
    unitTestPalindrome();
    unitTestOneAway();
    
    
    return 0;
}

void unitTestisUnique() {
    //Unicode or ASCII?
    //Assume ASCII for testing purposes
    //Assume 256 Characters total
    cout << "_____________________Is Unique_________________________________\n";
    cout << "Implement an algorithm to determine if a string has all unique \n"
        << "characters. What if you cannot use additional data structures?" << endl;
    cout << "_______________________________________________________________\n";
    string strT = "abcdefg123";
    string strF = "aaaabcdefg22";
    cout << "\nTest string: " << strT << endl;
    cout << "Returns: " << isUnique(strT) << endl;
    cout << "\nTest string: " << strF << endl;
    cout << "Returns: " << isUnique(strF) << endl;
    cout << endl;
    cout << "-------------------- End Unit Test: isUnique ------------------\n";
    cout << endl;
    
}

void unitTestPermutation() {
    
    cout << "_____________________Check Permutation_________________________\n";
    cout << "Given two strings, write a method to decide if one is a \n"
        << "permutation of the other." << endl;
    cout << "_______________________________________________________________\n";
    string str1 = "cattop";
    string str2 = "actotp";
    cout << "\nTest pair..." << endl;
    cout << "String One: " << str1 << endl;
    cout << "String Two: " << str2 << endl;
    cout << "True or False: " << permutation(str1, str2) << endl;
    
    str1 = "cattxw";
    str2 = "actotp";
    cout << "\nTest pair..." << endl;
    cout << "String One: " << str1 << endl;
    cout << "String Two: " << str2 << endl;
    cout << "True or False: " << permutation(str1, str2) << endl;
    
    cout << endl;
    cout << "-------------------- End Unit Test: Permutation ---------------\n";
    cout << endl;
}

void unitTestURLify() {
    
    cout << "_____________________URLify____________________________________\n";
    cout << "Write a function to replace all spaces in a string with '%20'. \n"
            << "You may assume that the string has enough space to hold all\n"
            << "additional characters. The true length is also given" << endl;
    cout << "_______________________________________________________________\n";
    char * str = new char[17];
    string test = "I'm Sofa King";
    int size = test.length();
    for (int i = 0; i < size; i++) {
        str[i] = test[i];
    }
    cout << "\nTest string: " << str << endl;
    URLify(str, size);
    cout << "Result: " << str << endl;    
    test = "Also a potato";
    size = test.length();
    str = new char[17];
    for (int i = 0; i < size; i++) {
        str[i] = test[i];
    }
    cout << "\nTest string: " << str << endl;
    URLify(str, size);
    cout << "Result: " << str << endl;
    
    cout << endl;
    cout << "-------------------- End Unit Test: URLify --------------------\n";
    cout << endl;
}

void unitTestPalindrome() {
    
    cout << "_____________________Palindrome________________________________\n";
    cout << "Given a string, write a function to check if it is a permutation\n"
            << "of a paldindrome." << endl;
    cout << "_______________________________________________________________\n";
    
    string str = "Tact Coa";
    cout << "\nTest string: " << str << endl;
    cout << "Result: " << palindrome(str) << endl;
    
    str = "Chocolate";
    cout << "\nTest string: " << str << endl;
    cout << "Result: " << palindrome(str) << endl;
    
    cout << endl;
    cout << "-------------------- End Unit Test: Palindrome ----------------\n";
    cout << endl;
}

void unitTestOneAway() {
    
    cout << "_____________________One Away__________________________________\n";
    cout << "Check to see if two strings are one edit away\n";
    cout << "_______________________________________________________________\n";
    
    string strb = "hale";
    string str1 = "bale";
    string str2 = "hle";
    string str3 = "haele";
    string str4 = "baele";
    cout << "\nTest Group...compare to base String" << endl;
    cout << "String Base: " << strb << endl;
    cout << "String One: " << str1 << " :: T/F: " << oneAway(strb, str1) << endl;
    cout << "String Two: " << str2 << " :: T/F: " << oneAway(strb, str2) << endl;
    cout << "String Three: " << str3 << " :: T/F: " << oneAway(strb, str3) << endl;
    cout << "String Four: " << str4 << " :: T/F: " << oneAway(strb, str4) << endl;
    
    
    cout << endl;
    cout << "-------------------- End Unit Test: One Away ------------------\n";
    cout << endl;
}