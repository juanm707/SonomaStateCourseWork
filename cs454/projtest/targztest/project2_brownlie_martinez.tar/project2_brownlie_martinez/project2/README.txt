# Assignment: Final Project - Encoded strings of a 3 x n graph
# File: README.txt
# Author: Alec Brownlie and Juan Martinez
# Date: December, Fall 2019
# Course: CS454 - Dr. Ravikumar

Description : For a given graph Gn on a 3 x n grid, our task is to determine the number of spanning trees in Gn.
We have also included two other sub-problems. One is a simple acceptance test of an encoded spanning-tree string,
and the other being how many spanning trees are accepted given some specified edges.

We recommend reading the project report!

DFA
	We used an object oriented approach to create our DFA. We have 34 states, including 1 accepting, and
	1 failing. The remaining 32 states indicate four 4 things (a, b, c, d):
		a = Number of components currently
		b = If the top row reaches the middle row
		c = If the top row reaches the bottom row
		d = If the middle row reaches the bottom row
	This is used to keep track of potential cycles and wether or not everything is 1 component.
	Thus there is 4 options for a {0, 1, 2, 3} and b, c, d = {0, 1} so 4 x 2 x 2 x 2 = 32. We
	can even reduce the number of states. The transitions are 00000, 00001, 00010,....., 11111
	All possible 5 bit binary numbers, 0 <-> 31. PLEASE READ THE REPORT FOR EXAMPLES, PICTURES,
	and more in-depth analysis of DFA and the program.

ENCODING
	The encoding of the graph is of the form XXXXX XXXXX ..... XXXXX EXX where X = {0, 1} if that edge
	is present or not. THE Xs must be in blocks of 5 except the last two EXX, which indicates the ending.
	PLEASE READ THE REPORT FOR EXAMPLES and PICTURES

Problem 1: 
	Counting the number of spanning trees in a 3 x n Graph.
	Works as intended, uses dynamic programming, from project 1, to calculate
	the encodings accepted of n = 2 up to the user specific n. Runs in linear time.
	Checked with brute force way from n = 2, 3, 4, 5, 6 and both equal numbers. 

Problem 2:
	User can input an encoded spanning tree to see if it is accepted or not. Runs in linear time. Sample
	output will be provided below

Problem 3:
	User can enter an encoding with specific edges = 1. For example, 1X1X1 XX11X E1X and the like.
	Runs in exponential. Read report to view analysis

TO RUN (on blue):

	1) use "python3 main.py" to run on terminal
	2) Enter problem number you want to solve
	3) Enter 4 to exit the program

--------------------------------------------------------------------------------------------------------------
BEGIN SAMPLE OUTPUT
--------------------------------------------------------------------------------------------------------------
[jmartinez@blue project2]$ python3 main.py 
Spanning Trees will be encoded in the form:

XXXXX XXXXX XXXXX ..... ..... XXXXX EXX

where X = {0, 1} depending if that edge is present.
Spaces are allowed but not required, the XXXXX blocks
must be length 5, and must have EXX to signal the ending.

EXAMPLE:

o---o   o   o---o
    |   |   |   |
o---o---o---o   o
|       |       |
o---o   o   o---o

ENCODING: 10111 01100 01110 11001 E11

