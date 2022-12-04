import re

class InclusiveRange:
    def __init__(self, a, b):
        self.l = min(a, b)
        self.r = max(a, b)
    def contains(self, i_range):
        return all(self.l <= x <= self.r for x in (i_range.l, i_range.r))
        
ans = 0
with open("input.txt") as f:
    for line in f:
        a, b, c, d = map(int, re.findall("\d+", line))
        x = InclusiveRange(a, b)
        y = InclusiveRange(c, d)
        if x.contains(y) or y.contains(x):
            ans += 1
print(ans)
