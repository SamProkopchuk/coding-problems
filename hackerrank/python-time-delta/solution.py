from datetime import datetime
for _ in range(int(input().strip())):
    d0 = datetime.strptime(input().strip(), '%a %d %b %Y %H:%M:%S %z')
    d1 = datetime.strptime(input().strip(), '%a %d %b %Y %H:%M:%S %z')
    print(int(abs(d1.timestamp() - d0.timestamp())))
