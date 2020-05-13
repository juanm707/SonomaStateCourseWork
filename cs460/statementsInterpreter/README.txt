Spring 2020, CS470 - Programming Languages
Final Project - Python Interpreter
Student: Juan Martinez

HOW TO COMPILE CODE
-------------------
  1. Use the 'make' command to make the executable 'statement.x'
  2. Then run using './statement.x tests/inputfile.py'

  You can also run all the tests using the bash script 'inputs.sh' which can be ran
  using './inputs.sh'

  This will go through all the test inputs, and you have to press enter after each
  one to continue.

FEATURES THAT WORK and CORRESPONDING TESTS
------------------------------------------
  * ALL TESTS ARE IN THE SUBDIRECTORY 'tests'
  * ONLY SPACES ARE ALLOWED FOR INDENTING
  * There is one test that reports an ident error and is suppose to do that
 
  A) Data types: integers, doubles, booleans (which are represented as integers...), strings and their various operations
     such as addition, subtraction, multiplication, division and integer division, modulus,
     relational operators (<, <=, <>, !=, == etc.), string concatenation and the like are supported.
     Both assignment statements and print statements can use what was stated above and any other statement using a 'test'.
     
     INPUT FILES TO TEST: input1.py 
                          input2.py
                          input3.py
			  input12.py

  B) If statements: If statements work as expected, you can nested ifs as well, ifs without elif or else. Indentation should
     work as expected, but no tabs are allowed, only spaces.

     INPUT FILES TO TEST: input4.py
       			  input5.py
			  input6.py
			  input7.py
			  input8.py
		 	  input9.py
			  input10.py
			  input11.py

  C) For statements: For statements work as expected, can have nested for statements as well. Range can take 1, 2, or 3 arguments.

     INPUT FILES TO TEST: input1.py
		          input3.py
		          input4.py
     			  input13.py
			  input14.py
			  input17.py

  D) Arrays: Arrays work, empty arrays and same type arrays work. Array operations work pop, (append, push), subscripting or indexing
     works as well. Arrays passed by reference in functions. 

     INPUT FILES TO TEST: input14.py
			  input15.py
   			  input16.py

  E) Functions: Most functions work. However no recursion works yet. Scopes should work appropriately. 
 
     INPUT FILES TO TEST: input19.py
			  input20.py
   			  input21.py

  F) Other:
       These were used for testing indentations (although technically all of them do...)

       INPUT FILES TO TEST: input17.py
                            input18.py

  Please look the tests before running so you can expect what is suppose to be the output, and/or stored
  in the symbol tables.

  * Some tests have aspects of more than 1 features

FEATURES THAT DON'T WORK and CORRESPONDING TESTS
------------------------------------------------
  Recursive functions are not implemented so they do not work.
  There may be a bug with print statements while using parentheses in some specific cases.
  
  TODOS:
    There are some TODOs commented in the code. Some include, checking array has same type of elements, checking if
    number of arguments are same as number of parameters.

Feel free to make any of your own tests to test! For now, I am sure I reported everything that works or does not work, 
but I might could have possibly skipped something since this was a big project and lots of code. Either way, I got to learn a lot!

SAMPLE OUTPUT BEGIN:
Using test input ./tests/input15.py file...
-----------BEGIN PRINT CODE INPUT-----------
c = 2
d = 3
v1 = []
v1_size = len(v1)
v1.push(2)
v1.push(777)
v1.pop()
v2 = [1, 3, 5, 7, 9]
v3 = [1 + 2, c + d, 5 - 3 * 2, 7, d + 9]
v4 = ["Data Structures", "Programming Languages", "Operating Systems"]
print v4
print v4[-3]
print v4[0] + " " + v4[1]
print v2[0] + 1000
b = [4, 5, 6]
a = 3 + 2
b[-3] = 5 + 5
b[1] = b[-2] + 10
z = b[0] + b[1] + b[2]
y = v4[d - c] + " and " + v4[d - 3]
print y
v2_size = len(v2)
v2_size_doubled = len(v2) * 2
v2.push(11)
v2_size_push = len(v2)
v2.pop()
v2_size_pop1 = len(v2)
v2.pop()
v2_size_pop2 = len(v2)
-----------END PRINT CODE INPUT-----------
-----------BEGIN PROGRAM OUTPUT-----------
["Data Structures", "Programming Languages", "Operating Systems"] 
Data Structures 
Data Structures Programming Languages 
1001 
Programming Languages and Data Structures 
------------END PROGRAM OUTPUT------------

Symbol table contains the following variables.
-----------BEGIN SYMBOL TABLE OUTPUT-----------
a = 5
b = [10, 15, 6]
c = 2
d = 3
v1 = [2]
v1_size = 0
v2 = [1, 3, 5, 7]
v2_size = 5
v2_size_doubled = 10
v2_size_pop1 = 5
v2_size_pop2 = 4
v2_size_push = 6
v3 = [3, 5, -1, 7, 12]
v4 = ["Data Structures", "Programming Languages", "Operating Systems"]
y = "Programming Languages and Data Structures"
z = 31
-----------END SYMBOL TABLE OUTPUT-----------
Press enter to continue
SAMPLE OUTPUT END:

