from collections import defaultdict

n, r = map(int, input().split())
nums = [*map(int, input().split())]
seen, jks = defaultdict(int), defaultdict(int)
res = 0
for x in reversed(nums):
	if r * x in jks:
		res += jks[r * x]
	if r * x in seen:
		jks[x] += seen[r * x]
	seen[x] += 1
print(res)
