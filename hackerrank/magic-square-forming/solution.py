from itertools import chain

base = [[8, 3, 4], [1, 5, 9], [6, 7, 2]]

def diff(test, square):
    return sum(abs(i - j) for i, j in zip(chain(*test), chain(*square)))

squares = []
for i in range(4):
    squares.append(base)
    base = base[::-1]
    squares.append(base)
    base = [*zip(*base)]

test = [tuple(map(int, input().strip().split())) for _ in range(3)]

print(min(map(lambda sqr: diff(test, sqr), squares)))
