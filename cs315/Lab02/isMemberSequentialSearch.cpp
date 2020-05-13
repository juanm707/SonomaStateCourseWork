//////////////////////////////////////////////
// Author:     Juan Martinez                //
// Student:    Juan Martinez                //
// Term:       Fall 2017                    //
// Course:     CS 315                       //
// Assignment: Lab 02                       //
// Date:       9/25/17                      //
// Professor:  Dr. Kooshesh                 //
// File:       isMemberSequentialSearch.cpp //
//////////////////////////////////////////////

bool isMemberSequentialSearchIterative(int list[], int n, int key) {
// list contains n unordered elements. The function uses an iterative
// solution to determine if key is a member of the list or not. That is,
// it returns true if there is an i, 0 < i < n,
// and list[i] == key. Otherwise, the function returns false.

    for (int i = 0; i < n; i++) {
        if (list[i] == key)
            return true;
    }
    return false;
}

bool isMemberSequentialSearchRecursive(int list[], int n, int key) {
// list contains n unordered elements. The function uses a recursive
// solution to determine if key is a member of the list or not. That is,
// it returns true if there is an i, 0 < i < n,
// and list[i] == key. Otherwise, the function returns false.

    if (n == 0)
        return false;
    if ( list[n - 1] == key)
        return true;
    return isMemberSequentialSearchIterative(list, n - 1, key);
}

