n, k = map(int, input().split())
s = set(map(int, input().split()))
print(sum(1 for x in s if k + x in s))
