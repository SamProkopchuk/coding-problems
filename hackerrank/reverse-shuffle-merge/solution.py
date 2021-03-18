from collections import Counter

s = input()
c = Counter(s)
reverse = {k: v // 2 for k, v in c.items()}
shuffle = reverse.copy()
A = []

for c in reversed(s):
    if reverse[c]:
        while A and A[-1] > c and shuffle[A[-1]]:
            r = A.pop()
            reverse[r] += 1
            shuffle[r] -= 1
        A.append(c)
        reverse[c] -= 1
    else:
        shuffle[c] -= 1

print(''.join(A))
