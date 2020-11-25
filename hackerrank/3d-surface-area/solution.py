h, w = map(int, input().split())
board = []
sa = 0
for row in range(h):
    board.append(list(map(int, input().strip().split())))
    for col in range(w):
        n = board[row][col]
        sa += n if row == 0 else abs(n - board[row - 1][col])
        sa += n if col == 0 else abs(n - board[row][col - 1])
        if row == h-1: sa += n
        if col == w-1: sa += n
        sa += 2
print(sa)
