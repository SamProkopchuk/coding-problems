from sys import stdin, stdout

for _ in range(int(input().strip())):
    d, n = map(int, stdin.readline().strip().split())
    nums = list(map(int, stdin.readline().strip().split()))
    remFreqs = [0] * d
    partSum = 0
    for idx in range(n):
        partSum += nums[idx]
        remFreqs[partSum % d] += 1
    res = remFreqs[0]
    for remFreq in remFreqs:
        if remFreq > 1:
            res += (remFreq * (remFreq - 1)) // 2
    stdout.write(str(res) + '\n')