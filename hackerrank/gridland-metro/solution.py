from collections import defaultdict

d = defaultdict(list)
n, m, k = map(int, input().split())
res = n * m
for _ in range(k):
    r, c1, c2 = map(int, input().split())
    d[r].append((c1, c2))

for r in d:
    d[r].sort()
    s = d[r][0][0]
    e = d[r][0][1]
    for (c1, c2) in d[r]:
        if c1 > e:
            res -= e-s + 1
            s = c1
        e = max(e, c2)
    res -= e-s + 1

print(res)
