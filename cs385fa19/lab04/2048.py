# -*- coding: utf-8 -*-

import curses
from curses import wrapper

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

EXIT_MESSAGE = "Do you want to exit (press 'y' to confirm)?"
END_MESSAGE = "Press 'q' to exit."
WON_MESSAGE = "Congratulations, you reached 2048!"
LOST_MESSAGE = "Shame on you, you lost!"

COLOR_PAIRS = {
    0: 0,
    2: 1,
    4: 2,
    8: 3,
    16: 4,
    32: 5,
    64: 6,
    128: 6,
    256: 6,
    512: 7,
    1024: 7,
    2048: 7,
}

BORDER_COLOR_PAIRS = {
    0: 0,
    2: 11,
    4: 12,
    8: 13,
    16: 14,
    32: 15,
    64: 16,
    128: 16,
    256: 16,
    512: 17,
    1024: 17,
    2048: 17,
}


def init_curses():
    curses.curs_set(0)
    curses.init_pair(1, curses.COLOR_BLACK, curses.COLOR_WHITE)
    curses.init_pair(2, curses.COLOR_BLACK, curses.COLOR_YELLOW)
    curses.init_pair(3, curses.COLOR_BLACK, curses.COLOR_BLUE)
    curses.init_pair(4, curses.COLOR_BLACK, curses.COLOR_GREEN)
    curses.init_pair(5, curses.COLOR_BLACK, curses.COLOR_CYAN)
    curses.init_pair(6, curses.COLOR_BLACK, curses.COLOR_MAGENTA)
    curses.init_pair(7, curses.COLOR_BLACK, curses.COLOR_RED)

    curses.init_pair(11, curses.COLOR_WHITE, curses.COLOR_WHITE)
    curses.init_pair(12, curses.COLOR_WHITE, curses.COLOR_YELLOW)
    curses.init_pair(13, curses.COLOR_WHITE, curses.COLOR_BLUE)
    curses.init_pair(14, curses.COLOR_WHITE, curses.COLOR_GREEN)
    curses.init_pair(15, curses.COLOR_WHITE, curses.COLOR_CYAN)
    curses.init_pair(16, curses.COLOR_WHITE, curses.COLOR_MAGENTA)
    curses.init_pair(17, curses.COLOR_WHITE, curses.COLOR_RED)


def paint_board(screen, board, offset_y, offset_x):
    y_position = offset_y
    for row in range(SIZE):
        x_position = offset_x
        for column in range(SIZE):
            paint_tile(screen, board[row][column], y_position, x_position)
            x_position += TILE_WIDTH
        y_position += TILE_HEIGHT


def paint_tile(screen, value, y, x):
    color = COLOR_PAIRS[value]
    border_color = BORDER_COLOR_PAIRS[value]
    screen.addstr(y, x, "▛▀▀▀▀▀▀▜", curses.color_pair(border_color))
    screen.addstr(y + 1, x, "▌      ▐", curses.color_pair(border_color))
    if value > 0:
        screen.addstr(y + 2, x, "▌", curses.color_pair(border_color))
        screen.addstr(y + 2, x + 1, "{:^6}".format(str(value)), curses.color_pair(color))
        screen.addstr(y + 2, x + 7, "▐", curses.color_pair(border_color))
    else:
        screen.addstr(y + 2, x, "▌      ▐", curses.color_pair(border_color))
    screen.addstr(y + 3, x, "▌      ▐", curses.color_pair(border_color))
    screen.addstr(y + 4, x, "▙▄▄▄▄▄▄▟", curses.color_pair(border_color))
    screen.refresh()


def main(stdscr):

    init_curses()

    # centering
    height, width = stdscr.getmaxyx()

    offset_x = int(width // 2) - int(BOARD_WIDTH/2)
    offset_y = int(height // 2) - int(BOARD_HEIGHT/2)

    message_y = offset_y + BOARD_HEIGHT + 1

    score_y = offset_y - 1

    exit_message_x = int(width // 2) - int(len(EXIT_MESSAGE) // 2)
    end_message_x = int(width // 2) - int(len(END_MESSAGE) // 2)
    won_message_x = int(width // 2) - int(len(WON_MESSAGE) // 2)
    lost_message_x = int(width // 2) - int(len(LOST_MESSAGE) // 2)

    board = initialize_board()
    paint_board(stdscr, board, offset_y, offset_x)

    while True:

        game_over, game_won, score = is_game_over(board)

        if game_won:
            stdscr.addstr(message_y, won_message_x, WON_MESSAGE)
            stdscr.addstr(message_y + 2, end_message_x, END_MESSAGE)
            while True:
                c = stdscr.getch()
                if c == ord('q'):
                    return

        if game_over:
            stdscr.addstr(message_y, lost_message_x, LOST_MESSAGE)
            stdscr.addstr(message_y + 2, end_message_x, END_MESSAGE)
            while True:
                c = stdscr.getch()
                if c == ord('q'):
                    return

        stdscr.addstr(score_y, offset_x, f"Current Score: {score}")

        c = stdscr.getch()
        moved_tiles = False

        if c == curses.KEY_UP:
            moved_tiles = move_up(board)
        elif c == curses.KEY_DOWN:
            moved_tiles = move_down(board)
        elif c == curses.KEY_LEFT:
            moved_tiles = move_left(board)
        elif c == curses.KEY_RIGHT:
            moved_tiles = move_right(board)
        elif c == ord('q'):
            stdscr.addstr(message_y, exit_message_x, EXIT_MESSAGE)
            if stdscr.getch() == ord('y'):
                return
            stdscr.addstr(message_y, exit_message_x, " " * len(EXIT_MESSAGE))

        if moved_tiles:
            add_random_tile(board)
            paint_board(stdscr, board, offset_y, offset_x)


if __name__ == '__main__':
    wrapper(main)
