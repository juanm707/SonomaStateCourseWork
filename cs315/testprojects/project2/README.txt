////////////////////////////////
// Author:     Juan Martinez  //
// Term:       Fall 2017      //
// Course:     CS 315         //          ____  _____    _    ____      __  __ _____
// Assignment: Project 2      //         |  _ \| ____|  / \  |  _ \    |  \/  | ____|
// Date:       9/28/17        //         | |_) |  _|   / _ \ | | | |   | |\/  |  _|
// Professor:  Dr. Kooshesh   //         |  _ <| |___ / ___ \| |_| |   | |  | | |___
////////////////////////////////         |_| \_\_____/_/   \_\____/    |_|  |_|_____|

FEATURES THAT WORK: All non-extra credit functions work as expected. They do not do any checking on the input
for example if it has to be an atom, or a list of atoms. If the wrong input is entered, then usually cdr or car will
create an error and exit. 

FEATURES THAT DO NOT WORK: Permute was not implemented. List_union works, but only with both p and q being considered
sets. That is, p and q have no duplicate atoms ( a a b c ) <- wrong form. It should be ( a b c ). Each atom only appearing once
in each list. If user enters (as an example), for list_union, ( a b c o ) for p and ( a d e c f b z ) for q, the result is the union which is
( o a d e c f b z ). BUT if input is ( a a b c ) and ( d e b ), the result is ( a a c d e b ). And vice versa if q had duplicate "a".

POSSIBLE BUGS: List_union duplicate issue.

                                                                                            
