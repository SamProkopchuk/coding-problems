from itertools import chain, product
from copy import deepcopy


def stoa(size):
    if size == 0:
        return 0
    return 4 * size - 3


def largest_plus(matrix, row, col, roff=0, coff=0, dr=0, dc=0):
    if matrix[row][col] == 0:
        return 0
    elif dr:
        if not (0 <= row+roff < len(matrix)) or matrix[row+roff][col+coff] == 0:
            return abs(roff)
        return largest_plus(matrix, row, col, roff + dr, coff, dr, dc)
    elif dc:
        if not (0 <= col+coff < len(matrix[0])) or matrix[row+roff][col+coff] == 0:
            return abs(coff)
        return largest_plus(matrix, row, col, roff, coff + dc, dr, dc)
    directions = set()
    for dr_ in (-1, 1):
        directions.add(largest_plus(matrix, row, col, dr_, dc, dr_, dc))
    for dc_ in (-1, 1):
        directions.add(largest_plus(matrix, row, col, dr, dc_, dr, dc_))
    return min(directions)


def zero_out(matrix, row, col, dist, dr=0, dc=0):
    if dist == 0:
        return
    elif dr == dc == 0:
        matrix[row][col] = 0
        for dr_ in (-1, 1):
            zero_out(matrix, row + dr_, col, dist-1, dr_, dc)
        for dc_ in (-1, 1):
            zero_out(matrix, row, col + dc_, dist-1, dr, dc_)
    else:
        matrix[row][col] = 0
        zero_out(matrix, row+dr, col+dc, dist-1, dr, dc)


def largest_bybase(lps, row, col):
    largest = 0
    temp = deepcopy(lps)
    for size in range(1, lps[row][col] + 1):
        zero_out(temp, row, col, size)
        tlps = [[largest_plus(temp, r, c) for c in range(m)] for r in range(n)]
        largest = max(largest, stoa(size) * stoa(max(chain.from_iterable(tlps))))
    return largest


n, m = map(int, input().split())
matrix = [[0 if c == 'B' else 1 for c in input().strip()] for r in range(n)]
lps = [[largest_plus(matrix, r, c) for c in range(m)] for r in range(n)]
bybase = [largest_bybase(lps, r, c) for r, c in product(range(n), range(m))]
print(max(bybase))