Enter the problem # you want to solve.
------------------------------------------------------
(1) Number of accepted spanning trees in a 3 x n Graph
(2) Enter encoded tree to test acceptance
(3) Specified Edges Spanning Tree
(4) Quit
------------------------------------------------------
1
------------------------------------------------------
Enter a value for n: 2
Number of acceptable spanning trees in a 3 x 2 graph is: 15
------------------------------------------------------
(1) Number of accepted spanning trees in a 3 x n Graph
(2) Enter encoded tree to test acceptance
(3) Specified Edges Spanning Tree
(4) Quit
------------------------------------------------------
1
------------------------------------------------------
Enter a value for n: 3
Number of acceptable spanning trees in a 3 x 3 graph is: 192
------------------------------------------------------
(1) Number of accepted spanning trees in a 3 x n Graph
(2) Enter encoded tree to test acceptance
(3) Specified Edges Spanning Tree
(4) Quit
------------------------------------------------------
1
------------------------------------------------------
Enter a value for n: 4
Number of acceptable spanning trees in a 3 x 4 graph is: 2415
------------------------------------------------------
(1) Number of accepted spanning trees in a 3 x n Graph
(2) Enter encoded tree to test acceptance
(3) Specified Edges Spanning Tree
(4) Quit
------------------------------------------------------
1
------------------------------------------------------
Enter a value for n: 100
Number of acceptable spanning trees in a 3 x 100 graph is: 6794534171988788764149140776500221713833226506330517958268986739996937157605098974906112636933178031969259375
------------------------------------------------------
(1) Number of accepted spanning trees in a 3 x n Graph
(2) Enter encoded tree to test acceptance
(3) Specified Edges Spanning Tree
(4) Quit
------------------------------------------------------
2
------------------------------------------------------
Enter an encoding of a spanning tree: 10111 01100 01110 11001 E11
This is a valid spanning tree!
------------------------------------------------------
(1) Number of accepted spanning trees in a 3 x n Graph
(2) Enter encoded tree to test acceptance
(3) Specified Edges Spanning Tree
(4) Quit
------------------------------------------------------
2 
------------------------------------------------------
Enter an encoding of a spanning tree: 01110 11010 E11
This is a valid spanning tree!
------------------------------------------------------
(1) Number of accepted spanning trees in a 3 x n Graph
(2) Enter encoded tree to test acceptance
(3) Specified Edges Spanning Tree
(4) Quit
------------------------------------------------------
2 
------------------------------------------------------
Enter an encoding of a spanning tree: 10101 11010 01101 00111 11011 E11
This is NOT a valid spanning tree.
------------------------------------------------------
(1) Number of accepted spanning trees in a 3 x n Graph
(2) Enter encoded tree to test acceptance
(3) Specified Edges Spanning Tree
(4) Quit
------------------------------------------------------
3
------------------------------------------------------
Enter an encoding of a spanning tree,
placing X for unspecified edges, and 1 for specified.
EXAMPLE: 1XXX1 XX1XX X1X1X 1XXX1 E1X
XX111 X1X1X XX1XX EX1
Number of spanning trees in a 3 x 4 graph with the specified edges = 0
------------------------------------------------------
(1) Number of accepted spanning trees in a 3 x n Graph
(2) Enter encoded tree to test acceptance
(3) Specified Edges Spanning Tree
(4) Quit
------------------------------------------------------
3
------------------------------------------------------
Enter an encoding of a spanning tree,
placing X for unspecified edges, and 1 for specified.
EXAMPLE: 1XXX1 XX1XX X1X1X 1XXX1 E1X
1XX11 XX11X E1X
Number of spanning trees in a 3 x 3 graph with the specified edges = 6
------------------------------------------------------
(1) Number of accepted spanning trees in a 3 x n Graph
(2) Enter encoded tree to test acceptance
(3) Specified Edges Spanning Tree
(4) Quit
------------------------------------------------------
3
------------------------------------------------------
Enter an encoding of a spanning tree,
placing X for unspecified edges, and 1 for specified.
EXAMPLE: 1XXX1 XX1XX X1X1X 1XXX1 E1X
XXXXX 1X1XX EXX
Number of spanning trees in a 3 x 3 graph with the specified edges = 71
------------------------------------------------------
(1) Number of accepted spanning trees in a 3 x n Graph
(2) Enter encoded tree to test acceptance
(3) Specified Edges Spanning Tree
(4) Quit
------------------------------------------------------
4
Quitting...
--------------------------------------------------------------------------------------------------------------
END SAMPLE OUTPUT
--------------------------------------------------------------------------------------------------------------
