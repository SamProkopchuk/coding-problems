n = int(input())
arr = [int(input()) for _ in range(n)]
dp = [1] * n

def update_increasing(i, dir):
    while 0 <= i+dir < n and arr[i+dir] > arr[i]:
        dp[i+dir] = max(dp[i+dir], dp[i] + 1)
        i += dir

update_increasing(0, 1)
update_increasing(n-1, -1)

for i in range(1, n-1):
    if not (arr[i-1] < arr[i] < arr[i+1] or arr[i-1] > arr[i] > arr[i+1]):
        update_increasing(i, -1)
        update_increasing(i, 1)

print(sum(dp))
