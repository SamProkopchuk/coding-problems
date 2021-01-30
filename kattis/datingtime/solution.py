def is_valid(h, m):
    return 0 <= h < 24 and 0 <= m < 60


def t_lt(h1, m1, h2, m2):
    return h1 < h2 or (h1 == h2 and m1 <= m2)


for _ in range(int(input())):
    t1, t2, a = input().split()
    h1, m1 = map(int, t1.split(':'))
    h2, m2 = map(int, t2.split(':'))
    a = int(a)

    count = 0
    for h in range(h1, h2 + 1):
        if a == 0:
            m = (h % 12) * 60 / 11
            if is_valid(h, m) and t_lt(h1, m1, h, m) and t_lt(h, m, h2, m2):
                count += 1
        elif a == 90:
            m = ((h + 3) % 12) * 60 / 11
            if is_valid(h, m) and t_lt(h1, m1, h, m) and t_lt(h, m, h2, m2):
                count += 1
            m = ((h - 3) % 12) * 60 / 11
            if is_valid(h, m) and t_lt(h1, m1, h, m) and t_lt(h, m, h2, m2):
                count += 1
        elif a == 180:
            m = ((h + 6) % 12) * 60 / 11
            if is_valid(h, m) and t_lt(h1, m1, h, m) and t_lt(h, m, h2, m2):
                count += 1
    print(count)
