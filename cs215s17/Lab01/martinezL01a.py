"""
Assignment: Lab01a
File: martinezL01a.py
Author: Juan Martinez
Date: Spring 2017
Description: This program reads 10 integers, finds the sum and the average
of the integers, and sorts the integers into ascending order.
"""

def main():

    num_list = []
    total = 0
    avg = 0

    print("Please enter 10 integer values.\nEach value should be entered on a separate line:")

    for i in range(10):

        num = int(input(''))
        num_list.append(num)
        total += num

    avg = total / len(num_list)

    print("The values you entered are:")
    print(num_list)
    print("The total of your values is:", total)
    print("The average of your values is:", avg)
    print("The sorted values are:")

    num_list.sort()

    print(num_list)

main()