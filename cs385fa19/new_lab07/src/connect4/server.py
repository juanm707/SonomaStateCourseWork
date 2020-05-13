#!/usr/bin/python3
# -*- coding: utf-8 -*-
import argparse
from collections import namedtuple
import json
from http.server import HTTPServer, BaseHTTPRequestHandler
from urllib.parse import urlparse, parse_qs
import logging

from connect4.models import C4Session, InvalidMoveError, PlayerTurnError
from connect4.db import SQLiteBackend

log = logging.getLogger(__name__)


Response = namedtuple('Response', ('status_code', 'content'))


class ConnectFourController():

    def __init__(self, db):
        self.db = db
        self.handlers = {
            '/join': self.join,
            '/status': self.status,
            '/move': self.move
        }

    def handle_request(self, path, params, session):
        handler = self.handlers.get(path, None)
        if handler:
            return handler(path, params, session)
        return Response(404, {"error": "Not found"})

    def join(self, path, query, _):
        """
        Handles a request to join a ConnectFour session
        Requires the username url query parameter
        If there are no open sessions available a new session is created.
        """
        username = query.get('username', [None])[0]
        if username:
            open_sessions = self.db.find_open_sessions()
            if open_sessions:
                row = open_sessions[0]
                if row.player_1 == username:
                    return Response(200, {"msg": "Existing Session found", "session": row.id, "player": 1})
                else:
                    row.player_2 = username
                    self.db.save_session(row)
                    return Response(209, {"msg": "Joined session", "session": row.id, "player": 2})
            else:
                row = C4Session(player_1=username)
                self.db.save_session(row)
                return Response(201, {"msg": "Session created", "session": row.id, "player": 1})
        else:
            return Response(400, {"error": "Missing username"})

    def status(self, path, query, session):
        """
        Handles a request to get the status of a ConnectFour session
        Requires the session header.
        The status consists of the board, a winner if there is one and the next player to move.
        """
        if not session:
            return Response(400, {"error": "No session was specified."})
        row = self.db.get_session(session)

        if row:
            board = [[0, 0, 0, 0, 0, 0, 0] for _ in range(6)]
            for idx in range(42):
                rowidx = idx // 7
                colidx = idx % 7
                board[rowidx][colidx] = row.board[idx]
            next_player = 1 + (row.board.count(' ') % 2) if row.status == 0 else 0
            return Response(200, {"board": board, "winner": row.status, "next": next_player})

        return Response(404, {"error": "Not found"})

    def move(self, path, query, session):
        """
        Handles a request to make a move.
        Requires the session id header and the username and column url query parameters
        If the move can not be applied an error response is returned.
        If after the move the game ends, the response reflects
        """

        if not session:
            return Response(400, {"error": "Session is required."})

        username = query.get('username', [None])[0]
        column_str = query.get('column', [None])[0]

        if not username or not column_str:
            return Response(400, {"error": "Username and column are required."})

        row = self.db.get_session(session)

        if not row:
            return Response(404, {"error": "Not found"})
        
        if row.status != 0:
            return Response(400, {"error": "Session ended"})

        if username not in (row.player_1, row.player_2):
            return Response(400, {"error": "Invalid Username"})

        player = 1 if username == row.player_1 else 2
        column = int(column_str)
        try:
            row.apply_move(player, column)
            if row.status == player:
                resp = Response(201, {"msg": "success", "game_status": "ended", "winner": username})
            elif row.status == 3:
                resp = Response(201, {"msg": "success", "game_status": "ended", "winner": "None"})
            else:
                resp = Response(201, {"msg": "success", "game_status": "in progress", "winner": "None"})
            self.db.save_session(row)
            return resp

        except InvalidMoveError:
            return Response(400, {"error": "Invalid Move"})
        except PlayerTurnError:
            return Response(400, {"error": "Player not allowed to make a move at this time."})


class ConnectFourRequestHandler(BaseHTTPRequestHandler):

    def __init__(self, controller, *args, **kwargs):
        self.controller = controller
        super().__init__(*args, **kwargs)

    def do_GET(self):
        """
        Handles a GET request, forwards to the controller and writes
        the response as specified by the controller
        """
        parsed_url = urlparse(self.path)
        session = self.headers.get('session', None)
        try:
            resp = self.controller.handle_request(
                parsed_url.path,
                parse_qs(parsed_url.query),
                session,
            )
            self.send_response(resp.status_code)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps(resp.content).encode('UTF-8'))

        except Exception:
            log.exception("Unable to process request to %s", self.path)
            self.send_response(503)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(b'Internal Server Error')


class ConnectFourRequestHandlerFactory():
    """
    Factory class that produces request handlers
    """

    def __init__(self, controller):
        self.controller = controller

    def __call__(self, *args, **kwargs):
        return ConnectFourRequestHandler(self.controller, *args, **kwargs)


if __name__ == '__main__':

    parser = argparse.ArgumentParser('Connect Four HTTP Server')
    parser.add_argument('--port', '-p', type=int, default=8080, help='Port number where the server will listen.')
    args = parser.parse_args()

    controller = ConnectFourController(SQLiteBackend())
    server = HTTPServer(('0.0.0.0', args.port), ConnectFourRequestHandlerFactory(controller))
    server.serve_forever()
