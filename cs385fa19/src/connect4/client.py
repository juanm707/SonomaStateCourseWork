#!/usr/bin/python3
# -*- coding: utf-8 -*-

import argparse
import json
import time
import random
import sys

import requests
import names


class TurnTimeoutException(Exception):
    """
    Exception to be raised when the wait for a turn times out
    """

class UnableToJoinException(Exception):
    """
    Exception to be raised when unable to join a session
    """


class ConnectFourClient:

    def __init__(self, host, port, playername, session, turn_timeout=15):
        self.host = host
        self.port = port
        self.base_url = 'http://{}:{}'.format(host, port)
        self.player_name = playername if playername else names.get_first_name()
        self.player_id = None
        self.session_id = None
        self.session = session
        self.ended = False
        self.turn_timeout = turn_timeout
        self.board = [[" " for _ in range(7)] for _ in range(6)]

    def make_request(self, endpoint, query_args):
        """
        Makes a request to the specified endpoint (string)
        with the specified query arguments (dict) and returns the
        response verbatim
        """
        return self.session.get(
            '{}/{}'.format(self.base_url, endpoint),
            params=query_args
        )

    def start(self):
        self.join()
        while True:
            # wait_for_turn updates the state of the game
            self.wait_for_turn()
            if not self.ended:
                self.make_move()
            else:
                break
        self.print_board()

    def join(self):
        print('Attempting to join session with username: {}'.format(self.player_name))
        resp = self.make_request('join', {'username': self.player_name})
        if resp.status_code in [200, 201, 209]:
            payload = resp.json()
            self.session_id = payload['session']
            self.session.headers.update({'session': self.session_id})
            self.player_id = payload['player']
            print('Joined session {} as player {}'.format(self.session_id, self.player_id))
        else:
            raise UnableToJoinException("Unable to Unable to establish a session: {}".format(resp.text))

    def wait_for_turn(self):
        print('Waiting for turn')
        end_time = int(time.time()) + self.turn_timeout
        next_player = -1
        ended = False
        while next_player != self.player_id and not ended:
            resp = self.make_request('status', {})
            if resp.status_code != 200:
                print('Unable to get session status')
                next_player = -1
                sleep(0.2)
                continue
            
            payload = resp.json()
            next_player = payload['next']
            winner = payload['winner']

            ended = next_player == 0 or winner > 0

            if next_player != self.player_id and not ended:
                if time.time() > end_time:
                    raise TurnTimeoutException("Client timed out waiting for turn")
                time.sleep(0.2)
            elif ended:
                self.ended = True
                self.winner = winner
                self.board = payload['board']
            else:
                print('Client ready to make move')
                self.board = payload['board']

    def make_move(self):
        available = self.find_available_columns()
        column = random.choice(available)
        resp = self.make_request('move', {'username': self.player_name, 'column': column})
        if resp.status_code != 201:
            # Add better handling for invalid move
            print('Unable to make a move: {}'.format(resp.text))
            sys.exit(1)
        return resp.json()

    def find_available_columns(self):
        available = []
        for column in range(7):
            if self.board[-1][column] == " ":
                available.append(column)
        return available

    def print_board(self):

        if self.winner == self.player_id:
            print('Game Won!!!')
        elif self.winner == 0:
            print('Game Tied.')
        else:
            print('Game Lost.')

        for row in reversed(self.board):
            print(' '.join(row))
            #rowstr = ' '.join(row)
            #for char in rowstr:
            #    colored_print(char)
            #colored_print(' ')
            #print('')

def colored_print(character):
    if character == ' ':
        print("\033[44m\033[34m \033[00m", end='')
    elif character == '1':
        print("\033[44m\033[31m⬤\033[00m", end='') 
    elif character == '2':
        print("\033[44m\033[33m⬤\033[00m", end='') 
    else:
        print(character, end='')


if __name__ == '__main__':

    parser = argparse.ArgumentParser('Connect Four HTTP Client')
    parser.add_argument('--hostname', type=str, default='127.0.0.1', help='Hostname where the Connect Four server is running')
    parser.add_argument('--port', type=int, default=80, help='Port number where the Connect Server is listening')
    parser.add_argument('--player', type=str, default=None, help='Player name')
    parser.add_argument('--timeout', type=int, default=10, help='Turn timeout')
    args = parser.parse_args()

    client = ConnectFourClient(args.hostname, args.port, args.player, requests.Session(), args.timeout)
    try:
        client.start()
    except TurnTimeoutException:
        print("Wait for turn timed out after {} seconds".format(args.timeout))
        sys.exit(1)
    except UnableToJoinException as ex:
        print(ex)
        sys.exit(1)
