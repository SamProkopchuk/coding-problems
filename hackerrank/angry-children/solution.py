n, k = int(input()), int(input()) - 1
arr = [int(input()) for _ in range(n)]
arr.sort()
min_ = min(arr[i+k]-arr[i] for i in range(n-k))
print(min_)
