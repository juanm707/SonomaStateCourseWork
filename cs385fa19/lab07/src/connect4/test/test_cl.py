import unittest
import json

from ..client import ConnectFourClient, UnableToJoinException, TurnTimeoutException


class SessionSpy:
    """
    A test spy to be able to very the calls made to the session object by the ConnectFourClient
    """

    def __init__(self, responses):
        self.headers = {}
        self.responses = responses
        self.calls = []

    def get(self, endpoint, params=None):
        self.calls.append((endpoint, params))
        response = self.responses.pop()
        return response

class ResponseStub:
    """
    A test stub used control the responses received by the ConnectFourClient
    """

    def __init__(self, status_code, text):
        self.status_code = status_code
        self.text = text

    def json(self):
        return json.loads(self.text)


class ClientTests(unittest.TestCase):


    def setUp(self):
        self.session = SessionSpy([])
        self.host = 'foo'
        self.port = 80
        self.playername = 'bar'
        self.c4client = ConnectFourClient(
            self.host,
            self.port,
            self.playername,
            self.session
        )

        
    def test_find_avaiable_columns_all_empty(self):

        response = ResponseStub(200,'{"session": "abc", "player": "bar"}')
        self.session.responses.append(response)
        self.c4client.join()
        # create another client
        self.c4_2_client = ConnectFourClient(self.c4client.host, self.c4client.port, 'bob', self.session)
        response = ResponseStub(200,'{"session": "abc", "player": "bob"}')
        self.session.responses.append(response)
        self.c4_2_client.join()

        # all columns should be available when empty
        expected = [0, 1, 2, 3, 4, 5, 6]
        self.assertEqual(self.c4client.find_available_columns(), expected)

        
    def test_find_avaiable_columns_all_full(self):

        response = ResponseStub(200,'{"session": "abc", "player": "bar"}')
        self.session.responses.append(response)
        self.c4client.join()
        # create another client                                                                                                    
        self.c4_2_client = ConnectFourClient(self.c4client.host, self.c4client.port, 'bob', self.session)
        response = ResponseStub(200,'{"session": "abc", "player": "bob"}')
        self.session.responses.append(response)
        self.c4_2_client.join()

        # no columns should be available when full
        self.c4client.board = [['1', '2', '1', '1', '2', '2', '1'],
                               ['2', '1', '2', '2', '1', '1', '2'],
                               ['1', '2', '1', '1', '2', '2', '1'],
                               ['2', '1', '2', '2', '1', '1', '2'],
                               ['1', '2', '1', '1', '2', '2', '1'],
                               ['2', '1', '2', '2', '1', '1', '2']]
        expected = []
        self.assertEqual(self.c4client.find_available_columns(), expected)

    def test_find_avaiable_columns_f_m_l(self):
        # first and middle and last column open
        response = ResponseStub(200,'{"session": "abc", "player": "bar"}')
        self.session.responses.append(response)
        self.c4client.join()
        # create another client                                                                                                    
        self.c4_2_client = ConnectFourClient(self.c4client.host, self.c4client.port, 'bob', self.session)
        response = ResponseStub(200,'{"session": "abc", "player": "bob"}')
        self.session.responses.append(response)
        self.c4_2_client.join()

        # no columns should be available when full                                                                                  
        self.c4client.board = [['1', '2', '1', '1', '2', '2', '1'],
                               ['2', '1', '2', ' ', '1', '1', '2'],
                               ['1', '2', '1', ' ', '2', '2', ' '],
                               [' ', '1', '2', ' ', '1', '1', ' '],
                               [' ', '2', '1', ' ', '2', '2', ' '],
                               [' ', '1', '2', ' ', '1', '1', ' ']]
        expected = [0, 3, 6]
        self.assertEqual(self.c4client.find_available_columns(), expected)

    def test_find_avaiable_columns_last(self):
        # last column open                                                                                                        
        response = ResponseStub(200,'{"session": "abc", "player": "bar"}')
        self.session.responses.append(response)
        self.c4client.join()
        # create another client                                                                                                                        
        self.c4_2_client = ConnectFourClient(self.c4client.host, self.c4client.port, 'bob', self.session)
        response = ResponseStub(200,'{"session": "abc", "player": "bob"}')
        self.session.responses.append(response)
        self.c4_2_client.join()

        # no columns should be available when full                                                                                                     
        self.c4client.board = [['1', '2', '1', '1', '2', '2', '1'],
                               ['2', '1', '2', '2', '1', '1', '2'],
                               ['1', '2', '1', '1', '2', '2', '1'],
                               ['2', '1', '2', '2', '1', '1', '2'],
                               ['1', '2', '1', '1', '2', '2', '1'],
                               ['2', '1', '2', '2', '1', '1', ' ']]
        expected = [6]
        self.assertEqual(self.c4client.find_available_columns(), expected)

    def test_wait_for_turn(self):
        response = ResponseStub(200,'{"session": "abc", "player": 1, "board": []}')
        self.session.responses.append(response)
        self.c4client.join()
        # create another client                                                                                                                      
        self.c4_2_client = ConnectFourClient(self.c4client.host, self.c4client.port, 'bob', self.session)
        response = ResponseStub(200,'{"session": "abc", "player": "bob"}')
        self.session.responses.append(response)
        self.c4_2_client.join()
        response = ResponseStub(200,'{"session": "abc", "next": 1, "winner": 0, "board": []}')
        self.session.responses.append(response)
        self.assertIsNone(self.c4client.wait_for_turn())


    def test_wait_for_turn_board(self):
        response = ResponseStub(200,'{"session": "abc", "player": 1, "board": []}')
        self.session.responses.append(response)
        self.c4client.join()
        # create another client                                                                                                                        
        self.c4_2_client = ConnectFourClient(self.c4client.host, self.c4client.port, 'bob', self.session)
        response = ResponseStub(200,'{"session": "abc", "player": "bob"}')
        self.session.responses.append(response)
        self.c4_2_client.join()
        response = ResponseStub(200,'{"session": "abc", "next": 1, "winner": 0, "board": []}')
        self.session.responses.append(response)
        self.c4client.wait_for_turn()
        self.assertEqual([], self.c4client.board)
        
