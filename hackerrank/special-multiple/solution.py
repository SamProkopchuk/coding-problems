from itertools import count

answers = [None]
for x in range(1, 501):
    for i in count(1):
        q = int(f'{i:b}'.replace('1', '9'))
        if q % x == 0:
            answers.append(q)
            break


for _ in range(int(input())):
    print(answers[int(input())])
