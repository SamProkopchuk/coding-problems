'''RUN USING Pypy 3 TO AVOID TLE'''

from itertools import chain

A = 26
MOD = 1_000_000_007
c1 = [0] * A
c2 = [[0] * A for _ in range(A)]
c3 = [[[0] * A for _ in range(A)] for __ in range(A)]
c4 = [[[[0] * A for _ in range(A)] for __ in range(A)] for ___ in range(A)]

s = input()
for c in s:
    i = ord(c) - ord('a')
    for l in range(A):
        c4[i][l][l][i] = (c4[i][l][l][i] + c3[i][l][l]) % MOD
        c3[l][i][i] = (c2[l][i] + c3[l][i][i]) % MOD
        c2[l][i] = (c2[l][i] + c1[l]) % MOD
    c1[i] += 1

print(sum(sum(chain(*x)) for x in chain(*c4)) % MOD)
