def len_range(start, end, step):
	return (end - start - 1) // step + 1

def solution(n):
	# Max input (10000) will not search past a prime > 2^15
	size = 1 << 15
	primeIdx = [False] * 2 + [True] * (size-2)

	res = ''
	# pstringIdx keeps track of index in "concatenated string of primes"
	pstringIdx = 0
	for seive in range(2, size):
		if not primeIdx[seive]: continue
		# Seive will always be the next prime here
		pstringIdx += len(str(seive))
		if pstringIdx > n:
			res += str(seive)[n - pstringIdx:]
			if len(res) >= 5: break

		# Update primeIdx list given next prime seive
		primeIdx[seive*2::seive] = [False] * len_range(seive * 2, size, seive)
	return res[:5]
