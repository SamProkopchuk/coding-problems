for _ in range(int(input())):
    word = input()
    previdx = -1
    for idx, c in reversed(list(enumerate(word))):
        if c < word[previdx]:
            swapidx = word.rindex(min(filter(lambda c_: c_ > c, word[idx+1:])))
            wordl = list(word)
            wordl[idx], wordl[swapidx] = wordl[swapidx], wordl[idx]
            wordl[idx+1:] = sorted(wordl[idx+1:])
            print(''.join(wordl))
            break
        previdx = idx
    else:
        print('no answer')
