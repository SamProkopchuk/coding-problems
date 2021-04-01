A = 26
MOD = 1_000_000_007

def shortPalindrome(s):
    c1 = [0] * A
    c2 = [[0] * A for _ in range(A)]
    c3 = [0] * A
    res = 0
    for i in (ord(c) - 97 for c in s):
        res = (res + c3[i]) % MOD
        for j in range(A):
            c3[j] += c2[j][i]
        for j in range(A):
            c2[j][i] += c1[j]
        c1[i] += 1
    return res

print(shortPalindrome(input()))
