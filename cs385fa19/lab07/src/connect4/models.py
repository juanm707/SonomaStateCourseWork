import uuid


class InvalidMoveError(Exception):
    """To be raised when the move is not possible because the column is full"""
    pass


class PlayerTurnError(Exception):
    """To be raised when it is not he player's turn"""
    pass


class C4Session:
    def __init__(self, id=None, board=None, player_1=None, player_2=None, status=0):
        
        if not player_1:
            raise Exception("Player 1 is required")

        self.id = id if id else str(uuid.uuid4())
        self.board = board if board else ' ' * 42
        self.player_1 = player_1
        self.player_2 = player_2
        self.status = status

    def as_dict(self):
        return {
            'id': self.id,
            'board': self.board,
            'player_1': self.player_1,
            'player_2': self.player_2,
            'status': self.status
        }

    def __repr__(self):
        return str(self.as_dict())

    def apply_move(self, player, column):
        """
        Verifies that the move is possible.
        If the number of available spaces is even, then it is player_1'sturn
        """
        if column < 0 or column > 6:
            raise InvalidMoveError("Invalid Column")

        player_1_turn = (self.board.count(' ') % 2) == 0
        idx = column
        while idx < 42:
            if self.board[idx] == ' ':
                break
            idx += 7

        if idx > 41:
            raise InvalidMoveError("Requested column is full")

        if player_1_turn and player == 1 or not player_1_turn and player == 2:
            self.board = self.board[0:idx] + str(player) + self.board[idx+1:]
            if self.check_full():
                self.status = 3
            elif self.check_winner(idx, player):
                self.status = player
            return

        raise PlayerTurnError("Player not allowed to move")

    def check_full(self):
        for cell in self.board[-7:]:
            if cell == ' ':
                return False
        return True

    def check_winner(self, idx, player):

        row = idx // 7
        col = idx % 7

        deltas = [
            (1, 1),   # north east direction
            (-1, 1),  # south east direction
            (1, 0),   # north
            (0, 1),   # eash
        ]
        player_str = str(player)
        for row_inc, col_inc in deltas:
            cur_col = col - (3 * col_inc)
            cur_row = row - (3 * row_inc)
            while True:
                connect = 0
                if cur_col >= 0 and cur_row >= 0 and cur_row < 6:  # check cell is within boundaries
                    cur_idx = cur_row * 7 + cur_col
                    while cur_col < 7 and cur_row >= 0 and cur_row < 6 and self.board[cur_idx] == player_str and connect < 4:
                        connect += 1
                        cur_col += col_inc
                        cur_row += row_inc
                        cur_idx = cur_row * 7 + cur_col
                    if connect == 4:
                        return True
                # if we got here, the last cell checked was either other player's or empty
                cur_col += col_inc
                cur_row += row_inc
                if cur_col >= col:
                    break
        return False
