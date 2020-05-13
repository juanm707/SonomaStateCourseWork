"""
    Program: CS 115 Lab 4c
    Author: Juan Martinez
    Description: This program draws a few squares the user picks and fills them,
    and also calculates the location of user's mouse click.

"""

from graphics import *
from random import seed, randint
from time import clock


def random_color():
    # Don't worry about the internal details of this function.
    colors = ['blue', 'blue2', 'blue3',
              'green', 'green2', 'green3',
              'orange', 'orange2', 'orange3',
              'red', 'red2', 'red3',
              'purple', 'purple2', 'purple3',
              'yellow', 'yellow2', 'yellow3',
              'gray', 'gray2', 'gray3',
              'pink', 'pink1', 'pink2', 'pink3']

    return colors[randint(0, len(colors)-1)]


def main():
    seed()  # Initialize random number generator

    top_left_x = 100
    top_left_y = 100
    width = 60
    height = 60
    num_rows = int(input('Number of rows: '))
    num_columns = int(input('Number of columns: '))

    print()

    window = GraphWin('Lab 4B', 800, 800)
    top_left_point = Point(top_left_x, top_left_y)
    bottom_right_point = Point(top_left_x + width, top_left_y + height)
    enclosing_rectangle = Rectangle(top_left_point, bottom_right_point)
    enclosing_rectangle.setFill(random_color())
    enclosing_rectangle.draw(window)

    for r in range(num_rows):

        # Sets coordinates for starting row square
        toprow_x = top_left_x
        toprow_y = top_left_y + r * height

        bottomrow_x = top_left_x + width
        bottomrow_y = top_left_y + r * height

        for c in range(num_columns):

            # Squares for column starts at row square
            top_x = toprow_x + c * width
            top_y = toprow_y

            bottom_x = bottomrow_x + c * width
            bottom_y = bottomrow_y + height

            square = Rectangle(Point(top_x,top_y),Point(bottom_x,bottom_y))
            square.setFill(random_color())
            square.draw(window)

    # Coordinates of grid; bottom right square
    top_x = top_x + width
    bottomrow_y = bottomrow_y + height

    for i in range(10):

        c_point = window.getMouse()
        x_c_point = int(c_point.getX())
        y_c_point = int(c_point.getY())

        row = (y_c_point - top_left_y) // height + 1
        column = (x_c_point - top_left_x) // width + 1

        # Sees if clicked points are inside the grid
        if x_c_point < top_left_x or x_c_point > top_x or y_c_point < top_left_y or y_c_point > bottomrow_y:
            print("The click at", (x_c_point, y_c_point), "is outside the grid.")

        else:
            print("The click at ", (x_c_point, y_c_point), " is in row ", row, " column ", column, ".", sep="")

    window.getMouse()
    window.close()

main()