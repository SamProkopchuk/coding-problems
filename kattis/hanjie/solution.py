r, c = map(int, input().split())
rclues = [[*map(int, input().split())] for _ in range(r)]
cclues = [[*map(int, input().split())] for _ in range(c)]
rclues = [rclue[1:] for rclue in rclues]
cclues = [cclue[1:] for cclue in cclues]

grid = [[0] * c for _ in range(r)]
count = 0


def is_partial(clue, row_or_col):
    consec = 0
    cur = []
    for x in row_or_col:
        if x == 1:
            consec += 1
        elif consec > 0:
            cur.append(consec)
            consec = 0
    if x == 1:
        cur.append(consec)
    return len(cur) <= len(clue) and all(i <= j for i, j in zip(cur, clue))


def is_rc_solved(clue, row_or_col):
    consec = 0
    cur = []
    for x in row_or_col:
        if x == 1:
            consec += 1
        elif consec > 0:
            cur.append(consec)
            consec = 0
    if x == 1:
        cur.append(consec)
    return cur == clue


def is_solved():
    for ir in range(r):
        row = grid[ir]
        clue = rclues[ir]
        if not is_rc_solved(clue, row):
            return False
    for ic in range(c):
        col = [row[ic] for row in grid]
        clue = cclues[ic]
        if not is_rc_solved(clue, col):
            return False
    return True


def calc_solutions(irow=0, icol=0):
    if irow == len(grid):
        if is_solved():
            global count
            count += 1
    else:
        for i in range(1, -1, -1):
            grid[irow][icol] = i
            if (is_partial(rclues[irow], grid[irow]) and
                    is_partial(cclues[icol], [row[icol] for row in grid])):
                if icol + 1 == len(grid[0]):
                    if is_rc_solved(rclues[irow], grid[irow]):
                        calc_solutions(irow + 1)
                else:
                    calc_solutions(irow, icol + 1)


calc_solutions()
print(count)
