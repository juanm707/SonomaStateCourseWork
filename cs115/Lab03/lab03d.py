"""
Program: CS 115 Lab 3 Part D
Author: Juan Martinez
Description: Using the graphics package, this program will draw a number of
             circles using a for-loop.
"""
from graphics import *


def main():
    window = GraphWin("Circles", 800, 800)

    x = 100
    y = 100
    num_circles = int(input("Enter a number of for amount of circles: "))
    radius = int(input("Enter a radius: "))
    for i in range(num_circles):
        print('x =', x, 'and y =', y)

        center = Point(x, y) # copy and paste a code-segment that draws one circle from your
        circle = Circle(center, radius) # previous program here.
        circle.setOutline('blue')
        circle.draw(window)

        y = y + radius*2 # copy the line that modifies y-value from Python tutor here

    window.getMouse()
    window.close()


main()