for _ in range(int(input())):
    input()
    cubes = map(int, input().strip().split())
    last = cube = float('inf')
    while cube and last >= cube:
        last, cube = cube, next(cubes, 0)
    while cube and last <= cube:
        last, cube = cube, next(cubes, 0)
    print('No' if cube else 'Yes')
