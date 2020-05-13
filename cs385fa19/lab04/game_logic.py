# juanmartinez
import random

"""
Do not import any additional libraries that are not part of the standard Python library.
"""


SIZE = 4
TILE_HEIGHT = 5
TILE_WIDTH = 8
BOARD_WIDTH = SIZE * TILE_WIDTH
BOARD_HEIGHT = SIZE * TILE_HEIGHT

# ADDED BY STUDENT
PROB_BOARD = [2, 2, 2, 2, 4]


def initialize_board():
    """
    Initializes a board with two randomly added tiles
    A board is a 2D array of SIZE x SIZE.
    Each element on the 2D array will correspond to a tile in the game
    A value of 0 indicates an empty tile
    """
    board = [[0 for _ in range(SIZE)] for _ in range(SIZE)]

    row = random.randint(0, 3)
    col = random.randint(0, 3)
    temp_r, temp_c = row, col
    board[row][col] = random.choice(PROB_BOARD)
    done = False

    while not done:
        row = random.randint(0, 3)
        col = random.randint(0, 3)
        if (row == temp_r) & (col == temp_c):
            pass
        else:
            board[row][col] = random.choice(PROB_BOARD)
            done = True

    return board


def add_random_tile(board):
    """
    Takes a board and randomly adds a new tile
    with a value of 2 or 4 with the former with a probability of 90% ???? 80%?????
    If the board is full, simply refuse to add a new tile.
    """
    empty = get_empty_tiles(board)
    if len(empty) == 0:
        pass
    else:
        cords = random.choice(empty)

        row, col = cords[0], cords[1]
        board[row][col] = random.choice(PROB_BOARD)
        empty.remove(cords)  # remove the coordinate since it has a value now and is not empty. Not sure if needed


def get_empty_tiles(board):
    """
    Returns a list of empty tiles.
    Tiles should be represented as a tuple in the form (row, column)
    e.g. A board with this configuration:

          c0  c1  c2  c3
         ╔═══╦═══╦═══╦═══╗
      r0 ║ 2 ║ 2 ║   ║   ║
         ╠═══╬═══╬═══╬═══╣
      r1 ║   ║ 4 ║ 2 ║ 2 ║
         ╠═══╬═══╬═══╬═══╣
      r2 ║16 ║   ║ 8 ║ 2 ║
         ╠═══╬═══╬═══╬═══╣
      r3 ║32 ║   ║512║   ║
         ╚═══╩═══╩═══╩═══╝


    should return a list:

    [(0, 2), (0, 3), (1, 0), (2, 1), (3, 1), (3, 3)]

    Tiles are not expected to be sorted
    """
    empty_tiles = []

    for row in range(SIZE):
        for col in range(SIZE):
            if board[row][col] == 0:
                empty_tiles.append((row, col))
            else:
                pass
    return empty_tiles


def move_up(board):
    """
    Applies a move in the up direction to all the tiles in a board.
    This function should apply the move directly to the passed board.
    This function returns a boolean that indicates if tiles were moved (or not)

    As an example, the following board will return False since no tiles can be moved in an
    upward direction:

           c0  c1  c2  c3
         ╔═══╦═══╦═══╦═══╗
      r0 ║ 2 ║ 2 ║   ║   ║
         ╠═══╬═══╬═══╬═══╣
      r1 ║ 8 ║ 4 ║   ║   ║
         ╠═══╬═══╬═══╬═══╣
      r2 ║   ║   ║   ║   ║
         ╠═══╬═══╬═══╬═══╣
      r3 ║   ║   ║   ║   ║
         ╚═══╩═══╩═══╩═══╝

    """
    copy_board = [row[:] for row in board]
    moved = False
    for row in range(1, SIZE):  # skip top row since it cant be moved up
        for col in range(SIZE):
            if board[row][col] == 0:
                pass
            else:
                new_row = _find_next_position_up(board, row, col)  # new coordinates if there are any
                if new_row == row:  # did not move tile, but can still be merged
                    if board[row][col] == board[row-1][col]:  # if they have same values...
                        board[row - 1][col] *= 2  # the upper most gets doubled
                        board[row][col] = 0  # set to empty since it has been merged
                        moved = True  # since it was merged
                else:
                    board[new_row][col] = board[row][col]  # update the board pre merge
                    board[row][col] = 0  # since it has now moved
                    v, h = _is_tile_movable(copy_board, row, col)  # is _tile_moveable?
                    if v:  # able to merge vertically, we do not care about h here
                        if new_row != 0:
                            if board[new_row][col] == board[new_row-1][col]:  # if they have same values...
                                board[new_row - 1][col] *= 2  # the upper most gets doubled
                                board[new_row][col] = 0  # set to empty since it has been merged
                    moved = True  # even if it was not merged, it still moved up

    return moved


