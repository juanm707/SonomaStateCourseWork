"""
Program: CS 115 Lab 3c
Author: Juan Martinez
Description: Using the graphics package, this program will draw
    a number of circles.
"""
from graphics import *


def main():
    window = GraphWin("Circles", 800, 800)

    # Circle 1
    radius = 50
    x = 100
    y = 200
    center = Point(x, y)
    circle = Circle(center, radius)
    circle.setOutline('blue')
    circle.draw(window)

    # Circle 2
    radius = 50
    x = 100
    y = 300
    center = Point(x, y)
    circle = Circle(center, radius)
    circle.setOutline('blue')
    circle.draw(window)

    # Circle 3
    radius = 50
    x = 100
    y = 400
    center = Point(x, y)
    circle = Circle(center, radius)
    circle.setOutline('blue')
    circle.draw(window)

    # Circle 4
    radius = 50
    x = 100
    y = 500
    center = Point(x, y)
    circle = Circle(center, radius)
    circle.setOutline('blue')
    circle.draw(window)

    # Circle 5
    radius = 50
    x = 100
    y = 600
    center = Point(x, y)
    circle = Circle(center, radius)
    circle.setOutline('blue')
    circle.draw(window)

    window.getMouse()  # wait for the mouse to be clicked in the window.
    window.close()     # close the window after the mouse is clicked in the window.


main()