ntos = {
    1: 'one',
    2: 'two',
    3: 'three',
    4: 'four',
    5: 'five',
    6: 'six',
    7: 'seven',
    8: 'eight',
    9: 'nine',
    10: 'ten',
    11: 'eleven',
    12: 'twelve',
    13: 'thirteen',
    14: 'fourteen',
    15: 'fifteen',
    16: 'sixteen',
    17: 'seventeen',
    18: 'eighteen',
    19: 'nineteen',
    20: 'twenty',
    30: 'thirty'}
for i in range(1, 10):
    ntos[20 + i] = f'{ntos[20]} {ntos[i]}'

h, m = int(input()), int(input())
res = ''
if m == 0:
    res = f'{ntos[h]} o\' clock'
elif m == 1:
    res = f'{ntos[m]} minute past {ntos[h]}'
elif m == 15:
    res = f'quarter past {ntos[h]}'
elif m == 30:
    res = f'half past {ntos[h]}'
elif m == 45:
    res = f'quarter to {ntos[h % 12 + 1]}'
elif 1 <= m <= 30:
    res = f'{ntos[m]} minutes past {ntos[h]}'
else:
    res = f'{ntos[60-m]} minutes to {ntos[h % 12 + 1]}'
print(res)
