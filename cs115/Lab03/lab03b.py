"""
Program: CS 115 Lab 3b
Author: Juan Martinez
Description: Using the graphics package, this program will draw a circle.
"""
from graphics import *


def main():
    window = GraphWin("Circles", 800, 800)

    center = Point(100, 200)         # create a point to serve as the center of the circle
    radius = 40
    circle = Circle(center, radius)  # create a circle centered at "center" with radius "radius"
    circle.setOutline('blue')
    circle.draw(window)              # draw the circle in the window that we created earlier

    center = Point(100, 280)  # create a point to serve as the center of the circle
    radius = 40
    circle = Circle(center, radius)  # create a circle centered at "center" with radius "radius"
    circle.setOutline('red')
    circle.draw(window)  # draw the circle in the window that we created earlier

    center = Point(100, 360)  # create a point to serve as the center of the circle
    radius = 40
    circle = Circle(center, radius)  # create a circle centered at "center" with radius "radius"
    circle.setOutline('green')
    circle.draw(window)  # draw the circle in the window that we created earlier

    center = Point(100, 440)  # create a point to serve as the center of the circle
    radius = 40
    circle = Circle(center, radius)  # create a circle centered at "center" with radius "radius"
    circle.setOutline('yellow')
    circle.draw(window)  # draw the circle in the window that we created earlier

    center = Point(100, 520)  # create a point to serve as the center of the circle
    radius = 40
    circle = Circle(center, radius)  # create a circle centered at "center" with radius "radius"
    circle.setOutline('pink')
    circle.draw(window)  # draw the circle in the window that we created earlier

    window.getMouse()                # wait for the mouse to be clicked in the window
    window.close()                   # close the window after the mouse is clicked in the window


main()