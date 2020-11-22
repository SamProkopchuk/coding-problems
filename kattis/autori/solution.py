import re
s = input().strip()
print(re.sub(r'-|[a-z]', '', s))
