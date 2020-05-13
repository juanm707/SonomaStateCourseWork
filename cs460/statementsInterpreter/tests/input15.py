c = 2
d = 3

v1 = []
v1_size = len(v1) # = 0
v1.push(2)
v1.push(777)
v1.pop()

v2 = [1, 3, 5,7,9]
v3 = [1 + 2, c + d, 5 - 3 * 2, 7, d + 9]
v4 = ["Data Structures", "Programming Languages", "Operating Systems"]
print v4
print v4[-3]
print v4[0] + " " + v4[1]
print v2[0] + 1000

b = [4, 5, 6]
a = 3 + 2
b[-3] = 5 + 5
b[1] = b[-2] + 10
z = b[0] + b[1] + b[2]

y = v4[d - c] + " and " + v4[d - 3]
print y

# size = not(-len(v2))
v2_size = len(v2)
v2_size_doubled = len(v2) * 2 # should = 10

v2.push(11)
v2_size_push = len(v2)

v2.pop()
v2_size_pop1 = len(v2)

v2.pop()
v2_size_pop2 = len(v2)
