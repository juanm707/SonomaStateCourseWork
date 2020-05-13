import itertools


class DFA(object):

    def __init__(self):
        self.states = []  # List of States
        self.alpha = Alphabet(['a', 'b', 'c', 'd'])  # Define Alphabet for this DFA
        self.start_state = None  # Starting State
        self.accepting_states = []  # All Accepting States

    def generate(self):
        starting_state = State('', 0)
        starting_state.set_accepting()
        self.start_state = starting_state
        self.states.append(starting_state)  # Add starting state to <Q>
        self.accepting_states.append(starting_state)  # Starting state is accepting state since it is < than len 6 <F>

        id_count = 0
        for i in range(1, 6):
            for string in map(''.join, itertools.product('abcd', repeat=i)):

                # print(string)
                id_count += 1
                # print(id_count)

                state = State(string, id_count)  # Create state
                state.set_accepting()  # They are all gonna be accpeting since len < 6
                self.states.append(state)  # Add state to DFA
                self.accepting_states.append(state)

        id_count += 1  # For fail state
        fail_state = State('FAIL', id_count)
        self.states.append(fail_state)
        self.link_state()

    def link_state(self):
        for state in self.states:
            if state.label == 'FAIL':
                state.on_a = state
                state.on_b = state
                state.on_c = state
                state.on_d = state

            else:

                a_string = state.label + 'a'
                b_string = state.label + 'b'
                c_string = state.label + 'c'
                d_string = state.label + 'd'

                if len(state.label) == 5:  # It was 5 but now 6, so change string
                    a_sub = a_string[1:]
                    b_sub = b_string[1:]
                    c_sub = c_string[1:]
                    d_sub = d_string[1:]

                    if ('a' in a_string) and ('b' in a_string) and ('c' in a_string) and ('d' in a_string):
                        #  With 5 characters it was accepting, but we added a 6 so
                        #  So check if abcd in this 6 characters, and add the characters 1-5 as state on 5
                        #  EXAMPLE: ababc + a or b or c = FAIL,
                        #  but with d, ababcd = success so move on to state babcd, remove 'a'
                        #  If not redirect to fail state
                        state.on_a = self.get_state(a_sub)
                    else:
                        state.on_a = self.get_state('FAIL')

                    if ('a' in b_string) and ('b' in b_string) and ('c' in b_string) and ('d' in b_string):
                        state.on_b = self.get_state(b_sub)
                    else:
                        state.on_b = self.get_state('FAIL')

                    if ('a' in c_string) and ('b' in c_string) and ('c' in c_string) and ('d' in c_string):
                        state.on_c = self.get_state(c_sub)
                    else:
                        state.on_c = self.get_state('FAIL')

                    if ('a' in d_string) and ('b' in d_string) and ('c' in d_string) and ('d' in d_string):
                        state.on_d = self.get_state(d_sub)
                    else:
                        state.on_d = self.get_state('FAIL')

                else:
                    state.on_a = self.get_state(a_string)
                    state.on_b = self.get_state(b_string)
                    state.on_c = self.get_state(c_string)
                    state.on_d = self.get_state(d_string)

    def get_state(self, l):
        for state in self.states:
            if state.label == l:
                return state
        return None

    def get_state_by_id(self, i_d):
        for state in self.states:
            if state.ID == i_d:
                return state
        return None

    def check_string(self, string):
        if (string == '') or (string == "") or (len(string) < 6):
            return True
        else:
            current_state = self.get_state('')  # Start at 0 or ''
            count = 0
            while count != len(string)-5:
                character = string[count]
                current_state = current_state.go_on(character)
                if current_state.accepting == 0:
                    return False
                else:
                    count += 1

            return True

    def states_length(self):
        return len(self.states)


class State(object):

    def __init__(self, label, i_d):
        self.label = label
        self.ID = i_d
        self.accepting = 0
        self.on_a = None
        self.on_b = None
        self.on_c = None
        self.on_d = None

    def set_accepting(self):
        self.accepting = 1

    def get_accepting(self):
        return self.accepting

    def go_on(self, character):
        if character == 'a':
            return self.on_a
        elif character == 'b':
            return self.on_b
        elif character == 'c':
            return self.on_c
        elif character == 'd':
            return self.on_d


class Alphabet(object):

    def __init__(self, symbols):
        self.symbol_list = symbols
