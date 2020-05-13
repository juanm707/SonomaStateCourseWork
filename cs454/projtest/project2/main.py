# Assignment: Final Project - Encoded strings of a 3 x n graph
# File: main.py
# Author: Alec Brownlie and Juan Martinez
# Date: December, Fall 2019
# Course: CS454 - Dr. Ravikumar
# Description : For a given graph Gn on a 3 x n grid, our task is to determine the number of spanning trees in Gn.
# We have also included two other sub-problems. One is a simple acceptance test of an encoded spanning-tree string,
# and the other being how many spanning trees are accepted given some specified edges.

from DFA import *
import itertools
import time
import matplotlib.pyplot as plt


def main():

    m = DFA()
    m.generate()

    # TO TEST TIME, will open new window, works on pycharm, not sure on terminal
    # time_results(m)
    # TO TEST TIME, will open new window, works on pycharm, not sure on terminal

    print("Spanning Trees will be encoded in the form:\n\n"
          "XXXXX XXXXX XXXXX ..... ..... XXXXX EXX\n\n"
          "where X = {0, 1} depending if that edge is present.\n"
          "Spaces are allowed but not required, the XXXXX blocks\n"
          "must be length 5, and must have EXX to signal the ending.\n")
    print("EXAMPLE:\n")
    print("o---o   o   o---o")
    print("    |   |   |   |")
    print("o---o---o---o   o")
    print("|       |       |")
    print("o---o   o   o---o\n")
    print("ENCODING: 10111 01100 01110 11001 E11\n")

    print("Enter the problem # you want to solve.")
    print("------------------------------------------------------")
    print("(1) Number of accepted spanning trees in a 3 x n Graph\n"
          "(2) Enter encoded tree to test acceptance\n"
          "(3) Specified Edges Spanning Tree\n"
          "(4) Quit")
    print("------------------------------------------------------")
    option = int(input())
    while option is not 4:
        if option == 1:
            print("------------------------------------------------------")
            count(m, False, '')
        elif option == 2:
            print("------------------------------------------------------")
            test_string(m)
        elif option == 3:
            print("------------------------------------------------------")
            specified_edges(m, False, '')
        print("------------------------------------------------------")
        print("(1) Number of accepted spanning trees in a 3 x n Graph\n"
              "(2) Enter encoded tree to test acceptance\n"
              "(3) Specified Edges Spanning Tree\n"
              "(4) Quit")
        print("------------------------------------------------------")
        option = int(input())

    print("Quitting...")


def test_string(dfa):
    """
    Check if user input, encoded spanning tree, is in the DFA, meaning it is a valid spanning tree.
    :param dfa:
    :return:
    """
    tree_string = input("Enter an encoding of a spanning tree: ")
    if dfa.check(tree_string):
        print("This is a valid spanning tree!")
    else:
        print("This is NOT a valid spanning tree.")


