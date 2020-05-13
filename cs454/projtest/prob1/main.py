from DFA import *


def main():
    M = DFA()
    M.generate()

    # Creates a table containing n = string length, and states S  all set to 0
    n = int(input('Enter a positive integer between 1 and 300 (inclusive)\n'))
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

    # print(M.check_string('abbccdaabca'))
    # print(M.check_string('badaabcbcdcabad'))
    # print(M.check_string('aaaaa'))


if __name__ == "__main__":
    """ This is executed when run from the command line """
    main()
