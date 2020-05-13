//////////////////////////////////////////
// Author:     Juan Martinez            //
// Student:    Juan Martinez            //
// Term:       Fall 2017                //
// Course:     CS 315                   //
// Assignment: Lab 02                   //
// Date:       9/25/17                  //
// Professor:  Dr. Kooshesh             //
// File:       isSorted.cpp             //
//////////////////////////////////////////

bool isSortedIterative(int list[], int n) {
// list is an array with n elements. The function uses an
// iterative algorithm to return true if the numbers in the array are sorted from
// the smallest (list[0]) to the largest (list[n-1]). An empty
// list is a sorted list!

    if (n == 0)
        return true;
    if (n == 1)
        return true;

    for (int i = 0; i < n - 1; i++) {

        if (list[i] <= list[i + 1]) {
            //do nothing
        }
        else
            return false;
    }
    return true;
}

bool isSortedRecursive(int list[], int n) {
// list is an array with n elements. The function uses a
// recursive algorithm to return true if the numbers in the array are sorted from
// the smallest (list[0]) to the largest (list[n-1]). An empty
// list is a sorted list!

    if (n == 0)
        return true;
    if (n == 1)
        return true;
    if (list[n-1] > list[n-2])
        return isSortedRecursive(list, n - 1);
    return false;
}