def count(dfa, time_bool, inp):
    """
    Counts the number of spanning trees in a 3 x n Graph in linear time using dynamic programming approach
    :param dfa:
    :param time_bool: True for timing results, False otherwise
    :param inp: Input for when timing results
    :return:
    """

    dfa_length = dfa.states_length()
    prev = [0 for _ in range(dfa_length)]
    next = [0 for _ in range(dfa_length)]

    for i in range(0, dfa_length):
        state = dfa.states[i]
        if state in dfa.accepting_states:
            prev[i] = 1
        else:
            pass

    if time_bool:
        n = inp
    else:
        n = int(input('Enter a value for n: '))

    if n == 1 and not time_bool:
        print("Number of acceptable spanning trees in a 3 x " + str(n) + " graph is: 1")
        return
    for j in range(1, n + 1):
        for i in range(0, dfa_length):
            state = dfa.states[i]
            state_0 = state.on_0
            state_1 = state.on_1
            state_2 = state.on_2
            state_3 = state.on_3
            state_4 = state.on_4
            state_5 = state.on_5
            state_6 = state.on_6
            state_7 = state.on_7
            state_8 = state.on_8
            state_9 = state.on_9
            state_10 = state.on_10
            state_11 = state.on_11
            state_12 = state.on_12
            state_13 = state.on_13
            state_14 = state.on_14
            state_15 = state.on_15
            state_16 = state.on_16
            state_17 = state.on_17
            state_18 = state.on_18
            state_19 = state.on_19
            state_20 = state.on_20
            state_21 = state.on_21
            state_22 = state.on_22
            state_23 = state.on_23
            state_24 = state.on_24
            state_25 = state.on_25
            state_26 = state.on_26
            state_27 = state.on_27
            state_28 = state.on_28
            state_29 = state.on_29
            state_30 = state.on_30
            state_31 = state.on_31

            state_32 = state.on_E00
            state_33 = state.on_E01
            state_34 = state.on_E10
            state_35 = state.on_E11

            next[i] = prev[state_0.ID] + prev[state_1.ID] + prev[state_2.ID] + prev[state_3.ID] + prev[state_4.ID] + \
                      prev[state_5.ID] + prev[state_6.ID] + prev[state_7.ID] + prev[state_8.ID] + prev[state_9.ID] + \
                      prev[state_10.ID] + prev[state_11.ID] + prev[state_12.ID] + prev[state_13.ID] + prev[state_14.ID] + \
                      prev[state_15.ID] + prev[state_16.ID] + prev[state_17.ID] + prev[state_18.ID] + prev[state_19.ID] + \
                      prev[state_20.ID] + prev[state_21.ID] + prev[state_22.ID] + prev[state_23.ID] + prev[state_24.ID] + \
                      prev[state_25.ID] + prev[state_26.ID] + prev[state_27.ID] + prev[state_28.ID] + prev[state_29.ID] + \
                      prev[state_30.ID] + prev[state_31.ID] + prev[state_32.ID] + prev[state_33.ID] + prev[state_34.ID] + prev[state_35.ID]
        prev = next.copy()
    if not time_bool:
        print("Number of acceptable spanning trees in a 3 x " + str(n) + " graph is: " + str(next[0]))
    # Brute force test
    # print("Brute force takes a while...")
    # print("Brute force n = 6: " + str(string_count(dfa)))


def string_count(dfa):
    """
    Used to test to compare dynamic programming approach vs brute force.
    This tests n = 6, but you can add more loops to test > n
    n = 6 brute force took more than 15+ minutes on blue server.
    """
    bits5 = ['00000', '00001', '00010', '00011', '00100', '00101', '00110', '00111', '01000', '01001', '01010', '01011',
             '01100', '01101', '01110', '01111', '10000', '10001', '10010', '10011', '10100', '10101', '10110', '10111',
             '11000', '11001', '11010', '11011', '11100', '11101', '11110', '11111']
    bits2 = ['E00', 'E01', 'E10', 'E11']
    count = 0
    for a in bits5:
        for b in bits5:
            for c in bits5:
                for d in bits5:
                    for e in bits5:
                        for i in bits2:
                            s = a + b + c + d + e + i
                            # print(s)
                            # uncomment the print statement to view how long it will take
                            t = dfa.check(s)
                            if t:
                                count += 1

    return count


