from typing import List


def find_root(parent: List[int], a: int) -> int:
    root: int = a
    while root != parent[root]:
        root = parent[root]
    while a != root:
        next: int = parent[a]
        parent[a] = root
        a = next
    return root


def union_sets(parent: List[int], size: List[int], a: int, b: int) -> None:
    a = find_root(parent, a)
    b = find_root(parent, b)
    if a != b:
        if size[b] > size[a]:
            a, b = b, a
        parent[b] = a
        size[a] += size[b]


for _ in range(int(input())):
    n, m, c_lib, c_road = map(int, input().split())
    if c_lib <= c_road:
        # Don't care about edges, discard the edge data:
        for __ in range(m):
            ___ = input()
        print(c_lib * n)
        continue
    parent: List[int] = list(range(n))
    size: List[int] = [1] * n
    for __ in range(m):
        a, b = (int(s) - 1 for s in input().split())
        union_sets(parent, size, a, b)
    seen = [False] * n
    cost = 0
    for a in range(n):
        root: int = find_root(parent, a)
        if seen[root]:
            continue
        seen[root] = True
        cost += c_lib + (size[root] - 1) * c_road
    print(cost)
