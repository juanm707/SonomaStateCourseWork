import os
import unittest
import json
import threading
import time

from http.server import HTTPServer

import names
import requests

from connect4.db import SQLiteBackend
from connect4.client import ConnectFourClient, UnableToJoinException, TurnTimeoutException
from connect4.server import ConnectFourController, ConnectFourRequestHandlerFactory


server_port = int(os.environ.get('PORT', 8080))


class WaitableHTTPServer(HTTPServer):

    def __init__(self, *args, **kwargs):
        super(WaitableHTTPServer, self).__init__(*args, **kwargs)

    def start(self, event):
        event.set()
        self.serve_forever()


class IntegrationTests(unittest.TestCase):

    def run_server(self):
        self.controller = ConnectFourController(SQLiteBackend(self.database))
        self.server = WaitableHTTPServer(('0.0.0.0', server_port), ConnectFourRequestHandlerFactory(self.controller))
        self.server.start(self.server_started)

    def setUp(self):
        # clean up the database after each test
        self.database = 'itest.db'
        try:
            os.remove(self.database)
        except FileNotFoundError:
            # if the file has already been removed, ignore
            pass
        
        self.server = None
        self.controller = None

        # event used to wait for the server to start
        self.server_started = threading.Event()

        # start the server in a thread, otherwise self.serve_forever() blocks
        self.server_thread = threading.Thread(name='connect4_server', target=self.run_server)
        self.server_thread.daemon = True
        self.server_thread.start()

        # wait for the server to be started
        self.server_started.wait()

        self.player1 = names.get_first_name()
        self.player2 = self.player1
        while self.player2 == self.player1:
            self.player2 = names.get_first_name()

        self.client_session = requests.Session()
        self.client = ConnectFourClient('127.0.0.1', server_port, self.player1, self.client_session)

    def tearDown(self):
        # stop the server, and wait for the thread to end
        self.server.server_close()
        self.server.shutdown()
        self.server_thread.join()
        # close the client session 
        self.client_session.close()

    def test_client_join(self):
        self.client.join()
        # make a bunch of asssertions here

