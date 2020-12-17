from itertools import product

def calcmatrix(matrix, time):
    if time < 2:
        return ['O'*len(matrix[0]) for _ in range(len(matrix))] if time else matrix
    res = [list(row) for row in matrix]
    for row, col in product(range(r), range(c)):
        if matrix[row][col] == 'O':
            res[row][min(col+1, c-1)] = res[row][max(col-1, 0)] = res[min(row+1, r-1)][col] = res[max(row-1, 0)][col] = 'O'
    res = (map(lambda v: '.' if v == 'O' else 'O', row) for row in res)
    res = [''.join(m) for m in res]
    return calcmatrix(res, (time - 2) % 4)

r, c, n = map(int, input().split())
matrix = [input().strip() for _ in range(r)]
res = calcmatrix(matrix, n-1)
print(*res, sep='\n')
