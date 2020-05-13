# juanmartinez
import unittest
import curses
from curses import wrapper

from random import Random


from game_logic import SIZE, BOARD_WIDTH, BOARD_HEIGHT, TILE_HEIGHT, TILE_WIDTH
from game_logic import (
    initialize_board,
    add_random_tile,
    move_up,
    move_down,
    move_left,
    move_right,
    is_game_over,
)

INITIAL_VALUES = (2, 4)


class TestInitializeBoard(unittest.TestCase):

    def test_board_size(self):
        """
        An initial board shall be a 2D array of SIZE x SIZE
        """
        board = initialize_board()
        self.assertEqual(len(board), SIZE)
        for row in range(SIZE):
            self.assertEqual(len(board[row]), SIZE)

    def test_board_initial_tiles(self):
        """
        An initial board shall only have two tiles with values 2 or 4.
        """
        board = initialize_board()
        tile_count = 0
        for row in range(SIZE):
            for col in range(SIZE):
                if board[row][col] != 0:
                    tile_count += 1
                    self.assertIn(board[row][col], INITIAL_VALUES)
        self.assertEqual(tile_count, 2)

    def test_initial_tiles_postions(self):
        """
        An initial board shall have its inital tiles in random positions
        There are 120 different combinations of 2 tile selections, therefore
        this test has a 1/120 probability of failure. This is not a good test.
        , """
        tile_positions = [[], []]
        board1 = initialize_board()
        board2 = initialize_board()
        for row in range(SIZE):
            for col in range(SIZE):
                if board1[row][col] != 0:
                    tile_positions[0].append(row * SIZE + col)
                if board2[row][col] != 0:
                    tile_positions[1].append(row * SIZE + col)

        self.assertNotEqual(tile_positions[0], tile_positions[1])


class AddRandomTileTests(unittest.TestCase):

    def test_add_random_tile_empty_board(self):
        """
        add_random_tile shall only add one tile to an empty board
        """

        board = [[0 for _ in range(SIZE)] for _ in range(SIZE)]
        tile_count = 0
        add_random_tile(board)
        for row in range(SIZE):
            for col in range(SIZE):
                if board[row][col] != 0:
                    tile_count += 1

        self.assertEqual(tile_count, 1)

    def test_add_random_tile_full_board(self):
        """
        add_random_tile shall not modify a full board
        """

        board = [[8, 512, 16, 32], [8, 16, 32, 1024], [128, 64, 16, 16], [8, 256, 16, 64]]
        expected_board = [[8, 512, 16, 32], [8, 16, 32, 1024], [128, 64, 16, 16], [8, 256, 16, 64]]
         
        tile_count = 0
        add_random_tile(board)
        self.assertEqual(board, expected_board)

    def test_add_random_tile_one_empty_tile(self):
        """
        add_random_tile shall not mofify a full board
        """
        board = [[8, 16, 16, 32], [8, 16, 32, 1024], [128, 16, 0, 16], [8, 256, 16, 64]]
        add_random_tile(board)
        self.assertIn(board[2][2], INITIAL_VALUES)

    def test_add_random_tile_partial_board(self):
        board = [[8, 16, 0, 32], [8, 16, 0, 1024], [128, 16, 0, 16], [0, 256, 16, 64]]
        original_board = [[8, 16, 0, 32], [8, 16, 0, 1024], [128, 16, 0, 16], [0, 256, 16, 64]]
        add_random_tile(board)
        new_tile_count = 0
        for row in range(SIZE):
            for col in range(SIZE):
                if board[row][col] != original_board[row][col]:
                    new_tile_count += 1
                    self.assertIn(board[row][col], INITIAL_VALUES)
        self.assertEqual(new_tile_count, 1)


