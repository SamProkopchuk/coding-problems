from math import floor, ceil, sqrt

s = input().strip().replace(' ', '')
n = sqrt(len(s))
rows = floor(n)
cols = ceil(n)
res = [''] * cols
for col in range(cols):
    col_vec = s[col * cols: (col + 1) * cols]
    for idx, c in enumerate(col_vec):
        res[idx] += c

print(' '.join(res))
