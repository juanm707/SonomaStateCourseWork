//////////////////////////////////////////
// Author:     Dr. Kooshesh             //
// Student:    Juan Martinez            //
// Term:       Fall 2017                //
// Course:     CS 315                   //
// Assignment: Lab 02                   //
// Date:       9/25/17                  //
// Professor:  Dr. Kooshesh             //
// File:       isPal_main.cpp           //
//////////////////////////////////////////

#include "isPal.hpp"

std::string lowerAndRemoveNonLetterChars(std::string s)
{
    std::string lettersOnly = "";
    for(int i = 0; unsigned(i) < s.length(); i++ )
        if( isalpha(s[i]) )
            lettersOnly += tolower(s[i]);
    return lettersOnly;
}

void palcheck(std::string p)
{
    std::cout << "String: " << p << std::endl;
    if( isPalIterative(p.c_str(), p.length()) )
        std::cout << "Iterative version: is a palindrome.\n";
    else
        std::cout << "Iterative version: is not a palindrome.\n";

    if( isPalRecursive(p.c_str(), 0, p.length()) )
        std::cout << "Recursive version: is a palindrome.\n";
    else
        std::cout << "Recursive version: is not a palindrome.\n";

    std::cout << std::endl;
}

int main() {
    // "A man, a plan, a canal -- Panama"

    std::string palStr = lowerAndRemoveNonLetterChars(std::string("A man, a plan, a canal -- Panama"));

    // palindromes
    palcheck(palStr);
    palcheck("anna");
    palcheck("racecar");

    palStr = lowerAndRemoveNonLetterChars(std::string("go hang a salami i'm a lasagna hog"));
    palcheck(palStr);

    // not palindromes
    palcheck("anza");
    palcheck("racebar");
    palcheck("this is in no way a palindrome");
    return 0;
}
