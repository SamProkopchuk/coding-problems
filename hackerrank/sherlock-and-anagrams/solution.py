from collections import Counter
from collections import defaultdict
from math import comb
# If < python 3.8 need to define own comb(n, k) function.


for _ in range(int(input())):
    s = input()
    agrams = defaultdict(int)
    for winsize in range(1, len(s)):
        for start in range(len(s) - winsize + 1):
            agrams[frozenset(Counter(s[start: start + winsize]).items())] += 1
    print(sum(comb(c, 2) for c in agrams.values()))
