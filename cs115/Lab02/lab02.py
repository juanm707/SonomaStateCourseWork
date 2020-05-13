"""
Program: CS 115 Lab 2
Author: Juan Martinez
Description: This program will compute the area of a square,
the area of a circle, the volume of a cube, the volume of a sphere,
and the area of an equilateral triangle given the side length.
"""

import math

def main():

    # Get the side length
    length = float(input('Enter a numeric value: '))

    # Compute the area of the square
    square_area = length * length

    # Compute the area of the circle
    circle_area = math.pi * length ** 2

    # Compute the volume of the cube
    cube_volume = length ** 3

    # Compute the volume of the sphere
    sphere_volume = 4/3 * math.pi * length ** 3

    # Compute the area of an equilateral triangle
    triangle_area = length ** 2 * (math.sqrt(3)/4)

    print("The area of a square with side length ", length,
          " is ", square_area, ".", sep="")

    print("The area of a circle with radius length ", length,
          " is ", circle_area, ".", sep="")

    print("The volume of a cube with edge length ", length,
          " is ", cube_volume, ".", sep="")

    print("The volume of a sphere with radius length ", length,
          " is ", sphere_volume, ".", sep="")

    print("The area of an equilateral triangle with side length ", length,
          " is ", triangle_area, ".", sep="")

main()
