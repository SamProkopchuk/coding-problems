from collections import defaultdict, deque
from itertools import islice


def unwrap(matrix):
    res = defaultdict(deque)
    wrapper = 0
    while matrix:
        for _ in range(4):
            if not matrix:
                break
            res[wrapper] += matrix.pop()
            matrix = [*zip(*reversed(matrix))]
        wrapper += 1
    return res


def wrap(idx2wrapper, m, n):
    res = [[None] * n for _ in range(m)]
    for edgedist in [*idx2wrapper.keys()]:
        it = iter(idx2wrapper[edgedist])
        for _ in range(4):
            res[-1 - edgedist][edgedist:-edgedist-1] = list(islice(it, n - 2 * edgedist - 1))
            res = [list(r) for r in zip(*reversed(res))]
            m, n = n, m
    return res


m, n, r = map(int, input().split())
matrix = [tuple(map(int, input().split())) for _ in range(m)]

idx2wrapper = unwrap(matrix)
for iwrapper in idx2wrapper:
    idx2wrapper[iwrapper].rotate(r)
matrix = wrap(idx2wrapper, m, n)

for row in matrix:
    print(*row)
