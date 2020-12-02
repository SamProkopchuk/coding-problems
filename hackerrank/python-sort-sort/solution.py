n, m = map(int, input().strip().split())
matrix = [list(map(int, input().strip().split())) for _ in range(n)]
k = int(input().strip())
for lst in sorted(matrix, key=lambda l: l[k]):
    print(*lst)
