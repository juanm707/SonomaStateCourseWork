//////////////////////////////////////////
// Author:     Juan Martinez            //
// Student:    Juan Martinez            //
// Term:       Fall 2017                //
// Course:     CS 315                   //
// Assignment: Lab 02                   //
// Date:       9/25/17                  //
// Professor:  Dr. Kooshesh             //
// File:       isMemberBinarySearch.cpp //
//////////////////////////////////////////

int helperBinarySearch(int list[], int key, int start, int last) {

    if (start > last)
        return -1;

    int mid = (start + last)/2;
    
    if (list[mid] < key)
        return helperBinarySearch(list, key, mid + 1, last);
    else if (list[mid] > key)
        return helperBinarySearch(list, key, start, mid - 1);
    else
      return mid;
}

bool isMemberBinarySearchIterative(int list[], int n, int key) {
// list contains n ordered elements. The function uses an iterative
// solution to determine if key is a member of the list or not. That is,
// it returns true if there is an i, 0 < i < n,
// and list[i] == key. Otherwise, the function returns false.

    int first = 0;
    int last = n - 1;

    while (first <= last) {

        int mid = (first + last) / 2;

        if (list[mid] > key)
            last = mid - 1;
        else if (list[mid] < key)
            first = mid + 1;
        else if (list[mid] == key)
            return true;
    }

    return false;
}

bool isMemberBinarySearchRecursive(int list[], int n, int key) { // FINISH THIS ONE //////////////
// list contains n ordered elements. The function uses a recursive
// solution to determine if key is a member of the list or not. That is,
// it returns true if there is an i, 0 < i < n,
// and list[i] == key. Otherwise, the function returns false. Hint: you may
// have to define another function (a helper function) that would take more
// arguments than provided here. Think about the role of the parameter start
// in the recursive function-prototype for the palindrome problem above.

    int index = helperBinarySearch(list, key, 0, n); // 0 is start of array
    if (index == -1)
        return false;
    else if (list[index] == key)
        return true;
    else
      return false;
}
