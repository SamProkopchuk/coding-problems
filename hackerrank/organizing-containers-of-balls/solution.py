from collections import Counter
for _ in range(int(input().strip())):
    matrix = [list(map(int, input().strip().split())) for _ in range(int(input().strip()))]
    rowsums = Counter(sum(row) for row in matrix)
    colsums = Counter(sum(col) for col in zip(*matrix))
    print('Possible' if rowsums == colsums else 'Impossible')
