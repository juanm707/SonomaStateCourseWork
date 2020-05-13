import queue
from DFA import *


def main():
    print("Enter the problem # you want to solve.")
    print("(1) Number of strings (2) Smallest Multiple (3) Quit")
    print("----------------------------------------------------")
    option = int(input())

    while option is not 3:
        if option == 1:
            print("----------------------------------------------------")
            count()
        elif option == 2:
            print("----------------------------------------------------")
            smallestMultiple()
        print("(1) Number of strings (2) Smallest Multiple (3) Quit")
        print("----------------------------------------------------")
        option = int(input())

    print("Quitting...")


def count():
    M = DFA()
    M.generate()

    s = M.states_length()
    # table = [[0 for j in range(n+1)] for i in range(s)]
    prev = [0 for _ in range(s)]
    next = [0 for _ in range(s)]

    for i in range(0, s):
        state = M.get_state_by_id(i)
        if state in M.accepting_states:  # BASE CASE N(j, 0) = 1 if j ∈ F, N(j, 0) = 0 if j NOT ∈ F
            prev[i] = 1
        else:
            pass

    # Creates a table containing n = string length, and states S  all set to 0
    n = int(input('Enter a positive integer between 1 and 300 (inclusive)\n'))

    for j in range(1, n + 1):
        for i in range(0, s):
            state = M.get_state_by_id(i)
            state_a = state.on_a
            state_b = state.on_b
            state_c = state.on_c
            state_d = state.on_d
            next[i] = prev[state_a.ID] + prev[state_b.ID] + prev[state_c.ID] + prev[state_d.ID]
        prev = next.copy()

    print('N(0, ' + str(n) + ') = ' + str(next[0]))
    print("----------------------------------------------------")

    # print(M.check_string('abbccdaabca'))
    # print(M.check_string('badaabcbcdcabad'))
    # print(M.check_string('aaaaa'))


def smallestMultiple():
    n = int(input("Enter a number between 1 and 99999 inclusive: "))  # user input
    while n < 1 or n > 99999:
        n = int(input("Must enter a number between 1 and 99999 inclusive: "))  # user input

    print("Enter the digits permitted, pressing enter after each one (ENTER -1 TO STOP): ")
    digit = 99
    digits_allowed = []
    while digit != -1:
        digit = int(input())
        if (digit < 0 or digit > 9) and digit != -1:
            print("Must enter a digit from 0 through 9!")
        else:
            digits_allowed.append(digit)  # user input
    del digits_allowed[-1]  # remove the -1

    digits_allowed = list(set(digits_allowed))
    m = len(digits_allowed)  # number of symbols
    final = [0 for _ in range(n)]  # 0 is only accepting state
    final[0] = 1
    label = [0 for _ in range(n)]
    parent = [0 for _ in range(n)]

    transition_table = [[-1 for _ in range(10)] for _ in range(n)]
    for i in range(n):
        for j in range(10):
            for k in range(len(digits_allowed)):
                if j != digits_allowed[k]:
                    pass
                else:
                    concat = str(i) + str(digits_allowed[k])
                    transition_table[i][j] = int(concat) % n

    # STEP 1
    q = queue.Queue(0)
    found = False

    # STEP 2
    visited = [0 for _ in range(n)]

    # STEP 3
    q.put(0)  # insert start state into q
    visited[0] = 1

    # STEP 4
    while not q.empty():
        current = q.get()
        for k in range(m):
            _next = transition_table[current][digits_allowed[k]]
            if _next == -1:
                continue
            elif final[_next] == 1:
                label[_next] = digits_allowed[k]
                parent[_next] = current
                found = True
                break

            else:
                if visited[_next] == 0:
                    parent[_next] = current
                    visited[_next] = 1
                    label[_next] = digits_allowed[k]
                    q.put(_next)
        if found:
            break

    print("Inputs: k = " + str(n) + ", Digits permitted: ", end='')
    digits_allowed.sort()
    print(digits_allowed, sep=", ")
    # STEP 5
    if not found:
        print("Output: No solution")


    else:
        string = str(label[0])
        current = parent[0]
        while current != 0:
            string += str(label[current])
            current = parent[current]
        print("Output: ", end="")
        print(string[::-1])

    print("----------------------------------------------------")


if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
