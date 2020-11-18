from itertools import chain

size, obstacles = list(map(int, input().strip().split()))
queen_pos = list(map(int, input().strip().split()))

# Rip PEP8 lmao
closest8 = [
    [min(queen_pos[0], queen_pos[1]) - 1,        queen_pos[0] - 1,    min(queen_pos[0] - 1, size - queen_pos[1])],
    [queen_pos[1] - 1,                           0,                   size - queen_pos[1]],
    [min(size - queen_pos[0], queen_pos[1] - 1), size - queen_pos[0], min(size - queen_pos[0], size - queen_pos[1])]]

def closest8_index(board_row_delta, board_col_delta):
    row = 1 + (-1 if board_row_delta < 0 else int(bool(row_delta)))
    col = 1 + (-1 if board_col_delta < 0 else int(bool(col_delta)))
    return row, col

for _ in range(obstacles):
    obstacle = list(map(int, input().strip().split()))
    row_delta = obstacle[0] - queen_pos[0]
    col_delta = obstacle[1] - queen_pos[1]
    if abs(row_delta) == abs(col_delta) or 0 in (row_delta, col_delta):
        # Then it is in queen's line of fire
        row, col = closest8_index(row_delta, col_delta)
        closest8[row][col] = min(closest8[row][col], max(abs(row_delta), abs(col_delta))-1)

print(sum(chain(*closest8)))
