from sys import stdin, stdout

for _ in range(int(input())):
    word = stdin.readline().strip()
    maxidx = -1
    for idx, c in reversed(list(enumerate(word))):
        if c < word[maxidx]:
            swapidx = word.rindex(min(filter(lambda c_: c_ > c, word[idx+1:])))
            wordl = list(word)
            wordl[idx], wordl[swapidx] = wordl[swapidx], wordl[idx]
            wordl[idx+1:] = sorted(wordl[idx+1:])
            stdout.write(''.join(wordl) + '\n')
            break
        maxidx = idx
    else:
        stdout.write('no answer\n')
