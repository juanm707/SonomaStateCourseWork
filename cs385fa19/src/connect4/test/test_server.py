import unittest

from ..server import ConnectFourController
from ..models import C4Session

class FakeBackend:

    def __init__(self, db=None):
        self.rows = []  # used to return values
        self.saved = []  # used to gather saved values

    def get_session(self, session_id):
        return self.rows[0]

    def find_open_sessions(self):
        return self.rows

    def save_session(self, c4session):
        self.saved.append(c4session)

    def set_backend(self, rows):
        self.rows = rows


class ServerTests(unittest.TestCase):

    def test_join_previous_session(self):
        """
        a request is assigned a previously created session that was open
        """
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = C4Session(id='blablabla', board='', player_1='joe')
        db.set_backend([session])
        resp = controller.join(None, {'username': ['moe']}, None)
        self.assertEqual(db.saved[0].player_2, 'moe')
        self.assertEqual(209, resp.status_code)
        self.assertEqual(
            {'msg': 'Joined session',
             'session': 'blablabla',
             'player': 2},
            resp.content
        )

    def test_join_new_session(self):
        """
        a requests is assigned a newly created session
        """
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = C4Session(id='blablabla', board='', player_1='joe')
        db.set_backend(None)
        resp = controller.join(None, {'username': ['moe']}, None)
        self.assertEqual(db.saved[0].player_1, 'moe')
        self.assertEqual(201, resp.status_code)
        # since the session is new, a new id is assigned, so we have to assert on individual fields
        self.assertEqual('Session created', resp.content['msg'])
        self.assertEqual(1, resp.content['player'])
        # since the uuid is random, we can't assert on its value.
        # however, and auto generated id should be an uuid, which is a 36 characters long string
        self.assertEqual(36, len(resp.content['session']))

    def test_join_previous_session_same_user(self):
        """
        join with a request made with a user that already has an open session
        """
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = C4Session(id='123', player_1='joe')
        db.set_backend([session])
        resp = controller.join(None, {'username': ['joe']}, None)
        self.assertEqual(len(db.saved), 0)
        self.assertEqual(200, resp.status_code)
        self.assertEqual(
            {'msg': 'Existing Session found',
             'session': '123',
             'player': 1},
            resp.content
        )

    def test_move_no_session(self):
        """
        move request does not specify a session
        """
        db = FakeBackend()
        controller = ConnectFourController(db)
        resp = controller.move(None, None, None)
        self.assertEqual(400, resp.status_code)
        self.assertEqual({'error': 'Session is required.'}, resp.content)

    def test_move_session_no_column(self):
        """
        move request does not specify a column
        """
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = C4Session(player_1='joe', status=1)
        db.set_backend([session])
        resp = controller.move(None, {'username': ['joe']}, '123')
        self.assertEqual(400, resp.status_code)
        self.assertEqual({'error': 'Username and column are required.'}, resp.content)

    def test_move_session_ended(self):
        """
        move request is made for a session that has a winner
        """
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = C4Session(player_1='joe', status=1)
        db.set_backend([session])
        resp = controller.move(None, {'username': ['joe'], 'column':['1']}, '123')
        self.assertEqual(400, resp.status_code)
        self.assertEqual({'error': 'Session ended'}, resp.content)

    def test_move_session_ended(self):
        """
        move request is made for a session that ended in draw (status=3)
        """
        db = FakeBackend()
        controller = ConnectFourController(db)
        session = C4Session(player_1='joe', status=3)
        db.set_backend([session])
        resp = controller.move(None, {'username': ['joe'], 'column':['1']}, '123')
        self.assertEqual(400, resp.status_code)
        self.assertEqual({'error': 'Session ended'}, resp.content)

    
    def test_move_column_full(self):
        """
        move request is made for a column that is already full
        test sets up column 0 as full.
        """
        db = FakeBackend()
        controller = ConnectFourController(db)
        board_with_c1_full = '1      2      1      2      1      2      '
        session = C4Session(id='123', board=board_with_c1_full, player_1='joe', player_2='moe', status=0)
        db.set_backend([session])
        resp = controller.move(None, {'username': ['joe'], 'column':['0']}, '123')
        self.assertEqual(400, resp.status_code)
        self.assertEqual({'error': 'Invalid Move'}, resp.content)

    def test_move_invalid_column(self):
        """
        move request is made for a column that is invalid (7)
        """
        db = FakeBackend()
        controller = ConnectFourController(db)
        board = '                                          '
        session = C4Session(id='123', board=board, player_1='joe', player_2='moe', status=0)
        db.set_backend([session])
        resp = controller.move(None, {'username': ['joe'], 'column':['7']}, '123')
        self.assertEqual(400, resp.status_code)
        self.assertEqual({'error': 'Invalid Move'}, resp.content)

    def test_move_invalid_turn(self):
        """
        move request is made for by a player whose turn is not ready yet
        """
        db = FakeBackend()
        controller = ConnectFourController(db)
        board = '                                          '
        session = C4Session(id='123', board=board, player_1='joe', player_2='moe', status=0)
        db.set_backend([session])
        resp = controller.move(None, {'username': ['moe'], 'column':['1']}, '123')
        self.assertEqual(400, resp.status_code)
        self.assertEqual({'error': 'Player not allowed to make a move at this time.'}, resp.content)

    def test_move_invalid_username(self):
        """
        move request is made for a user that is not either player 1 or 2
        """
        db = FakeBackend()
        controller = ConnectFourController(db)
        board = '                                          '
        session = C4Session(id='123', board=board, player_1='joe', player_2='moe', status=0)
        db.set_backend([session])
        resp = controller.move(None, {'username': ['noe'], 'column':['1']}, '123')
        self.assertEqual(400, resp.status_code)
        self.assertEqual({'error': 'Invalid Username'}, resp.content)

    def test_satus_with_invalid_session(self):
        """
        status request specifies an invalid session
        """
        db = FakeBackend()
        controller = ConnectFourController(db)
        db.set_backend([None])
        resp = controller.status(None, None, '123')
        self.assertEqual(404, resp.status_code)
        self.assertEqual({'error': 'Not found'}, resp.content)


