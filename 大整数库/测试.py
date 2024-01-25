import random

# a = random.randint(0,pow(10,300))
# b = random.randint(0,pow(10,300))
# print(f"{a} * {b} = {a * b}")

a = random.randint(1,pow(10,9))
print(a)

# p = 100000000000031
# q = 13
# e = 65537
# def ex_gcd(a,b):
#     """扩展欧几里德算法"""
#     if b == 0:
#         return 1, 0
#     else:
#         q = a // b
#         r = a % b
#         s, t = ex_gcd(b, r)
#         s, t = t, s-q*t
#     return [s, t]

# phi = (q - 1) * (p - 1)
# print(((ex_gcd(e,phi)[0]) % phi + phi) % phi)