def _find_next_position_up(board, row, col):
    """
    Support function that takes a board, and a tile coordinates,
    and returns the position where it should be located after moving upward.
    This function does not consider merging of the tile with the next neighbor, it only considers
    available spots due to them being empty and withing the board boundaries
    """
    moving = True
    if board[row][col] == 0:
        return row
    if row == 0:  # top row
        return row

    else:
        while moving:
            if board[row-1][col] == 0:  # If the position above is empty
                row -= 1
                if row == 0:  # Can not move up anymore
                    return row
            else:  # row - 1 would hit an occupied tile so return row
                moving = False
                return row


def move_down(board):
    """
    Applies a move in the down direction to all the tiles in a board.
    This function should apply the move directly to the passed board.
    This function returns a boolean that indicates if tiles were moved (or not)
    """
    copy_board = [row[:] for row in board]
    moved = False
    for row in range(2, -1, -1):  # skip bottom row since it cant be moved down
        for col in range(SIZE):
            if board[row][col] == 0:
                pass
            else:
                new_row = _find_next_position_down(board, row, col)  # new coordinates if there are any
                if new_row == row:  # did not move tile, but can still be merged
                    if board[row][col] == board[row + 1][col]:  # if they have same values...
                        board[row + 1][col] *= 2  # the bottom most gets doubled
                        board[row][col] = 0  # set to empty since it has been merged
                        moved = True  # since it was merged
                else:
                    board[new_row][col] = board[row][col]  # update the board pre merge
                    board[row][col] = 0  # since it has now moved
                    v, h = _is_tile_movable(copy_board, row, col)  # is _tile_moveable?
                    if v:  # able to merge vertically, we do not care about h here
                        if new_row != 3:
                            if board[new_row][col] == board[new_row + 1][col]:  # if they have same values...
                                board[new_row + 1][col] *= 2  # the bottom most gets doubled
                                board[new_row][col] = 0  # set to empty since it has been merged
                    moved = True  # even if it was not merged, it still moved up

    return moved


def _find_next_position_down(board, row, col):
    """
    Support function that takes a board, and a tile coordinates,
    and returns the position where it should be located after moving downward
    This function does not consider merging of the tile with the next neighbor, it only considers
    available spots due to them being empty and withing the board boundaries
    """
    moving = True
    if board[row][col] == 0:
        return row
    if row == 3:  # bottom row
        return row

    else:
        while moving:
            if board[row + 1][col] == 0:  # If the position below is empty
                row += 1
                if row == 3:  # Can not move down anymore
                    return row
            else:  # row + 1 would hit an occupied tile so return row
                moving = False
                return row


def move_left(board):
    """
    Applies a move in the left direction to all the tiles in a board.
    This function should apply the move directly to the passed board.
    This function returns a boolean that indicates if tiles were moved (or not)
    """
    copy_board = [row[:] for row in board]
    moved = False
    for col in range(1, SIZE):  # skip first column since it cant be moved left
        for row in range(SIZE):
            if board[row][col] == 0:
                pass
            else:
                new_col = _find_next_position_left(board, row, col)  # new coordinates if there are any
                if new_col == col:  # did not move tile, but can still be merged
                    if board[row][col] == board[row][col-1]:  # if they have same values...
                        board[row][col-1] *= 2  # the left most gets doubled
                        board[row][col] = 0  # set to empty since it has been merged
                        moved = True  # since it was merged
                else:
                    board[row][new_col] = board[row][col]  # update the board pre merge
                    board[row][col] = 0  # since it has now moved
                    v, h = _is_tile_movable(copy_board, row, col)  # is _tile_moveable?
                    if h:  # able to merge horizontally, we do not care about v here
                        if new_col != 0:
                            if board[row][new_col] == board[row][new_col-1]:  # if they have same values...
                                board[row][new_col-1] *= 2  # the left most gets doubled
                                board[row][new_col] = 0  # set to empty since it has been merged
                    moved = True  # even if it was not merged, it still moved left

    return moved


