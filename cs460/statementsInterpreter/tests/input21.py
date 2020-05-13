a = 98
def addOne(x):
    b = x + 1
    def multThree(x):
        c = x * 3
        return a
    return multThree(b)

w = addOne(55)
print(w)
