n, k = int(input()), int(input()) - 1
arr = sorted(int(input()) for _ in range(n))
print(min(arr[i+k]-arr[i] for i in range(n-k)))
