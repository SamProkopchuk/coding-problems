from heapq import merge

n, k = map(int, input().split())
entrs, exits = zip(*[map(int, input().split()) for _ in range(n)])
entrs, exits = sorted(entrs), sorted(exits)
entrs = ((e, True) for e in entrs)
exits = ((e + k + 1, False) for e in exits)
ppl = merge(entrs, exits)
cur = most = 0
for t, e in ppl:
    if e:
        cur += 1
    else:
        cur -= 1
    most = max(most, cur)
print(most)
