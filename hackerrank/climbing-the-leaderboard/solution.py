from collections import deque

input()
scores = list(dict.fromkeys(map(int, input().strip().split())))
input()
pscores = deque(map(int, input().strip().split()))

rank = len(scores)
res = []

score = scores.pop()
while pscores:
    pscore = pscores.popleft()
    while scores:
        if pscore <= score:
            res.append(rank + (1 if pscore < score else 0))
            break
        score = scores.pop()
        rank -= 1
    else:
        res.append(rank + (1 if pscore < score else 0))

print(*res, sep = '\n')
