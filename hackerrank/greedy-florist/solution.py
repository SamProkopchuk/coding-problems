n, k = map(int, input().split())
prices = [*map(int, input().split())]
prices.sort(reverse=True)
cost = sum((1 + i // k) * price for i, price in enumerate(prices))
print(cost)
