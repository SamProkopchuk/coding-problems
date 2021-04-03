for _ in range(int(input())):
    n = int(input())
    rounds = 0
    minidx = 1_000_000_000
    for _, idx in sorted(zip(map(int, input().split()), range(n)), reverse=True):
        if idx < minidx:
            minidx = idx
            rounds += 1
    print("BOB" if rounds % 2 else "ANDY")
