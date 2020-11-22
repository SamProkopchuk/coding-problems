from sys import stdin, stdout
from collections import deque

class Teque():
    def __init__(self):
        self.deque0 = deque()
        self.deque1 = deque()

    def get(self, idx):
        if idx < len(self.deque0):
            return self.deque0[idx]
        return self.deque1[idx - len(self.deque0)]

    def push_front(self, x):
        self.deque0.appendleft(x)
        if len(self.deque0) > len(self.deque1):
            self.deque1.appendleft(self.deque0.pop())

    def push_back(self, x):
        self.deque1.append(x)
        if len(self.deque1) > len(self.deque0):
            self.deque0.append(self.deque1.popleft())

    def push_middle(self, x):
        if len(self.deque1) > len(self.deque0):
            self.deque0.append(self.deque1.popleft())
        self.deque1.appendleft(x)


teque = Teque()

for _ in range(int(input().strip())):
    op, x = stdin.readline().split()
    x = int(x)
    if op == 'get':
        stdout.write(str(teque.get(x)) + '\n')
    elif op == 'push_front':
        teque.push_front(x)
    elif op == 'push_back':
        teque.push_back(x)
    elif op == 'push_middle':
        teque.push_middle(x)
