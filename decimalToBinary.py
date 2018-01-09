# i = 3
# a = 1
# for _ in range(0,3):
#     a *= a
#     a *= i

a = ((4*4-2)**2 - 2)

b = []
while a != 0:
    # b *= 10
    # b += (a % 2)
    b.append(a%2)

    a /= 2

b.reverse()
print(b)