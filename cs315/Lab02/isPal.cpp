//////////////////////////////////////////
// Author:     Juan Martinez            //
// Student:    Juan Martinez            //
// Term:       Fall 2017                //
// Course:     CS 315                   //
// Assignment: Lab 02                   //
// Date:       9/25/17                  //
// Professor:  Dr. Kooshesh             //
// File:       isPal.cpp                //
//////////////////////////////////////////

bool isPalIterative(const char *s, int n) {
// s contains n characters. The function uses an iterative
// algorithm to determine if s contains a string that is a palindrome or
// not.

    for (int i = 0; i < n/2; i++)
    {
        if (s[i] != s[n - 1 - i])
        {
            return false;
        }
    }
    return true;
}

bool isPalRecursive(const char *s, int start, int n) {
// s contains n characters. The function uses a recursive
// algorithm to determine if s contains a string that is a palindrome or
// not. When the function is called for the first time,  start will
// contain zero, the index of the first element of s.

    if (n == 0)
        return true;
    if (n == 1)
        return true;
    if (s[start] == s[n-1])
      return isPalRecursive(s, start + 1, n - 1);
    else
      return false;
}
