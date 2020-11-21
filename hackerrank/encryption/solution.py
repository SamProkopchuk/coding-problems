from math import floor, ceil, sqrt

s = input().strip().replace(' ', '')
n = sqrt(len(s))
rows = floor(n)
cols = ceil(n)
res = [''] * cols
for col in range(cols):
    row_vec = s[col * cols: (col + 1) * cols]
    for idx in range(len(row_vec)):
        res[idx] += row_vec[idx]

print(' '.join(res))
