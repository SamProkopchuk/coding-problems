from copy import deepcopy
from itertools import product


def stoa(size):
    if size == 0:
        return 0
    return 4 * size - 3


def valid_idx(matrix, row, col):
    return 0 <= row < len(matrix) and 0 <= col < len(matrix[row])


def largest_plus(matrix, row, col, roff=0, coff=0, dr=0, dc=0):
    if matrix[row][col] == 0:
        return 0
    elif dr or dc:
        if (not valid_idx(matrix, row + roff, col + coff) or
                matrix[row + roff][col + coff] == 0):
            return abs(roff + coff)  # One of them should be zero.
        return largest_plus(matrix, row, col, roff + dr, coff + dc, dr, dc)
    else:
        directions = set()
        for delta in (-1, 1):
            directions.add(largest_plus(matrix, row, col, delta, 0, delta, 0))
            directions.add(largest_plus(matrix, row, col, 0, delta, 0, delta))
        return min(directions)


def zero_out(matrix, row, col, dist, dr=0, dc=0):
    if dist == 0:
        return
    elif dr == dc == 0:
        matrix[row][col] = 0
        for delta in (-1, 1):
            zero_out(matrix, row + delta, col, dist - 1, delta, 0)
            zero_out(matrix, row, col + delta, dist - 1, 0, delta)
    else:
        matrix[row][col] = 0
        zero_out(matrix, row + dr, col + dc, dist - 1, dr, dc)


def largest_bybase(lps, row, col):
    largest = 0
    temp = deepcopy(lps)
    for size in range(1, lps[row][col] + 1):
        zero_out(temp, row, col, size)
        tlp = max(largest_plus(temp, r, c)
                  for r, c in product(range(len(temp)), range(len(temp[0]))))
        largest = max(largest, stoa(size) * stoa(tlp))
    return largest


n, m = map(int, input().split())
matrix = [[0 if c == 'B' else 1 for c in input().strip()] for r in range(n)]
lps = [[largest_plus(matrix, r, c) for c in range(m)] for r in range(n)]
bybase = [largest_bybase(lps, r, c) for r, c in product(range(n), range(m))]
print(max(bybase))
