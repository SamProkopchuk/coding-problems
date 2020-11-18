from itertools import chain

size, obstacles = list(map(int, input().strip().split()))
queen_pos = list(map(int, input().strip().split()))

# Rip PEP8 lmao
closest8 = [
    [min(queen_pos[0], queen_pos[1]) - 1,        queen_pos[0] - 1,    min(queen_pos[0] - 1, size - queen_pos[0])],
    [queen_pos[1] - 1,                           0,                   size - queen_pos[1]],
    [min(size - queen_pos[0], queen_pos[1] - 1), size - queen_pos[0], min(size - queen_pos[0], size - queen_pos[0])]]

def closest8_coord(x_delta, y_delta):
    row = -1 if x_delta > 0 else int(bool(x))
    col = -1 if y_delta > 0 else int(bool(y))
    row += 1
    col += 1
    return row, col

for _ in range(obstacles):
    obstacle = list(map(int, input().strip().split()))
    x = obstacle[0] - queen_pos[0]
    y = obstacle[1] - queen_pos[1]
    if abs(x) == abs(y):
        # Then it is in queens line of fire
        row, col = closest8_coord(x, y)
        closest8[row][col] = min(closest8[row][col], abs(x)-1)

print(sum(chain(*closest8)))
