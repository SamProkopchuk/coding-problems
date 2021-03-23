from collections import Counter

n = int(input())
s = input()
chars = ('G', 'C', 'A', 'T')
cc = Counter(s)
if all(cc[c] == n // 4 for c in chars):
    best = 0
else:
    best = 1_000_000
    i = 0
    for j in range(n):
        cc[s[j]] -= 1
        if all(cc[c] <= n // 4 for c in chars):
            for i in range(i, j):
                if cc[s[i]] == n // 4:
                    break
                cc[s[i]] += 1
            best = min(best, j - i + 1)
print(best)
