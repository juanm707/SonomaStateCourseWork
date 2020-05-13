# Assignment: Final Project - Encoded strings of a 3 x n graph
# File: DFA.py
# Author: Alec Brownlie and Juan Martinez
# Date: December, Fall 2019
# Course: CS454 - Dr. Ravikumar
# Description : For a given graph Gn on a 3 x n grid, our task is to determine the number of spanning trees in Gn.
# We have also included two other sub-problems. One is a simple acceptance test of an encoded spanning-tree string,
# and the other being how many spanning trees are accepted given some specified edges.


class DFA(object):

    def __init__(self):
        self.states = []  # List of States
        self.start_state = None  # Starting State
        self.accepting_states = []  # All Accepting States

    def generate(self):
        """
        Creates the DFA, 34 states, 32 transitions on each
        :return:
        """

        id_count = 0
        components_possible = 3

        for i in range(0, components_possible + 1):
            for j in range(0, 2):
                for k in range(0, 2):
                    for l in range(0, 2):
                        state = State([i, j, k, l])
                        state.ID = id_count
                        if (i == 0) and (j == 0) and (k == 0) and (l == 0):
                            self.start_state = state
                        self.states.append(state)  # Add starting state to <Q>
                        id_count += 1
        f = State([-1, -1, -1, -1])
        f.ID = 32
        self.states.append(f)  # FAIL STATE
        a = State(['ACCEPTING'])
        a.ID = 33
        a.set_accepting()
        self.states.append(a)
        self.accepting_states.append(a)
        self.link_states()

    def link_states(self):

        for state in self.states:

            if state.label == [-1, -1, -1, -1] or state.label == ['ACCEPTING']:  # if state is fail state
                state.on_0 = self.get_state([-1, -1, -1, -1])
                state.on_1 = self.get_state([-1, -1, -1, -1])
                state.on_2 = self.get_state([-1, -1, -1, -1])
                state.on_3 = self.get_state([-1, -1, -1, -1])
                state.on_4 = self.get_state([-1, -1, -1, -1])
                state.on_5 = self.get_state([-1, -1, -1, -1])
                state.on_6 = self.get_state([-1, -1, -1, -1])
                state.on_7 = self.get_state([-1, -1, -1, -1])
                state.on_8 = self.get_state([-1, -1, -1, -1])
                state.on_9 = self.get_state([-1, -1, -1, -1])
                state.on_10 = self.get_state([-1, -1, -1, -1])
                state.on_11 = self.get_state([-1, -1, -1, -1])
                state.on_12 = self.get_state([-1, -1, -1, -1])
                state.on_13 = self.get_state([-1, -1, -1, -1])
                state.on_14 = self.get_state([-1, -1, -1, -1])
                state.on_15 = self.get_state([-1, -1, -1, -1])
                state.on_16 = self.get_state([-1, -1, -1, -1])
                state.on_17 = self.get_state([-1, -1, -1, -1])
                state.on_18 = self.get_state([-1, -1, -1, -1])
                state.on_19 = self.get_state([-1, -1, -1, -1])
                state.on_20 = self.get_state([-1, -1, -1, -1])
                state.on_21 = self.get_state([-1, -1, -1, -1])
                state.on_22 = self.get_state([-1, -1, -1, -1])
                state.on_23 = self.get_state([-1, -1, -1, -1])
                state.on_24 = self.get_state([-1, -1, -1, -1])
                state.on_25 = self.get_state([-1, -1, -1, -1])
                state.on_26 = self.get_state([-1, -1, -1, -1])
                state.on_27 = self.get_state([-1, -1, -1, -1])
                state.on_28 = self.get_state([-1, -1, -1, -1])
                state.on_29 = self.get_state([-1, -1, -1, -1])
                state.on_30 = self.get_state([-1, -1, -1, -1])
                state.on_31 = self.get_state([-1, -1, -1, -1])
                state.on_E00 = self.get_state([-1, -1, -1, -1])
                state.on_E01 = self.get_state([-1, -1, -1, -1])
                state.on_E10 = self.get_state([-1, -1, -1, -1])
                state.on_E11 = self.get_state([-1, -1, -1, -1])

            else:
                for i in range(0, 32):
                    state.set_transition(i)

                self.set_end_transitions(state)
                self.transitions_helper(state)

    def get_state(self, l):
        for state in self.states:
            if state.label == l:
                return state
        return None

    def states_length(self):
        return len(self.states)

    def set_end_transitions(self, state):

        if state == self.start_state or state.label == [-1, -1, -1, -1] or state.label[0] == 0:  # if it is beginning and we end,
            # it should fail, also fail state on end = fail state
            state.transitions.append(Transition(state.label, 'E00', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E01', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E10', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E11', [-1, -1, -1, -1]))
        elif state.label == ['ACCEPTING']:
            state.transitions.append(Transition(state.label, 'E00', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E01', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E10', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E11', [-1, -1, -1, -1]))
        elif state.label[0] == 1:  # if 1 component
            self.set_end_transitions_1_component(state)
        elif state.label[0] == 2:
            self.set_end_transitions_2_component(state)
        elif state.label[0] == 3:
            self.set_end_transitions_3_component(state)

    def set_end_transitions_1_component(self, state):
        # if less than 3 ones in label, everything fails
        count = 0
        for i in state.label:
            if i == 1:
                count += 1

        if count < 3:
            state.transitions.append(Transition(state.label, 'E00', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E01', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E10', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E11', [-1, -1, -1, -1]))
        else:
            state.transitions.append(Transition(state.label, 'E00', ['ACCEPTING']))
            state.transitions.append(Transition(state.label, 'E01', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E10', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E11', [-1, -1, -1, -1]))

    def set_end_transitions_2_component(self, state):
        # if 0 or more than 1 ones in label, everything fails
        count = 0
        for i in state.label:
            if i == 1:
                count += 1

        if count < 1 or count > 1:
            state.transitions.append(Transition(state.label, 'E00', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E01', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E10', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E11', [-1, -1, -1, -1]))
        elif state.label[1]:
            state.transitions.append(Transition(state.label, 'E00', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E01', ['ACCEPTING']))
            state.transitions.append(Transition(state.label, 'E10', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E11', [-1, -1, -1, -1]))
        elif state.label[2]:
            state.transitions.append(Transition(state.label, 'E00', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E01', ['ACCEPTING']))
            state.transitions.append(Transition(state.label, 'E10', ['ACCEPTING']))
            state.transitions.append(Transition(state.label, 'E11', [-1, -1, -1, -1]))
        else:  # state.label[3]
            state.transitions.append(Transition(state.label, 'E00', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E01', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E10', ['ACCEPTING']))
            state.transitions.append(Transition(state.label, 'E11', [-1, -1, -1, -1]))

    def set_end_transitions_3_component(self, state):
        if state.label == [3, 0, 0, 0]:
            state.transitions.append(Transition(state.label, 'E00', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E01', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E10', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E11', ['ACCEPTING']))
        else:
            state.transitions.append(Transition(state.label, 'E00', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E01', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E10', [-1, -1, -1, -1]))
            state.transitions.append(Transition(state.label, 'E11', [-1, -1, -1, -1]))

    def transitions_helper(self, state):
        state.on_0 = self.get_state(state.transitions[0].get_q())
        state.on_1 = self.get_state(state.transitions[1].get_q())
        state.on_2 = self.get_state(state.transitions[2].get_q())
        state.on_3 = self.get_state(state.transitions[3].get_q())
        state.on_4 = self.get_state(state.transitions[4].get_q())
        state.on_5 = self.get_state(state.transitions[5].get_q())
        state.on_6 = self.get_state(state.transitions[6].get_q())
        state.on_7 = self.get_state(state.transitions[7].get_q())
        state.on_8 = self.get_state(state.transitions[8].get_q())
        state.on_9 = self.get_state(state.transitions[9].get_q())
        state.on_10 = self.get_state(state.transitions[10].get_q())
        state.on_11 = self.get_state(state.transitions[11].get_q())
        state.on_12 = self.get_state(state.transitions[12].get_q())
        state.on_13 = self.get_state(state.transitions[13].get_q())
        state.on_14 = self.get_state(state.transitions[14].get_q())
        state.on_15 = self.get_state(state.transitions[15].get_q())
        state.on_16 = self.get_state(state.transitions[16].get_q())
        state.on_17 = self.get_state(state.transitions[17].get_q())
        state.on_18 = self.get_state(state.transitions[18].get_q())
        state.on_19 = self.get_state(state.transitions[19].get_q())
        state.on_20 = self.get_state(state.transitions[20].get_q())
        state.on_21 = self.get_state(state.transitions[21].get_q())
        state.on_22 = self.get_state(state.transitions[22].get_q())
        state.on_23 = self.get_state(state.transitions[23].get_q())
        state.on_24 = self.get_state(state.transitions[24].get_q())
        state.on_25 = self.get_state(state.transitions[25].get_q())
        state.on_26 = self.get_state(state.transitions[26].get_q())
        state.on_27 = self.get_state(state.transitions[27].get_q())
        state.on_28 = self.get_state(state.transitions[28].get_q())
        state.on_29 = self.get_state(state.transitions[29].get_q())
        state.on_30 = self.get_state(state.transitions[30].get_q())
        state.on_31 = self.get_state(state.transitions[31].get_q())

        state.on_E00 = self.get_state(state.transitions[32].get_q())
        state.on_E01 = self.get_state(state.transitions[33].get_q())
        state.on_E10 = self.get_state(state.transitions[34].get_q())
        state.on_E11 = self.get_state(state.transitions[35].get_q())

    def check(self, s):
        # checks if string s is in the DFA, a valid spanning tree with no cycles of a 3 x n graph
        current_state = self.start_state
        s_no_space = s.replace(" ", "")
        count = 0
        i = 0
        block = ''
        for c in s_no_space:
            if c == 'E':  # if ending reached
                block = c+s_no_space[i+1]+s_no_space[i+2]
                if block == 'E00':
                    index = 32
                elif block == 'E01':
                    index = 33
                elif block == 'E10':
                    index = 34
                elif block == 'E11':
                    index = 35
                current_state = self.get_state(current_state.transitions[index].get_q())
                if current_state.label == ['ACCEPTING']:
                    return True
                elif current_state.label == [-1, -1, -1, -1]:
                    return False
            i += 1
            block += c
            count += 1
            if count % 5 == 0:
                current_state = self.get_state(current_state.transitions[int(block, 2)].get_q())
                if current_state.label == [-1, -1, -1, -1]:
                    return False
                block = ''


class State(object):

    def __init__(self, label):
        self.label = label
        self.accepting = 0
        self.transitions = []
        self.ID = None

        # Transitions
        self.on_0 = None
        self.on_1 = None
        self.on_2 = None
        self.on_3 = None
        self.on_4 = None
        self.on_5 = None
        self.on_6 = None
        self.on_7 = None
        self.on_8 = None
        self.on_9 = None

        self.on_10 = None
        self.on_11 = None
        self.on_12 = None
        self.on_13 = None
        self.on_14 = None
        self.on_15 = None
        self.on_16 = None
        self.on_17 = None
        self.on_18 = None
        self.on_19 = None

        self.on_20 = None
        self.on_21 = None
        self.on_22 = None
        self.on_23 = None
        self.on_24 = None
        self.on_25 = None
        self.on_26 = None
        self.on_27 = None
        self.on_28 = None
        self.on_29 = None

        self.on_30 = None
        self.on_31 = None

        # Ending transitions
        self.on_E00 = None
        self.on_E01 = None
        self.on_E10 = None
        self.on_E11 = None

    def set_accepting(self):
        self.accepting = 1

    def get_accepting(self):
        return self.accepting

    def set_transition(self, e):  # e is symbol, so p -> on e -> q, p on e takes you to state q

        symbols = ['00000', '00001', '00010', '00011', '00100', '00101', '00110', '00111', '01000', '01001', '01010',
                   '01011', '01100', '01101', '01110', '01111', '10000', '10001', '10010', '10011', '10100', '10101',
                   '10110', '10111', '11000', '11001', '11010', '11011', '11100', '11101', '11110', '11111']
        l0 = l1 = l2 = l3 = 0  # label for q

        s = symbols[e]  # ex '10101'
        x = []  # ex [1, 0, 1, 0, 1]
        for sym in s:
            x.append(int(sym))

        if self.label[0] == 0:  # if its 0, no components yet so beginning
            if self.label[1] == 0:
                if self.label[2] == 0:
                    if self.label[3] == 0:  # if p is [0, 0, 0, 0]

                            if (x[0] == 0 and x[1] == 0) or (x[2] == 0 and (x[1] == 0 and x[3] == 0)) or (x[3] == 0 and x[4] == 0)\
                                    or (x[0] == 0 and x[2] == 0 and x[4] == 0) \
                                    or (x[3] == 0 and (x[4] == 0 and x[2] == 0))\
                                    or (x[1] == 0 and (x[0] == 0 and x[2] == 0)) \
                                    or (x[1] == 1 and x[3] == 1 and x[0] == 0 and x[2] == 0 and x[4] == 0)\
                                    or e == 18 or e == 9:
                                l0 = l1 = l2 = l3 = -1  # fail state

                            else:
                                if x[0] or x[1] or x[2] or x[3] or x[4]:  # we have at least one component
                                    for i in x:
                                        if i == 1:
                                            l0 += 1
                                    l0 = 6 - l0

                                if x[0] and x[1] and x[2]:
                                    l1 = 1
                                if x[0] and x[1] and x[3] and x[4]:
                                    l2 = 1
                                if x[2] and x[3] and x[4]:
                                    l3 = 1

                    #  we skip all but [0, 0, 0, 0] since after reading some input you either fail or
                    #  move on to [{1,2,3}, x, x, x]
                    elif self.label[3] == 1:  # if p is [0, 0, 0, 1]
                        l0 = l1 = l2 = l3 = -1  # fail state

                elif self.label[2] == 1:
                    if self.label[3] == 0:  # if p is [0, 0, 1, 0]
                        l0 = l1 = l2 = l3 = -1  # fail state
                    elif self.label[3] == 1:  # if p is [0, 0, 1, 1]
                        l0 = l1 = l2 = l3 = -1  # fail state

            elif self.label[1] == 1:
                if self.label[2] == 0:
                    if self.label[3] == 0:  # if p is [0, 1, 0, 0]
                        l0 = l1 = l2 = l3 = -1  # fail state

                    elif self.label[3] == 1:  # if p is [0, 1, 0, 1]
                        l0 = l1 = l2 = l3 = -1  # fail state

                elif self.label[2] == 1:
                    if self.label[3] == 0:  # if p is [0, 1, 1, 0]
                        l0 = l1 = l2 = l3 = -1  # fail state

                    elif self.label[3] == 1:  # if p is [0, 1, 1, 1]
                        l0 = l1 = l2 = l3 = -1  # fail state

        elif self.label[0] == 1:
            if self.label[1] == 0:
                if self.label[2] == 0:
                    if self.label[3] == 0:
                        l0 = l1 = l2 = l3 = -1
                        # pass

                    elif self.label[3] == 1:
                        l0 = l1 = l2 = l3 = -1
                        # pass

                elif self.label[2] == 1:
                    if self.label[3] == 0:
                        l0 = l1 = l2 = l3 = -1
                        # pass

                    elif self.label[3] == 1:  # if p is [1, 0, 1, 1]
                        if (x[1] == 1 or x[3] == 1) or (x[0] == 0 and x[2] == 0 and x[4] == 0):  # causes a cycle and if the 3 middle ones missing -> fail state
                            l0 = l1 = l2 = l3 = -1
                        else:
                            if x[0] == 1:
                                if x[2] == 1:
                                    if x[4] == 1:
                                        l0 = 1
                                        l1 = 0
                                        l2 = 1
                                        l3 = 1
                                    else:
                                        l0 = 2
                                        l1 = 1
                                        l2 = 0
                                        l3 = 0
                                else:
                                    if x[4] == 1:
                                        l0 = 2
                                        l1 = 0
                                        l2 = 1
                                        l3 = 0
                                    else:
                                        l0 = 3
                                        l1 = l2 = l3 = 0
                            else:
                                if x[2] == 1:
                                    if x[4] == 1:
                                        l0 = 2
                                        l1 = l2 = 0
                                        l3 = 1
                                    else:
                                        l0 = 3
                                        l1 = l2 = l3 = 0
                                else:
                                    if x[4] == 1:
                                        l0 = 3
                                        l1 = l2 = l3 = 0
                                    else:
                                        l0 = l1 = l2 = l3 = -1
                        # pass

            elif self.label[1] == 1:
                if self.label[2] == 0:
                    if self.label[3] == 0:  # if p is [1, 1, 0, 0]
                        l0 = l1 = l2 = l3 = -1
                        # pass

                    elif self.label[3] == 1:
                        if x[1] == 1 or x[3] == 1:
                            l0 = l1 = l2 = l3 = -1
                        else:
                            if x[0]:
                                if x[2]:
                                    if x[4]:
                                        l0 = l1 = l2 = l3 = 1
                                    else:
                                        l0 = 2
                                        l1 = 1
                                        l2 = 0
                                        l3 = 0
                                else:
                                    if x[4]:
                                        l0 = 2
                                        l1 = 0
                                        l2 = 1
                                        l3 = 0
                                    else:
                                        l0 = 3
                                        l1 = 0
                                        l2 = 0
                                        l3 = 0
                            else:
                                if x[2]:
                                    if x[4]:
                                        l0 = 2
                                        l1 = 0
                                        l2 = 0
                                        l3 = 1
                                    else:
                                        l0 = 3
                                        l1 = l2 = l3 = 0
                                else:
                                    if x[4]:
                                        l0 = 3
                                        l1 = 0
                                        l2 = 0
                                        l3 = 0
                                    else:
                                        l0 = l1 = l2 = l3 = -1
                            # pass

                elif self.label[2] == 1:
                    if self.label[3] == 0:  # if p is [1, 1, 1, 0]
                        if x[1] == 1 or x[3] == 1:  # causes cycle
                            l0 = l1 = l2 = l3 = -1
                        else:
                            if x[0] == 1:
                                if x[2] == 1:
                                    if x[4] == 1:
                                        l0 = l1 = l2 = l3 = 1
                                    else:
                                        l0 = 2
                                        l1 = 1
                                        l2 = 0
                                        l3 = 0
                                else:
                                    if x[4] == 1:
                                        l0 = 2
                                        l1 = 0
                                        l2 = 1
                                        l3 = 0
                                    else:
                                        l0 = 3
                                        l1 = l2 = l3 = 0
                            else:
                                if x[2] == 1:
                                    if x[4] == 1:
                                        l0 = 2
                                        l1 = l2 = 0
                                        l3 = 1
                                    else:
                                        l0 = 3
                                        l1 = l2 = l3 = 0
                                else:
                                    if x[4] == 1:
                                        l0 = 3
                                        l1 = l2 = l3 = 0
                                    else:
                                        l0 = l1 = l2 = l3 = -1
                        # pass

                    elif self.label[3] == 1:  # if p is [1, 1, 1, 1]
                        if x[1] == 1 or x[3] == 1:
                            l0 = l1 = l2 = l3 = -1
                        else:
                            if x[0]:
                                if x[2]:
                                    if x[4]:
                                        l0 = l1 = l2 = l3 = 1
                                    else:
                                        l0 = 2
                                        l1 = 1
                                        l2 = 0
                                        l3 = 0
                                else:
                                    if x[4]:
                                        l0 = 2
                                        l1 = 0
                                        l2 = 1
                                        l3 = 0
                                    else:
                                        l0 = 3
                                        l1 = 0
                                        l2 = 0
                                        l3 = 0
                            else:
                                if x[2]:
                                    if x[4]:
                                        l0 = 2
                                        l1 = 0
                                        l2 = 0
                                        l3 = 1
                                    else:
                                        l0 = 3
                                        l1 = l2 = l3 = 0
                                else:
                                    if x[4]:
                                        l0 = 3
                                        l1 = 0
                                        l2 = 0
                                        l3 = 0
                                    else:
                                        l0 = l1 = l2 = l3 = -1
                        # pass

        elif self.label[0] == 2:
            if self.label[1] == 0:
                if self.label[2] == 0:
                    if self.label[3] == 0:  # if p is [2, 0, 0, 0]
                        l0 = l1 = l2 = l3 = -1
                    else:  # if p is [2, 0, 0, 1]
                        if x[3]:
                            l0 = l1 = l2 = l3 = -1
                        else:
                            if x[0]:
                                if x[1]:
                                    if x[2]:
                                        if x[4]:  # if symbol = 11101
                                            l0 = l1 = l2 = l3 = 1
                                        else:  # if symbol = 11100
                                            l0 = 2
                                            l1 = 1
                                            l2 = l3 = 0
                                    else:
                                        if x[4]:  # if symbol = 11001
                                            l0 = 2
                                            l1 = l3 = 0
                                            l2 = 1
                                        else:  # if symbol = 11000
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                else:
                                    if x[2]:
                                        if x[4]: # if symbol = 10101
                                            l0 = 2
                                            l1 = l2 = 0
                                            l3 = 1
                                        else:  # if symbol = 10100
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                    else:
                                        if x[4]:  # if symbol = 10001
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                        else:  # if symbol = 10000
                                            l0 = l1 = l2 = l3 = -1
                            else:
                                if x[1]:
                                    if x[2]:
                                        if x[4]:  # if symbol is 01101
                                            l0 = 2
                                            l1 = 0
                                            l2 = 0
                                            l3 = 1
                                        else:  # if symbol is 01100
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                    else:
                                        if x[4]:  # if symbol is  01001
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                        else:  # if symbol is  01000
                                            l0 = l1 = l2 = l3 = -1
                                else:
                                    if x[2]:
                                        if x[4]:  # if symbol is  00101
                                            l0 = l1 = l2 = l3 = -1
                                        else:  # if symbol is  00100
                                            l0 = l1 = l2 = l3 = -1
                                    else:
                                        if x[4]:  # if symbol is  00001
                                            l0 = l1 = l2 = l3 = -1
                                        else:  # if symbol is  00000
                                            l0 = l1 = l2 = l3 = -1
                else:
                    if self.label[3] == 0:  # if p is [2, 0, 1, 0]
                        if x[1] and x[3]:  # creates cycle
                            l0 = l1 = l2 = l3 = -1
                        else:
                            if x[1]:
                                if x[0]:
                                    if x[2]:
                                        if x[4]:  # if symbol is 11101
                                            l0 = l1 = l2 = l3 = 1
                                        else:  # if symbol is 11100
                                            l0 = 2
                                            l1 = 1
                                            l2 = l3 = 0
                                    else:
                                        if x[4]:  # if symbol is 11001
                                            l0 = 2
                                            l1 = l3 = 0
                                            l2 = 1
                                        else:  # if symbol is 11000
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                else:
                                    if x[2]:
                                        if x[4]:  # if symbol is 01101
                                            l0 = 2
                                            l1 = l2 = 0
                                            l3 = 1
                                        else:  # if symbol is 01100
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                    else:
                                        if x[4]: # if symbol is 01001
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                        else:  # if symbol is 01000
                                            l0 = l1 = l2 = l3 = -1
                            elif x[3]:
                                if x[0]:
                                    if x[2]:
                                        if x[4]:  # if symbol is 10111
                                            l0 = l1 = l2 = l3 = 1
                                        else:  # if symbol is 10110
                                            l0 = 2
                                            l1 = 1
                                            l2 = l3 = 0
                                    else:
                                        if x[4]:  # if symbol is 10011
                                            l0 = 2
                                            l1 = l3 = 0
                                            l2 = 1
                                        else:  # if symbol is 10010
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                else:
                                    if x[2]:
                                        if x[4]:  # if symbol is 00111
                                            l0 = 2
                                            l1 = l2 = 0
                                            l3 = 1
                                        else:  # if symbol is 00110
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                    else:
                                        if x[4]: # if symbol is 00011
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                        else:  # if symbol is 00010
                                            l0 = l1 = l2 = l3 = -1
                            else:  # both side ones are 0
                                if x[0] == 0 and x[2] == 0 and x[4] == 0:
                                    l0 = l1 = l2 = l3 = -1
                                else:
                                    if x[0] and x[2] and x[4]:  # 1 1 1
                                        l0 = 2
                                        l1 = 0
                                        l2 = 1
                                        l3 = 0
                                    elif x[0] and x[2] and x[4] == 0:  # 1 1 0
                                        l0 = 3
                                        l1 = l2 = l3 = 0
                                    elif x[0] and x[2] == 0 and x[4]:  # 1 0 1
                                        l0 = l1 = l2 = l3 = -1
                                    elif x[0] and x[2] == 0 and x[4] == 0:  # 1 0 0
                                        l0 = l1 = l2 = l3 = -1
                                    elif x[0] == 0 and x[2] and x[4]:  # 0 1 1
                                        l0 = 3
                                        l1 = l2 = l3 = 0
                                    elif x[0] == 0 and x[2] and x[4] == 0:  # 0 1 0
                                        l0 = l1 = l2 = l3 = -1
                                    elif x[0] == 0 and x[2] == 0 and x[4]:  # 0 0 1
                                        l0 = l1 = l2 = l3 = -1

                    else:  # if p is [2, 0, 1, 1] technically invalid state since 2 components but everything together
                        l0 = l1 = l2 = l3 = -1
            else:
                if self.label[2] == 0:
                    if self.label[3] == 0:  # if p is [2, 1, 0, 0]
                        if x[1]:
                            l0 = l1 = l2 = l3 = -1
                        else:
                            if x[0]:
                                if x[3]:
                                    if x[2]:
                                        if x[4]:  # if symbol = 10111
                                            l0 = l1 = l2 = l3 = 1
                                        else:  # if symbol = 10110
                                            l0 = 2
                                            l1 = 1
                                            l2 = l3 = 0
                                    else:
                                        if x[4]:  # if symbol = 10011
                                            l0 = 2
                                            l1 = 0
                                            l2 = 1
                                            l3 = 0
                                        else:  # if symbol = 10010
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                else:
                                    if x[2]:
                                        if x[4]:  # if symbol = 10101
                                            l0 = 2
                                            l1 = 1
                                            l2 = l3 = 0
                                        else:  # if symbol = 10100
                                            l0 = l1 = l2 = l3 = -1
                                    else:
                                        if x[4]:  # if symbol = 10001
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                        else:  # if symbol = 10000
                                            l0 = l1 = l2 = l3 = -1
                            else:
                                if x[3]:
                                    if x[2]:
                                        if x[4]:  # if symbol is 00111
                                            l0 = 2
                                            l1 = 0
                                            l2 = 0
                                            l3 = 1
                                        else:  # if symbol is 00110
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                    else:
                                        if x[4]:  # if symbol is 00011
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                        else:  # if symbol is 00010
                                            l0 = l1 = l2 = l3 = -1
                                else:
                                    if x[2]:
                                        if x[4]:  # if symbol is 00101
                                            l0 = 3
                                            l1 = l2 = l3 = 0
                                        else:  # if symbol is  00100
                                            l0 = l1 = l2 = l3 = -1
                                    else:
                                        if x[4]:  # if symbol is 00001
                                            l0 = l1 = l2 = l3 = -1
                                        else:  # if symbol is 00000
                                            l0 = l1 = l2 = l3 = -1
                    else:  # if p is [2, 1, 0, 1] technically invalid state since 2 components but everything together
                        l0 = l1 = l2 = l3 = -1
                else:
                    if self.label[3] == 0:  # if p is [2, 1, 1, 0]
                        # technically invalid state since 2 components but everything together
                        l0 = l1 = l2 = l3 = -1
                    else:  # if p is [2, 1, 1, 1] technically invalid state since 2 components but everything together
                        l0 = l1 = l2 = l3 = -1

        elif self.label[0] == 3:
            if self.label[1] == 0:
                if self.label[2] == 0:
                    if self.label[3] == 0:  # if p is [3, 0, 0, 0]

                        if (x[0] == 0 and x[1] == 0) or (x[2] == 0 and (x[1] == 0 and x[3] == 0)) or (
                                x[3] == 0 and x[4] == 0) \
                                or (x[0] == 0 and x[2] == 0 and x[4] == 0) \
                                or (x[3] == 0 and (x[4] == 0 and x[2] == 0)) \
                                or (x[1] == 0 and (x[0] == 0 and x[2] == 0)) \
                                or (x[1] == 1 and x[3] == 1 and x[0] == 0 and x[2] == 0 and x[4] == 0)\
                                or e == 18 or e == 9:
                            l0 = l1 = l2 = l3 = -1  # fail state

                        else:
                            if x[0] or x[1] or x[2] or x[3] or x[4]:  # we have at least one component
                                for i in x:
                                    if i == 1:
                                        l0 += 1
                                l0 = 6 - l0

                            if x[0] and x[1] and x[2]:
                                l1 = 1
                            if x[0] and x[1] and x[3] and x[4]:
                                l2 = 1
                            if x[2] and x[3] and x[4]:
                                l3 = 1

                    else:  # if p is [3, 0, 0, 1] technically invalid state since 3 components but actually 2
                        l0 = l1 = l2 = l3 = -1
                else:
                    if self.label[3] == 0:  # if p is [3, 0, 1, 0] technically invalid state since 3 components but actually 2
                        l0 = l1 = l2 = l3 = -1
                    else:  # if p is [3, 0, 1, 0] technically invalid state since 3 components but everything together
                        l0 = l1 = l2 = l3 = -1
            else:
                if self.label[2] == 0:
                    if self.label[3] == 0:  # if p is [3, 1, 0, 0] technically invalid state since 3 components but actually 2
                        l0 = l1 = l2 = l3 = -1
                    else:  # if p is [3, 1, 0, 1] technically invalid state since 3 components but everything together
                        l0 = l1 = l2 = l3 = -1
                else:
                    if self.label[3] == 0:  # if p is [3, 1, 1, 0] technically invalid state since 3 components but everything together
                        l0 = l1 = l2 = l3 = -1
                    else:  # if p is [3, 1, 1, 1] technically invalid state since 3 components but everything together
                        l0 = l1 = l2 = l3 = -1
            pass

        q_state = [l0, l1, l2, l3]
        t = Transition(self.label, e, q_state)
        self.transitions.append(t)

    def go_on(self, character):
        if character == '0':
            return self.on_0
        elif character == '1':
            return self.on_1
        elif character == '2':
            return self.on_2
        elif character == '3':
            return self.on_3
        elif character == '4':
            return self.on_4
        elif character == '5':
            return self.on_5
        elif character == '6':
            return self.on_6
        elif character == '7':
            return self.on_7
        elif character == '8':
            return self.on_8
        elif character == '9':
            return self.on_9

        elif character == '10':
            return self.on_10
        elif character == '11':
            return self.on_11
        elif character == '12':
            return self.on_12
        elif character == '13':
            return self.on_13
        elif character == '14':
            return self.on_14
        elif character == '15':
            return self.on_15
        elif character == '16':
            return self.on_16
        elif character == '17':
            return self.on_17
        elif character == '18':
            return self.on_18
        elif character == '19':
            return self.on_19

        elif character == '20':
            return self.on_20
        elif character == '21':
            return self.on_21
        elif character == '22':
            return self.on_22
        elif character == '23':
            return self.on_23
        elif character == '24':
            return self.on_24
        elif character == '25':
            return self.on_25
        elif character == '26':
            return self.on_26
        elif character == '27':
            return self.on_27
        elif character == '28':
            return self.on_28
        elif character == '29':
            return self.on_29

        elif character == '30':
            return self.on_30
        elif character == '31':
            return self.on_31


class Transition(object):

    def __init__(self, p, e, q):

        self.p = p  # state
        self.e = e  # symbol
        self.q = q  # resulting state

    def set_p(self, p):
        self.p = p

    def set_e(self, e):
        self.e = e

    def set_q(self, q):
        self.q = q

    def get_p(self):
        return self.p

    def get_e(self):
        return self.e

    def get_q(self):
        return self.q
