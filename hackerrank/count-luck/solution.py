from itertools import product

n, m = 0, 0


def isValid(r, c):
    return 0 <= r < n and 0 <= c < m


def dfs(grid, r, c):
    if grid[r][c] == '*':
        return 0
    grid[r][c] = 'X'
    options = 0
    res = -1
    for dr, dc in product(range(-1, 2), range(-1, 2)):
        if (dr != 0) ^ (dc != 0) and isValid(r + dr,
                                             c + dc) and grid[r + dr][c + dc] != 'X':
            options += 1
            res = max(res, dfs(grid, r + dr, c + dc))
    if res == -1:
        return res
    return res + 1 if options > 1 else res


for _ in range(int(input())):
    n, m = map(int, input().split())
    grid = [[*input()] for _ in range(n)]
    k = int(input())
    for r, c in product(range(n), range(m)):
        if grid[r][c] == 'M':
            ans = dfs(grid, r, c)
            break
    print('Impressed' if k == ans else 'Oops!')
