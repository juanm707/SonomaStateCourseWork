n = 1
print not n
a = 5
b = 0
print a or b        # 1
print a and b       # 0
print not 1 or b    # 0
x = not a or b
print not (a or b)  # 0
print a and not b   # 1
print a and (not b) # 1
print(-a or b)      # 1
