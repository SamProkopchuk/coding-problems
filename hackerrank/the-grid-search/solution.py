from itertools import product


def match(matrix, pattern, r, c):
    for ridx, r_ in enumerate(matrix[r: r + len(pattern)]):
        if r_[c: c + len(pattern[0])] != pattern[ridx]:
            return False
    return True


for _ in range(int(input())):
    mr, mc = map(int, input().split())
    matrix = [[int(c) for c in input().strip()] for _ in range(mr)]
    pr, pc = map(int, input().split())
    pattern = [[int(c) for c in input().strip()] for _ in range(pr)]
    for r, c in product(range(mr - pr + 1), range(mc - pc + 1)):
        if [r_[c: c + pc] for r_ in matrix[r: r + pr]] == pattern:
            print('YES')
            break
    else:
        print('NO')
