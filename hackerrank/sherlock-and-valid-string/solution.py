from collections import Counter

def is_valid(s: str):
    c = Counter(Counter(s).values())
    if len(c) == 1:
        return True
    elif len(c) == 2:
        (k1, v1), (k2, v2) = c.items()
        return (v1 == 1 and k1-1 in [0, k2]) or (v2 == 1 and k2-1 in [0, k1])
    else:
        return False

print('YES' if is_valid(input()) else 'NO')
