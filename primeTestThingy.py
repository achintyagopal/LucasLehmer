import string
import random
import cmath

# def isPrime(k):
#     for m in range(2, int(math.sqrt(k) + 1)):
#         if k % m == 0:
#             return False
#     return True

p = 4000
prime = (1 << p) - 1
# prime = 2 ** p - 1
a = 4
for j in range(2, p):
    a *= a
    # print(a)
    a -= 2
    # print(a)
    # print(a, prime)
    # a %= prime
    # print(a)
    # print

    b = a >> p
    a &= prime
    a += b
    b = a >> p
    # print(b)
    a &= prime
    # print(a)
    # if b != 0:
        # print(b)
    a += b

print(a in (0,prime))