def specified_edges(dfa, test_bool, s):
    """
    Exponential (really slow...) when user enters only Xs, but the user should not do that since having only Xs is
    the same goal of the first problem, which the first option solves much faster.
    For example, having XXXXX XXXXX EXX is the same as solving the number of acceptable spanning trees for a 3 X 3 graph.
    Obviously the more 1s present the better. Does not exclude edges, for example 0X011.
    """
    if test_bool:
        tree_string = s
    else:
        tree_string = input("Enter an encoding of a spanning tree,\nplacing X for unspecified edges, and 1 for specified.\n"
                        "EXAMPLE: 1XXX1 XX1XX X1X1X 1XXX1 E1X\n")

    s_no_space = tree_string.replace(" ", "")
    n = int(((len(s_no_space) - 3)/5)+1)
    section_count = 0
    sections = []
    for i in range(n):
        sections.append([])

    bits5 = ['00000', '00001', '00010', '00011', '00100', '00101', '00110', '00111', '01000', '01001', '01010', '01011',
             '01100', '01101', '01110', '01111', '10000', '10001', '10010', '10011', '10100', '10101', '10110', '10111',
             '11000', '11001', '11010', '11011', '11100', '11101', '11110', '11111']
    bits2 = ['E00', 'E01', 'E10', 'E11']

    count = 0
    i = 0
    block = ''
    for c in s_no_space:
        if c == 'E':  # if ending reached
            block = c + s_no_space[i + 1] + s_no_space[i + 2]
            if block == 'EXX':
                for w in bits2:
                    sections[section_count].append(w)
            elif block == 'EX1':
                sections[section_count].append('E01')
                sections[section_count].append('E11')
            elif block == 'E1X':
                sections[section_count].append('E10')
                sections[section_count].append('E11')
            elif block == 'E11':
                sections[section_count].append('E11')

        i += 1
        block += c
        count += 1

        if count % 5 == 0:
            x_pos = xpositions(block)
            for b in bits5:
                pos_count = 0
                for index in x_pos:
                    if b[index] == '1':
                        pos_count += 1
                    else:
                        break
                if pos_count == len(x_pos):
                    sections[section_count].append(b)
            section_count += 1
            block = ''

    spanning_tree_count = 0
    l = list(itertools.product(*sections))
    for encoding in l:
        tree_string = convert_tuple(encoding)
        if dfa.check(tree_string):
            spanning_tree_count += 1

    if not test_bool:
        print("Number of spanning trees in a 3 x " + str(n) + " graph with the specified edges = " + str(spanning_tree_count))


def xpositions(block):
    """
    Helper function for specific edges case, keeps track of the indexes where there is a 1 in 'block'
    :param block: a block string, ex: 1XX1X
    :return: array of indices were there is a 1 in 'block' ex: [0,3]
    """
    i = 0
    i_array = []
    for c in block:
        if c == '1':
            i_array.append(i)
        i += 1
    return i_array


def convert_tuple(tup):
    """
    Converts a tuple to string
    :param tup:
    :return: tuple as string
    """
    str = ''.join(tup)
    return str


def time_results(dfa):
    """
    Not sure if matplot works in terminal or command line. Recommend using PyCharm!

    Creates the charts for time complexity using matplot. You can change the values of input if you want.
    Creates 3 windows, must close current plot window to view next plot window
    """
    time_and_size = []

    # for count function
    for i in range(501):
        start = time.time()
        count(dfa, True, i)
        end = time.time()
        time_and_size.append((end - start, i))
    # print(time_and_size)
    x_val = [x[1] for x in time_and_size]
    y_val = [x[0] for x in time_and_size]
    plt.plot(x_val, y_val)
    plt.plot(x_val, y_val, 'or')
    plt.xlabel("Size of input n")
    plt.ylabel("Time taken to count all span. trees")
    plt.show()

    # for check function, checking if string is accepted
    time_and_size = []
    for i in range(300):
        str = '11111' + '10101' * i + 'E00'
        start = time.time()
        dfa.check(str)
        end = time.time()
        time_and_size.append((end - start, i+2))
        # print(str)
    x_val = [x[1] for x in time_and_size]
    y_val = [x[0] for x in time_and_size]
    plt.plot(x_val, y_val)
    plt.plot(x_val, y_val, 'or')
    plt.xlabel("Size of input n, a 3 x n encoded string")
    plt.ylabel("Time taken reach accepting state")
    plt.show()

    # for specific edges function
    time_and_size = []
    c = 2
    test_cases = ['XXXXX EXX', 'XXXXX XXXXX EXX', 'XXXXX XXXXX XXXXX EXX', 'XXXXX XXXXX XXXXX XXXXX EXX']
    for t in test_cases:

        start = time.time()
        specified_edges(dfa, True, t)
        end = time.time()
        time_and_size.append((end - start, c))
        c += 1
    x_val = [x[1] for x in time_and_size]
    y_val = [x[0] for x in time_and_size]
    plt.plot(x_val, y_val)
    plt.plot(x_val, y_val, 'or')
    plt.xlabel("Size of input n, ALL 3 x n encoded string")
    plt.ylabel("Time taken count all accepting strings of 3 x n graph")
    plt.show()


if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
