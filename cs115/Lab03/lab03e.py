"""
Program: CS 115 Lab 3 Part E
Author: Juan Martinez
Description: Using the graphics package, this program will draw
a square of circles with diagonal circles crossing each other inside.
"""
from graphics import *


def main():
    window = GraphWin("Circles", 800, 800)

    num_circles = int(input("Enter a number for amount of circles: "))
    radius = int(input("Enter a radius: "))

    # 2. Draw the left vertical circles.

    x = 5 + radius
    y = 5 + radius
    for i in range(num_circles):

        center = Point(x, y)
        circle = Circle(center, radius)
        circle.setOutline('red')
        circle.draw(window)

        y = y + radius * 2

    bottom = y

    # 3. Draw the top horizontal circles.

    y = 5 + radius
    for i in range(num_circles):

        center = Point(x, y)
        circle = Circle(center, radius)
        circle.setOutline('red')
        circle.draw(window)

        x = x + radius * 2

    topright = x - radius * 2

    # 4. Draw the bottom horizontal circles.

    x = 5 + radius
    y = bottom - radius * 2
    for i in range(num_circles):

        center = Point(x, y)
        circle = Circle(center, radius)
        circle.setOutline('red')
        circle.draw(window)

        x = x + radius * 2

    # 5. Draw the right vertical circles.

    x = topright
    y = 5 + radius
    for i in range(num_circles):
        center = Point(x, y)
        circle = Circle(center, radius)
        circle.setOutline('red')
        circle.draw(window)

        y = y + radius * 2

    # 6. Draw the top-left-to-bottom-right diagonal circles.

    x = 5 + radius
    y = 5 + radius
    for i in range(num_circles):
        center = Point(x, y)
        circle = Circle(center, radius)
        circle.setOutline('blue')
        circle.draw(window)
        x = x + radius * 2
        y = y + radius * 2

    # 7. Draw the top-right-to-bottom-left diagonal circles.

    x = topright
    y = 5 + radius
    for i in range(num_circles):
        center = Point(x, y)
        circle = Circle(center, radius)
        circle.setOutline('blue')
        circle.draw(window)
        x = x - radius * 2
        y = y + radius * 2

    window.getMouse()
    window.close()


main()