def _find_next_position_left(board, row, col):
    """
    Support function that takes a board, and a tile coordinates,
    and returns the position where it should be located after moving leftward
    This function does not consider merging of the tile with the next neighbor, it only considers
    available spots due to them being empty and withing the board boundaries
    """
    moving = True
    if board[row][col] == 0:
        return col
    if col == 0:  # leftmost column
        return col

    else:
        while moving:
            if board[row][col-1] == 0:  # If the position to the left is empty
                col -= 1
                if col == 0:  # Can not move left anymore
                    return col
            else:  # col - 1 would hit an occupied tile so return row
                moving = False
                return col


def move_right(board):
    """
    Applies a move in the right direction to all the tiles in a board.
    This function should apply the move directly to the passed board.
    This function returns a boolean that indicates if tiles were moved (or not)
    """
    copy_board = [row[:] for row in board]
    moved = False
    for col in range(2, -1, -1):  # skip last column since it cant be moved right
        for row in range(SIZE):
            if board[row][col] == 0:
                pass
            else:
                new_col = _find_next_position_right(board, row, col)  # new coordinates if there are any
                if new_col == col:  # did not move tile, but can still be merged
                    if board[row][col] == board[row][col + 1]:  # if they have same values...
                        board[row][col + 1] *= 2  # the right most gets doubled
                        board[row][col] = 0  # set to empty since it has been merged
                        moved = True  # since it was merged
                else:
                    board[row][new_col] = board[row][col]  # update the board pre merge
                    board[row][col] = 0  # since it has now moved
                    v, h = _is_tile_movable(copy_board, row, col)  # is _tile_moveable?
                    if h:  # able to merge horizontally, we do not care about v here
                        if new_col != 3:
                            if board[row][new_col] == board[row][new_col + 1]:  # if they have same values...
                                board[row][new_col + 1] *= 2  # the right most gets doubled
                                board[row][new_col] = 0  # set to empty since it has been merged
                    moved = True  # even if it was not merged, it still moved right

    return moved


def _find_next_position_right(board, row, col):
    """
    Takes a board, and a tile coordinates,
    and returns the position where it should be located after moving rightward.
    This function does not consider merging of the tile with the next neighbor, it only considers
    available spots due to them being empty and withing the board boundaries
    """
    moving = True
    if board[row][col] == 0:
        return col
    if col == 3:  # rightmost column
        return col

    else:
        while moving:
            if board[row][col + 1] == 0:  # If the position to the right is empty
                col += 1
                if col == 3:  # Can not move right anymore
                    return col
            else:  # col + 1 would hit an occupied tile so return row
                moving = False
                return col


def is_game_over(board):
    """
    Returns a tuple with three elements:

    a boolean that indicates that the game is over if True
    a boolean that indicates that the game has been won if True
    a score that consists of the sum of all the tiles
    """
    game_over, game_won, score, flag = False, False, 0, 0  # flag is to check if at least one square is still move-able
    for row in range(SIZE):
        for col in range(SIZE):
            if board[row][col] == 0:  # at least one open space
                flag = 1
                game_over = False
            v, h = _is_tile_movable(board, row, col)
            if (v or h) & (flag == 0):
                flag = 1
                game_over = False
            elif ((not v) & (not h)) & (flag == 0):
                game_over = True
            if board[row][col] == 2048:
                game_won = True
            score += board[row][col]

    return game_over, game_won, score


def _is_tile_movable(board, row, col):
    """
    Helper function that Determines if a tile can be moved due to the presence of adjacent spaces
    of neighbors with the same value
    This function assumes that is called in a sequence that goes from left to
    right and then from up to down, so it only needs to check on the right and down neighbors.
    """
    vertical, horizontal = False, False
    c_col = 0
    while c_col != SIZE:
        if c_col == col:
            c_col += 1
        elif (abs(c_col - col) == 1) & (board[row][col] == board[row][c_col]):
            horizontal = True
            break
        elif board[row][c_col] == 0:
            horizontal = True
            break
            #############
            #c_col += 1
            #pass
            ############
        elif board[row][col] != board[row][c_col]:
            horizontal = False
            c_col += 1
        else:
            c_col += 1

    c_row = 0
    while c_row != SIZE:
        if c_row == row:
            c_row += 1
        elif (abs(c_row - row) == 1) & (board[row][col] == board[c_row][col]):
            vertical = True
            break
        elif board[c_row][col] == 0:
            vertical = True
            break
            #####c_row += 1
            #######pass
        elif board[row][col] != board[c_row][col]:
            vertical = False
            c_row += 1
        else:
            c_row += 1

    return vertical, horizontal
