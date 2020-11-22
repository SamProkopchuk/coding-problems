from sys import stdin, stdout

def val(x, y, n):
    if n & 1: return 1
    n >>= 1
    if x >= n:
        if y >= n:
            return - val(x-n, y-n, n)
        return val(x-n, y, n)
    elif y >= n:
        return val(x, y-n, n)
    return val(x, y, n)

for _ in range(int(input().strip())):
    n, c, r, w, h = map(int, stdin.readline().strip().split())
    res = [[0 for _w in range(w)] for _h in range(h)]
    for rd in range(h):
        for cd in range(w):
            res[rd][cd] = val(r + rd, c + cd, n)
    for row in res:
        print(*row)
