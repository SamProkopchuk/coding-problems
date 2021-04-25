from collections import Counter

c = Counter(input().strip() for _ in range(int(input())))
print('\n'.join(str(c[input().strip()]) for _ in range(int(input()))))
