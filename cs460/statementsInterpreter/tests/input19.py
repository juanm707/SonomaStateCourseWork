def rangeTest():
    return 10

for i in range(rangeTest()):
    print i

def printAdd(a, b):
    s = a + b
    print s
    return

def add(a, b):
    sum = a + b
    return sum

m = 3
def addAndMult(a, b):
    s = a + b
    ss = s * s
    print "s =", s, "ss =", ss
    def printAM():
        print m
    printAM()
    
addAndMult(5, 5)

j = add(1, 2) + 5
print j + add(5, 7)

zero = not(add(1,0))

if add(0,1):
    print "Func call is 1"
else:
    print "Func call is 0"
    

print add(1,2) + 5

printAdd(1, 2)

def sub(a, b):
    dif = a - b
    return

def dispAdd(a):
    b = 1
    print a + b

def popLast(arr):
    arr.pop()
    print arr

def sumArray(arr):
    sum = 0
    for i in range(len(arr)):
        sum = sum + arr[i]
    return sum


array1 = [1, 2, 3, 4, 5]
popLast(array1)
print array1

array2 = [10, 20, 30, 40, 50]
print "Sum of array:", array2, "+ 100 is =", sumArray(array2) + 100
# sumArray(array2)

x = 2
dispAdd(x)

#print "Not(add(23, 45)) =", not(add(23,45))




