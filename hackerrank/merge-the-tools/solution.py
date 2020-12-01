string, k = input(), int(input())
for i in range(0, len(string), k):
    print(''.join([*dict.fromkeys(list(string[i: i+k]))]))
