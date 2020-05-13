#!/usr/bin/env python3

def find_minimum(numbers):
    """
    Finds the minimum of a list 
    Does the same what the `min()` built in does, but of course, less efficiently, and buggy.
    """
    minimum = numbers[0]
    for number in numbers:
        if number < minimum:
            minimum = number

    return minimum



if __name__ == '__main__':

    n = int(input())
    numbers = [int(input()) for _ in range(n)]
    assert n == len(numbers)
    print(find_minimum(numbers))
