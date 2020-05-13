////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 1          //
// Date:       9/8/17             //
// Professor:  Dr. Kooshesh       //
// File:       Number.h           //
////////////////////////////////////

#ifndef NUMBER_NUMBER_H
#define NUMBER_NUMBER_H

#include <string>
using namespace std;

enum Romans {I = 1, IV = 4, V = 5, IX = 9,  X = 10, XL = 40, L = 50, XC = 90, C = 100, CD = 400, D = 500, CM = 900, M = 1000};
const int romanValues = 13;

class Number {
public:
    Number(int n);
    Number(std::string s);

    // is the Roman number that is stored in "strNumber" a legal Roman number?
    bool isALegalRomanNumber();

    // Return the int value of this Roman number.  If the instance was
    // created by having used a decimal number, just return it.
    // Otherwise, convert "strNumber" to its decimal counterpart and
    // return it.  Note that you may already have converted it when the
    // user called "isALegalRomanNumber".
    int intValue();

    // convert "intNumber" to its Roman counterpart and return it as a string.
    std::string romanValue();

private:
    std::string strNumber;
    int intNumber;
};


#endif //NUMBER_NUMBER_H
