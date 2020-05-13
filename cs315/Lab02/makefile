########################################
# Author:     Juan Martinez            #
# Student:    Juan Martinez            #
# Term:       Fall 2017                #
# Course:     CS 315                   #
# Assignment: Lab 02                   #
# Date:       9/25/17                  #
# Professor:  Dr. Kooshesh             #
# File:       isMemberBinarySearch.cpp #
########################################

CFLAGS= -ggdb -std=c++11 -Wall -Wextra

# the first target ("all") is made by default.
# So, we list all targets that need to be made here.
all: isSorted.x isPal.x gcd.x isMemberSequentialSearch.x isMemberBinarySearch.x collatz.x

# dependencies for isSorted
isSorted.x: isSorted.o isSorted_main.o
	g++ $(CFLAGS) -o isSorted.x isSorted.o isSorted_main.o

isSorted.o: isSorted.hpp isSorted.cpp
	g++ $(CFLAGS) -c -o isSorted.o isSorted.cpp

isSorted_main.o: isSorted.hpp isSorted_main.cpp
	g++ $(CFLAGS) -c -o isSorted_main.o isSorted_main.cpp

# dependencies for isPal
isPal.x: isPal.o isPal_main.o
	g++ $(CFLAGS) -o isPal.x isPal.o isPal_main.o

isPal.o: isPal.hpp isPal.cpp
	g++ $(CFLAGS) -c -o isPal.o isPal.cpp

isPal_main.o: isPal.hpp isPal_main.cpp
	g++ $(CFLAGS) -c -o isPal_main.o isPal_main.cpp

# dependencies for gcd
gcd.x: gcd.o gcd_main.o
	g++ $(CFLAGS) -o gcd.x gcd.o gcd_main.o

gcd.o: gcd.hpp gcd.cpp
	g++ $(CFLAGS) -c -o gcd.o gcd.cpp

gcd_main.o: gcd.hpp gcd_main.cpp
	g++ $(CFLAGS) -c -o gcd_main.o gcd_main.cpp

# dependencies for isMemberSequentialSearch
isMemberSequentialSearch.x: isMemberSequentialSearch.o isMemberSequentialSearch_main.o
	g++ $(CFLAGS) -o isMemberSequentialSearch.x isMemberSequentialSearch.o isMemberSequentialSearch_main.o

isMemberSequentialSearch.o: isMemberSequentialSearch.hpp isMemberSequentialSearch.cpp
	g++ $(CFLAGS) -c -o isMemberSequentialSearch.o isMemberSequentialSearch.cpp

isMemberSequentialSearch_main.o: isMemberSequentialSearch.hpp isMemberSequentialSearch_main.cpp
	g++ $(CFLAGS) -c -o isMemberSequentialSearch_main.o isMemberSequentialSearch_main.cpp

# dependencies for isMemberBinarySearch
isMemberBinarySearch.x: isMemberBinarySearch.o isMemberBinarySearch_main.o
	g++ $(CFLAGS) -o isMemberBinarySearch.x isMemberBinarySearch.o isMemberBinarySearch_main.o

isMemberBinarySearch.o: isMemberBinarySearch.hpp isMemberBinarySearch.cpp
	g++ $(CFLAGS) -c -o isMemberBinarySearch.o isMemberBinarySearch.cpp

isMemberBinarySearch_main.o: isMemberBinarySearch.hpp isMemberBinarySearch_main.cpp
	g++ $(CFLAGS) -c -o isMemberBinarySearch_main.o isMemberBinarySearch_main.cpp

# dependencies for collatz
collatz.x: collatz.o collatz_main.o
	g++ $(CFLAGS) -o collatz.x collatz.o collatz_main.o

collatz.o: collatz.hpp collatz.cpp
	g++ $(CFLAGS) -c -o collatz.o collatz.cpp

collatz_main.o: collatz.hpp collatz_main.cpp
	g++ $(CFLAGS) -c -o collatz_main.o collatz_main.cpp

# At the shell prompt, type:
# make clean
# to remove the .o, .x and Emacs backup files.

clean:
	rm -f *.o *.x *~
