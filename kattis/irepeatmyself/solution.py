from sys import stdin, stdout
from re import findall

for _ in range(int(input().strip())):
    s = input()
    if len(s) in (0, 1):
        print(len(s))
    else:
        for prefix_size in range(1, len(s)):
            if s in s[:prefix_size] * 200:
                stdout.write(str(prefix_size) + '\n')
                break
        else:
            stdout.write(str(len(s)) + '\n')
