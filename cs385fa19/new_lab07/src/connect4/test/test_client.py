import unittest
import json

from connect4.client import ConnectFourClient, UnableToJoinException, TurnTimeoutException


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

    def test_make_request(self):
        """
        make_request shall call the get method of the 
        session object with an url that is equal to the base url with the endpoint appended
        at the end, with the query arguments passed as a keyworded argument
        """
        self.session.responses.append('zoo')
        self.c4client.make_request('goo', {'free': 'fallin'})
        self.assertEqual(self.session.calls[0], ('http://foo:80/goo', {'free': 'fallin'}))
        
    def test_join_success_201(self):
        """
        join should call the 'join' endpoint with the username instance variable as a query argument, and if
        successful, should set the 'session' field of the session header to the returned session_id
        """
        for code in [200, 201, 209]:
            response = ResponseStub(code, '{"session": "1234", "player": 34}')
            self.session.responses.append(response)
            self.c4client.join()
            self.assertEqual('1234', self.c4client.session_id, msg="Incorrect session_id with {}".format(code))
            self.assertEqual('1234', self.session.headers['session'], msg="Incorrect session header with {}".format(code))
            self.assertEqual(34, self.c4client.player_id, msg="Incorrect player with {}".format(code))

    def test_join_success(self):
        """
        join should raise an exception with codes not equal to 200, 201 or 209
        and the content of the response will not be parsed as JSON
        """
        for code in [400, 404, 503]:
            response = ResponseStub(code, 'Invalid request')
            self.session.responses.append(response)
            with self.assertRaises(UnableToJoinException, msg="Exception not raised for status code {}".format(code)):
                self.c4client.join()


