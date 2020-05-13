print not(1 > 2)
j = 1
k = not j
shouldBeOne = not(0 or 0)
check = not(1-1)
print not(1-1)
check2 = not 1-1
print (not check2)
check3 = not(1) or not(1)

uno = 1
print(not(uno-uno))
print(not uno-uno)

one = 2
print(not(one))

print(not(2))
print(not 2)

m = not(1)
n = not 1
ww = not(m)

a = 0
b = 2
for i in range(2,10):
    a = a + 1
    b = b - 1

print "i:", i, " a:", a

shouldBeTrue = not a > 0 and b > 0 or a > b or b > a
print(not not not not not not not 1-1)
x = 0
y = 1
print x or y     # 1
print x and y    # 0
print x or not y # 0
