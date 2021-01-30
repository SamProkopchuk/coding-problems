from random import randint, shuffle


def binary_insertion_sort(lst: list) -> None:
    def binary_insert(r: int, x: int) -> None:
        l = 0
        mid = (l + r + 1) // 2
        while l <= r:
            if x < lst[mid]:
                r = mid - 1
            else:
                l = mid + 1
            mid = (l + r + 1) // 2
        lst.insert(mid, x)
    for i in range(len(lst)):
        binary_insert(i-1, lst.pop(i))


def qsort(lst: list, l=None, r=None) -> None:
    if l is None:
        l = 0
    if r is None:
        r = len(lst) - 1

    def part(l: int, r: int) -> int:
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


def visual_test(sort_fn, lst: list) -> None:
    print(lst, end=' => ')
    sort_fn(lst)
    print(lst)


def main():
    print(f'{"Shuffled Integers [0, 10)":-^{40}}')
    for _ in range(5):
        lst = [*range(10)]
        shuffle(lst)
        visual_test(qsort, lst)

    print(f'{"10 Random Integers [0, 10)":-^{40}}')
    for _ in range(10):
        lst = [randint(0, 9) for _ in range(10)]
        visual_test(binary_insertion_sort, lst)


if __name__ == '__main__':
    main()
