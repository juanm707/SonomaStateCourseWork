# juan martinez
import unittest

from server import ConnectFourController, Response
from models import C4Session


class FakeBackend:

    def __init__(self, db=None):
        self.row = []
        self.saved = []

    def get_session(self, session_id):
        return self.rows[0]

    def find_open_sessions(self):
        return self.rows

    def save_session(self, c4session):
        self.saved.append(c4session)

    def set_backend(self, rows):
        self.rows = rows


class TestJoin(unittest.TestCase):
    
    # 1
    def test_newly_created_session(self):

        db = FakeBackend()
        controller = ConnectFourController(db)
        db.set_backend([])  # No sessions
        controller.join(None, {'username': ['joe']}, None)
        # print(db.saved[0].player_1)
        self.assertEqual('joe', db.saved[0].player_1)

    # 2
    def test_previously_created_session(self):

        db = FakeBackend()
        controller = ConnectFourController(db)
        session = C4Session(id='something', board='', player_1='joe')
        db.set_backend([session])
        controller.join(None, {'username': ['moe']}, None)
        # print(db.saved[0].player_2)
        self.assertEqual('moe', db.saved[0].player_2)

    # Enhancement to Implement Test Case - Same Username
    def test_same_username(self):

        expected_result = Response(400, {"error": "Must use a different username"})
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = C4Session(id='something', board='', player_1='joe')
        db.set_backend([session])
        result = controller.join(None, {'username': ['joe']}, None)
        self.assertEqual(expected_result, result)


class TestMove(unittest.TestCase):
    
    # Number 1 on /move test cases
    def test_user_not_match_session_in_request(self):
    
        expected_result = Response(400, {"error": "Invalid Username"})
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = [C4Session(id='something', board='', player_1='joe', player_2='moe'), C4Session(id='something2', board='', player_1='juan', player_2='bob')]  # Create a session with two players
        db.set_backend(session)
        db.saved.append(session[0])
        db.saved.append(session[1])
        result = controller.move(None, {'username': ['juan'], 'column': ['1']}, 'something')
        self.assertEqual(expected_result, result)
    
    
    # Number 6 on /move test cases
    def test_user_does_not_match(self):
        
        expected_result = Response(400, {"error": "Invalid Username"})
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = C4Session(id='something', board='', player_1='joe', player_2='moe')  # Create a session with two players
        db.set_backend([session])
        db.saved.append(session)
        result = controller.move(None, {'username': ['bob'], 'column': ['1']}, 'something')
        self.assertEqual(expected_result, result)

    # 2
    def test_move_when_session_ended(self):

        expected_result = Response(400, {"error": "Session ended"})
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = C4Session(id='something', board='', player_1='joe', player_2='moe', status=1)
        db.set_backend([session])
        db.saved.append(session)
        result = controller.move(None, {'username': ['joe'], 'column': ['1']}, 'something')
        self.assertEqual(expected_result, result)

    # 3
    def test_move_invalid_column(self):

        expected_result = Response(400, {"error": "Invalid Move"})
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = C4Session(id='something', board='', player_1='joe', player_2='moe', status=0)
        db.set_backend([session])
        db.saved.append(session)
        result = controller.move(None, {'username': ['joe'], 'column': ['10']}, 'something')
        self.assertEqual(expected_result, result)

    # 4
    def test_move_column_full(self):

        expected_result = Response(400, {"error": "Invalid Move"})
        # Column 0 is full!
        b = '1      1      1      1      1      1      '
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = C4Session(id='something', board=b, player_1='joe', player_2='moe', status=0)
        db.set_backend([session])
        db.saved.append(session)
        result = controller.move(None, {'username': ['joe'], 'column': ['0']}, 'something')
        self.assertEqual(expected_result, result)

    # 5
    def test_move_wrong_player_turn(self):

        expected_result = Response(400, {"error": "Player not allowed to make a move at this time."})
        
        b = '1                                         '  # Should be player 2 moe turn
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = C4Session(id='something', board=b, player_1='joe', player_2='moe', status=0)
        db.set_backend([session])
        db.saved.append(session)
        result = controller.move(None, {'username': ['joe'], 'column': ['0']}, 'something')
        self.assertEqual(expected_result, result)


class TestStatus(unittest.TestCase):

    # 1
    def test_invalid_session(self):

        expected_result = Response(404, {"error": "Not found"})
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = []
        db.set_backend([session])
        result = controller.status(None, None, 'something')
        self.assertEqual(expected_result, result)

