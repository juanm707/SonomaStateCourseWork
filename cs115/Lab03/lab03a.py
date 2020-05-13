"""
Program: CS 115 Lab 3a
Author: Juan Martinez
Description: This program adds up the numbers from 1 to 5.
"""


def main():
    total = 0

    for i in range(5):

        num = int(input("Enter an integer: "))

        total = total + num

    print('The total is:', total)

    mean = total/5

    print("The mean is:", mean)



main()
