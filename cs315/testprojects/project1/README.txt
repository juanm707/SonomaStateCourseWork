/////////////////////////////				
Author:     Juan Martinez  //		
Term:       Fall 2017      //
Course:     CS 315         //	       ____  _____    _    ____      __  __ _____
Assignment: Project 1      //         |  _ \| ____|  / \  |  _ \    |  \/  | ____|
Date:       9/8/17	   //	      | |_) |  _|   / _ \ | | | |   | |\/  |  _|
Professor:  Dr. Kooshesh   //         |  _ <| |___ / ___ \| |_| |   | |  | | |___
/////////////////////////////  	      |_| \_\_____/_/   \_\____/    |_|  |_|_____|				

FEAUTURES THAT WORK: User entered expression must be begin with a lower case variable followed by an equal sign.
Spaces are not required. "a=X+X" or "a = X + X" is valid or combination of both "a = X+X". You can use variables
that have a value greater than or equal to 0 and less than 3999. If you use a variable with no previous value or its value is
not in range, then the expression results to UNDEFINED ex: "a UNDEFINED". Valid roman numerals are expected. If a
roman numeral is in bad format or not valid, an error will be thrown saying it is not legal or unrecognizable.
No digits are allowed ex: "a = 3 + X". User can use parantheses but they must be balanced. After each expression,
once user presses enter or return key, the expression will be evaluated, stored in the variable in decimal form,
but output the answer in roman numeral. If user enters "a = X + X" then output is "a equals XX". Forms that work:
a = X + X
a=X+X
a = (X + X) * V
b =       X - I
b = a - a
b = c -> but result is undefined if c not given value before
c=X+(X*V+(II+III-(I*II)))
   d      =        c     +      I
and other possible combinations.

FEATURES THAT DO NOT WORK: If user inputs nothing, or spaces, or tabs, and then presses enter/return
the program will stop and break. You can not input expression backwards "X + X = a". You can not set
value of variable to 0 by doing "a = 0" you have to do "a = I - I" or "b = a - a" if "a" is defined.
You cannot use integers.

POSSIBLE BUGS: If user inputs any variable = "X(XX)" the result will be the roman numerals together
so this will be "a equals XXX. If user does "X(XXX)", will result it UNDEFINED and an error since it
puts together XXXX which is not a legal roman numeral.