class MoveTests(unittest.TestCase):

    def test_move_up_from_bottom(self):
        """
        All the values from the bottom two rows should fill rows 0 and 1, and their original positions should now have 0
        Return value should be true
        """
        board = [[0, 0, 0, 0], [0, 0, 0, 0], [128, 64, 32, 16], [8, 256, 16, 64]]
        expected_board = [[128, 64, 32, 16], [8, 256, 16, 64], [0, 0, 0, 0], [0, 0, 0, 0]]
        bool = move_up(board)
        self.assertEqual(board, expected_board)
        self.assertTrue(bool)

    def test_move_up_merge(self):
        """
        Tests that the tiles that can be merged, adjacent neighbors with same value, are merged
        Return value should be true
        """
        board = [[2, 4, 8, 16],
                 [2, 4, 8, 16],
                 [32, 64, 128, 256],
                 [32, 64, 128, 256]]
        expected_board = [[4, 8, 16, 32], [64, 128, 256, 512], [0, 0, 0, 0], [0, 0, 0, 0]]
        bool = move_up(board)
        self.assertEqual(board, expected_board)
        self.assertTrue(bool)

    def test_move_up_false(self):
        """
        Tests that the function returns false since no tiles can and were not moved
        """
        board = [[2, 4, 8, 16],
                 [16, 8, 4, 2],
                 [32, 64, 128, 256],
                 [256, 128, 64, 32]]
        expected_board = [[2, 4, 8, 16],
                          [16, 8, 4, 2],
                          [32, 64, 128, 256],
                          [256, 128, 64, 32]]
        bool = move_up(board)
        self.assertEqual(board, expected_board)
        self.assertFalse(bool)

    def test_move_down_from_top(self):
        """
        All the values from the top two rows should fill rows 2 and 3, and their original positions should now have 0
        Return value should be true
        """
        board = [[128, 64, 32, 16], [8, 256, 16, 64], [0, 0, 0, 0], [0, 0, 0, 0]]
        expected_board = [[0, 0, 0, 0], [0, 0, 0, 0], [128, 64, 32, 16], [8, 256, 16, 64]]
        bool = move_down(board)
        self.assertEqual(board, expected_board)
        self.assertTrue(bool)

    def test_move_down_merge(self):
        """
        Tests that the tiles that can be merged, adjacent neighbors with same value, are merged
        Return value should be true
        """
        board = [[2, 4, 8, 16],
                 [2, 4, 8, 16],
                 [32, 64, 128, 256],
                 [32, 64, 128, 256]]
        expected_board = [[0, 0, 0, 0], [0, 0, 0, 0], [4, 8, 16, 32], [64, 128, 256, 512]]
        bool = move_down(board)
        self.assertEqual(board, expected_board)
        self.assertTrue(bool)

    def test_move_down_false(self):
        """
        Tests that the function returns false since no tiles can and were not moved
        """
        board = [[2, 4, 8, 16],
                 [16, 8, 4, 2],
                 [32, 64, 128, 256],
                 [256, 128, 64, 32]]
        expected_board = [[2, 4, 8, 16],
                          [16, 8, 4, 2],
                          [32, 64, 128, 256],
                          [256, 128, 64, 32]]
        bool = move_down(board)
        self.assertEqual(board, expected_board)
        self.assertFalse(bool)

    def test_move_left_from_right(self):
        """
        All the values from the rightmost two columns should fill columns 0 and 1, and their original positions should now have 0
        Return value should be true
        """
        board = [[0, 0, 32, 16],
                 [0, 0, 16, 64],
                 [0, 0, 4, 2],
                 [0, 0, 8, 128]]
        expected_board = [[32, 16, 0, 0],
                          [16, 64, 0, 0],
                          [4, 2, 0, 0],
                          [8, 128, 0, 0]]
        bool = move_left(board)
        self.assertEqual(board, expected_board)
        self.assertTrue(bool)

    def test_move_left_merge(self):
        """
        Tests that the tiles that can be merged, adjacent neighbors with same value, are merged
        Return value should be true
        """
        board = [[2, 2, 8, 8],
                 [4, 4, 16, 16],
                 [32, 32, 128, 128],
                 [64, 64, 256, 256]]
        expected_board = [[4, 16, 0, 0],
                          [8, 32, 0, 0],
                          [64, 256, 0, 0],
                          [128, 512, 0, 0]]
        bool = move_left(board)
        self.assertEqual(board, expected_board)
        self.assertTrue(bool)

    def test_move_left_false(self):
        """
        Tests that the function returns false since no tiles can and were not moved
        """
        board = [[2, 4, 8, 16],
                 [16, 8, 4, 2],
                 [32, 64, 128, 256],
                 [256, 128, 64, 32]]
        expected_board = [[2, 4, 8, 16],
                          [16, 8, 4, 2],
                          [32, 64, 128, 256],
                          [256, 128, 64, 32]]
        bool = move_left(board)
        self.assertEqual(board, expected_board)
        self.assertFalse(bool)

    def test_move_right_from_left(self):
        """
        All the values from the leftmost two columns should fill columns 2 and 3, and their original positions should now have 0
        Return value should be true
        """
        board = [[32, 16, 0, 0],
                 [16, 64, 0, 0],
                 [4, 2, 0, 0],
                 [8, 128, 0, 0]]
        expected_board = [[0, 0, 32, 16],
                          [0, 0, 16, 64],
                          [0, 0, 4, 2],
                          [0, 0, 8, 128]]
        bool = move_right(board)
        self.assertEqual(board, expected_board)
        self.assertTrue(bool)

    def test_move_right_merge(self):
        """
        Tests that the tiles that can be merged, adjacent neighbors with same value, are merged
        Return value should be true
        """
        board = [[2, 2, 8, 8],
                 [4, 4, 16, 16],
                 [32, 32, 128, 128],
                 [64, 64, 256, 256]]
        expected_board = [[0, 0, 4, 16],
                          [0, 0, 8, 32],
                          [0, 0, 64, 256],
                          [0, 0, 128, 512]]
        bool = move_right(board)
        self.assertEqual(board, expected_board)
        self.assertTrue(bool)

    def test_move_left_right(self):
        """
        Tests that the function returns false since no tiles can and were not moved
        """
        board = [[2, 4, 8, 16],
                 [16, 8, 4, 2],
                 [32, 64, 128, 256],
                 [256, 128, 64, 32]]
        expected_board = [[2, 4, 8, 16],
                          [16, 8, 4, 2],
                          [32, 64, 128, 256],
                          [256, 128, 64, 32]]
        bool = move_right(board)
        self.assertEqual(board, expected_board)
        self.assertFalse(bool)


