string, k = input(), int(input())
for i in range(0, len(string), k):
    print(*dict.fromkeys(string[i: i+k]), sep='')
