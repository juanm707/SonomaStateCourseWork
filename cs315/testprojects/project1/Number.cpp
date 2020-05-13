////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 1          //
// Date:       9/8/17             //
// Professor:  Dr. Kooshesh       //
// File:       Number.cpp         //
////////////////////////////////////

#include "Number.h"

using namespace std;

Number::Number(int n) {

    if (-1 >= n || n > 3999) //if not in range set undefined
        intNumber = -1;
    else {
        intNumber = n;
        strNumber = romanValue();
    }
}

Number::Number(std::string s) {
    strNumber = s;
    intNumber = 0;
}

bool Number::isALegalRomanNumber() {

    int check = intValue();
    intNumber = check;

    return strNumber == romanValue();
}

//convert to int
int Number::intValue() {

    if (intNumber >= 1)
        return intNumber;
    if (intNumber == -1)
        return intNumber;

    int value = 0; // value of roman numeral

    for (int i = 0; unsigned(i) < strNumber.length(); i++) {

        int c1 = 0;
        if (strNumber[i] == 'I')
            c1 = I;
        else if (strNumber[i] == 'V')
            c1 = V;
        else if (strNumber[i] == 'X')
            c1 = X;
        else if (strNumber[i] == 'L')
            c1 = L;
        else if (strNumber[i] == 'C')
            c1 = C;
        else if (strNumber[i] == 'D')
            c1 = D;
        else if (strNumber[i] == 'M')
            c1 = M;
        else
            c1 = 0;
        //---------------------------------
        // check adjacent value
        if (unsigned(i + 1) < strNumber.length()) {
            int c2 = 0;
            if (strNumber[i + 1] == 'I')
                c2 = I;
            else if (strNumber[i + 1] == 'V')
                c2 = V;
            else if (strNumber[i + 1] == 'X')
                c2 = X;
            else if (strNumber[i + 1] == 'L')
                c2 = L;
            else if (strNumber[i + 1] == 'C')
                c2 = C;
            else if (strNumber[i + 1] == 'D')
                c2 = D;
            else if (strNumber[i + 1] == 'M')
                c2 = M;
            else
                c2 = 0;
            //-----------------------------
            if (c1 >= c2)
                value += c1;
            else {
                value += c2 - c1;
                i++; // since subtraction only use once in a row skip to next value
            }
        }
            //if it is the last roman numeral
        else {
            value += c1;
            i++;
        }
    }

    return value;
}

//convert int to string
std::string Number::romanValue() {

    int copyIntNum = intNumber;
    if (copyIntNum == 0)
        return "0";
    if (copyIntNum == -1)
        return "UNDEFINED";

    Romans romArray[romanValues] = {M, CM, D, CD, C, XC, L, XL, X, IX, V, IV, I};
    string romStrArray[romanValues] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    string resString = "";
    for (int i = 0; i < romanValues; i++) {
        while ((copyIntNum % romArray[i]) < copyIntNum) {
            resString += romStrArray[i];
            copyIntNum -= romArray[i];
        }
    }
    return resString;
}
