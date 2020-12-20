from itertools import chain


def diff(test, square):
    return sum(abs(i - j) for i, j in zip(chain(*test), chain(*square)))

base = [[8, 3, 4], [1, 5, 9], [6, 7, 2]]
squares = []
for _ in range(4):
    squares.append(base)
    base = base[::-1]
    squares.append(base)
    base = [*zip(*base)]

test = [tuple(map(int, input().strip().split())) for _ in range(3)]

print(min(diff(test, sqr) for sqr in squares))
