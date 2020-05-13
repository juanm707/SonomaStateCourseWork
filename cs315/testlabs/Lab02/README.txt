////////////////////////////////
// Author:     Juan Martinez  //
// Term:       Fall 2017      //
// Course:     CS 315         //          ____  _____    _    ____      __  __ _____
// Assignment: Lab 02         //         |  _ \| ____|  / \  |  _ \    |  \/  | ____|
// Date:       9/25/17        //         | |_) |  _|   / _ \ | | | |   | |\/  |  _|
// Professor:  Dr. Kooshesh   //         |  _ <| |___ / ___ \| |_| |   | |  | | |___
////////////////////////////////         |_| \_\_____/_/   \_\____/    |_|  |_|_____|

FEATURES THAT WORK: All 12 Iterative and Recursive functions work. gcd works but only with positive non-zero
numbers. I was not sure what GCD of 0 would be wether in position a or b. Recursive binary search has a
helper function that does the recursive bianry search, but isMemberBinarySearchRecursive calls it to start
and does checking if the key is found. It was said that no output was to be shown by our iterative or
recursive functions, however, I was unsure about collatz since both functions have return type void. So I just
output the sequence in those functions. Collatz should be run many times since each time it outputs a new number
randomly. Every other file should be used with corresponding input file if provided (Just the search programs
use input files).

FEATURES THAT DO NOT WORK: GCD with 0 in any position, or even negative numbers. It returns a -1 if anything unsual
happens. I am unsure about my recursive binary function. It works but I am not sure if it was implemented properly.

POSSIBLE BUGS: GCD with negative numbers and 0.

                                                                                            
