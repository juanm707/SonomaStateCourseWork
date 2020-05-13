import sqlite3
from connect4.models import C4Session

DEFAULT_DATABASE = 'connect4.db'


def c4session_row_factory(cursor, row):
    return C4Session(*row)


class SQLiteBackend:

    def __init__(self, db=DEFAULT_DATABASE):
        self.db = db
        self.connection = sqlite3.connect(self.db)
        self.connection.row_factory = c4session_row_factory
        self._setup_database()

    def _setup_database(self):
        """
        Creates database structure if it does not exist
        """
        sql_statement = """CREATE TABLE IF NOT EXISTS sessions (
                                id TEXT PRIMARY KEY,
                                board TEXT,
                                player_1 TEXT,
                                player_2 TEXT,
                                status INTEGER
                        );"""
        self.connection.execute(sql_statement)

    def get_session(self, session_id):
        cursor = self.connection.cursor()
        cursor.execute('SELECT * FROM sessions WHERE id=?', (session_id,))
        return cursor.fetchone()

    def find_open_sessions(self):
        cursor = self.connection.cursor()
        cursor.execute('SELECT * FROM sessions WHERE player_2 IS NULL')
        return cursor.fetchall()

    def save_session(self, c4session):
        if c4session and c4session.id and c4session.board and c4session.player_1:
            cursor = self.connection.cursor()
            cursor.execute('INSERT OR REPLACE INTO sessions (id, board, player_1, player_2, status) '
                           'VALUES (:id, :board , :player_1, :player_2, :status)',
                           c4session.as_dict())
            self.connection.commit()
        else:
            raise Exception("Unable to save incomplete session.")
