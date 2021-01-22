from random import randint, shuffle


def qsort(lst: list, l=None, r=None) -> None:
    if not lst:
        return
    if l is None:
        l = 0
    if r is None:
        r = len(lst) - 1

    def part(l: int, r: int):
        p, r_ = l, r
        while l < r:
            while l < r_ and lst[p] >= lst[l]:
                l += 1
            while r > p and lst[p] <= lst[r]:
                r -= 1
            if l < r:
                lst[l], lst[r] = lst[r], lst[l]
        lst[p], lst[r] = lst[r], lst[p]
        return r

    if l < r:
        r_ = part(l, r)
        qsort(lst, l, r_ - 1)
        qsort(lst, r_ + 1, r)


def visual_test(lst: list) -> None:
    print(lst, end=' => ')
    qsort(lst)
    print(lst)


def main():
    print(f'{"Shuffled Integers [0, 10)":-^{40}}')
    for _ in range(5):
        lst = [*range(10)]
        shuffle(lst)
        visual_test(lst)

    print(f'{"10 Random Integers [0, 10)":-^{40}}')
    for _ in range(10):
        lst = [randint(0, 9) for _ in range(10)]
        visual_test(lst)


if __name__ == '__main__':
    main()
