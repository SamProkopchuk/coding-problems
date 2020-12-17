from itertools import chain

for _ in range(int(input())):
    n, k = map(int, input().split())
    if not k:
        print(*range(1, n+1))
    elif n % (2 * k):
        print(-1)
    else:
        s1 = (range(i + k + 1, i + 2 * k + 1) for i in range(0, n, 2 * k))
        s2 = (range(i + 1, i + k + 1) for i in range(0, n, 2 * k))
        print(*chain.from_iterable(chain.from_iterable(zip(s1, s2))))
