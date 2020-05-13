a = 25
def addOne(x):
    b = x + 1
    def multThree(x):
        c = x * 3
        print(a)
    multThree(b)

addOne(55)
