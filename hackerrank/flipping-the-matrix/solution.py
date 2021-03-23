from itertools import product

for _ in range(int(input())):
    n = int(input())
    matrix = [[*map(int, input().split())] for _ in range(2 * n)]
    print(sum(max(matrix[i][j],
                  matrix[2 * n - i - 1][j],
                  matrix[i][2 * n - j - 1],
                  matrix[2 * n - i - 1][2 * n - j - 1]) for i, j in product(range(n), range(n))))
