from collections import Counter
_, rem = map(int, input().strip().split())
remcount = Counter(i % rem for i in map(int, input().strip().split()))
res = min(remcount[0], 1) + (rem % 2 == 0 and min(remcount[rem // 2], 1))
res += sum(max(remcount[c], remcount[rem-c]) for c in range(1, (rem+1) // 2))
print(res)
