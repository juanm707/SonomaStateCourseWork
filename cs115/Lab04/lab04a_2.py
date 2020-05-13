"""
    Program: CS 115 Lab 4a_2
    Author: Juan Martinez
    Description: This program draws a few rectangles and fills them.
"""
from graphics import *


def main():
    window = GraphWin('Lab 4a_2', 400, 600)

    palette_top_left_x = 10
    palette_top_left_y = 20
    width = 60
    height = 60
    yellow_top_left = Point(palette_top_left_x, palette_top_left_y)
    yellow_bottom_right = Point(palette_top_left_x + width, palette_top_left_y + height)
    yellow_rectangle = Rectangle(yellow_top_left, yellow_bottom_right)
    yellow_rectangle.setFill('yellow')
    yellow_rectangle.draw(window)

    pinkrectL = Point(70,20)
    pinkrectR = Point(130,80)
    pinkrect = Rectangle(pinkrectL,pinkrectR)
    pinkrect.setFill("pink")
    pinkrect.draw(window)

    bluerectL = Point(130, 20)
    bluerectR = Point(190, 80)
    bluerect = Rectangle(bluerectL, bluerectR)
    bluerect.setFill("blue")
    bluerect.draw(window)

    for i in range(5):
        c_point = window.getMouse()
        x_c_point = c_point.getX()
        y_c_point = c_point.getY()
        if (yellow_top_left.getX() <= x_c_point <= yellow_bottom_right.getX() and
           yellow_top_left.getY() <= y_c_point <= yellow_bottom_right.getY()):
            print('The click with x =', c_point.getX(), 'and y =',
                  c_point.getY(), 'is in the yellow square.')

        elif 70 <= x_c_point <= 130 and 20 <= y_c_point <= 80:
            print('The click with x =',x_c_point,'and y =',y_c_point,'is in the pink square.')

        elif 130 <= x_c_point <= 190 and 20 <= y_c_point <= 80:
            print('The click with x =',x_c_point,'and y =',y_c_point,'is in the blue square.')

        else:
            print('The click with x =', c_point.getX(), 'and y =',
                  c_point.getY(), 'is not in any of the squares.')

    window.getMouse()
    window.close()

main()