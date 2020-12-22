from itertools import product

h, w = map(int, input().split())
board = [list(map(int, input().strip().split())) for _ in range(h)]
sa = 2 * h * w
for row, col in product(range(h), range(w)):
    n = board[row][col]
    sa += n if row == 0 else abs(n - board[row - 1][col])
    sa += n if col == 0 else abs(n - board[row][col - 1])
    if row == h - 1: sa += n
    if col == w - 1: sa += n
print(sa)
