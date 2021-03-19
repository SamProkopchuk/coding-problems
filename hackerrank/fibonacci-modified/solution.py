dp = [0] * 21
t1, t2, n = map(int, input().split())

def query(n):
    if n == 1: return t1
    if n == 2: return t2
    if dp[n] == 0:
        dp[n] = query(n-2) + query(n-1) ** 2
    return dp[n]

print(query(n))
