for _ in range(int(input())):
    n, e = map(int, input().split())
    conn = [[-1] * n for _ in range(n)]
    for _ in range(e):
        x, y, r = map(int, input().split())
        x, y = x-1, y-1
        conn[x][y] = conn[y][x] = r if conn[x][y] == -1 else min(conn[x][y], r)
    s = int(input()) - 1
    visited = {s}
    shortests = conn[s].copy()
    while (m := min(((r, n) for n, r in enumerate(shortests) if r != -1 and n not in visited), default=None)) is not None:
        mr, mn = m
        for n, r in enumerate(conn[mn]):
            if r != -1:
                shortests[n] = mr + r if shortests[n] == -1 else min(shortests[n], mr + r)
        visited.add(mn)
    shortests.pop(s)
    print(*shortests)