class IsGameOverTests(unittest.TestCase):

    def test_game_is_over(self):
        """
        Tests the true is returned since game is over, no more moves can be made
        :return:
        """
        board = [[2, 4, 8, 16],
                 [16, 8, 4, 2],
                 [32, 64, 128, 256],
                 [256, 128, 64, 32]]
        over, _, _ = is_game_over(board)
        self.assertTrue(over)

    def test_game_is_not_over(self):
        """
        Tests that false is returned since moves can still be made
        """
        board = [[32, 16, 16, 0],
                 [16, 64, 8, 4],
                 [4, 2, 2, 4],
                 [8, 128, 2, 256]]
        over, _, _ = is_game_over(board)
        self.assertFalse(over)

    def test_game_is_won(self):
        """
        Tests that true is returned since tile 2048 is present in board
        """
        board = [[2, 4, 8, 16],
                 [16, 8, 4, 2],
                 [32, 2048, 128, 256],
                 [256, 128, 64, 32]]
        _, won, _ = is_game_over(board)
        self.assertTrue(won)

    def test_game_is_not_won(self):
        """
        Tests that false is returned since tile 2048 is not present in board
        """
        board = [[2, 4, 8, 16],
                 [16, 8, 4, 2],
                 [32, 2, 128, 256],
                 [256, 128, 64, 32]]
        _, won, _ = is_game_over(board)
        self.assertFalse(won)

    def test_game_score(self):
        """
        Tests that the correct score is returned based on the sum of the tiles in board
        """
        expected_score = 3004
        board = [[2, 4, 8, 16],
                 [16, 8, 4, 2],
                 [32, 2048, 128, 256],
                 [256, 128, 64, 32]]
        _, _, score = is_game_over(board)
        self.assertEqual(expected_score, score)

    def test_game_complete(self):
        """
        Tests that the all 3 returns are correct; game_over, game_won, and score
        """
        expected_score = 3004
        board = [[2, 4, 8, 16],
                 [16, 8, 4, 2],
                 [32, 2048, 128, 256],
                 [256, 128, 64, 32]]
        over, won, score = is_game_over(board)
        self.assertTrue(over)
        self.assertTrue(won)
        self.assertEqual(expected_score, score)
