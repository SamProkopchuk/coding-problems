MOD = 1_000_000_000 + 7

for _ in range(int(input())):
    a, b = map(int, input().split())
    b = b % (MOD - 1)
    r = 1
    while b > 1:
        if b % 2 == 1:
            r = (r * a) % MOD
        a = a**2 % MOD
        b //= 2
    print((a * r) % MOD)
