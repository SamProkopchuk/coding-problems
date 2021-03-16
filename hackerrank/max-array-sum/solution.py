n = int(input())
nums = [*map(int, input().split())]
dp = [0] * n
dp[0] = max(0, nums[0])
if n > 1:
    dp[1] = max(0, nums[1])
if n > 2:
    dp[2] = max(dp[0], dp[0] + nums[2])

for i in range(3, n):
    dp[i] = max(
        dp[i - 2],
        dp[i - 2] + nums[i],
        dp[i - 3],
        dp[i - 3] + nums[i])

print(max(dp))
