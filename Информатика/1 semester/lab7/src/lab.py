import io

A = {}
with io.open('text.txt', encoding='utf-8') as file:
	for i in file:
		for x in i:
			x = x.lower()
			if A.get(x, False):
				A[x] += 1
			else:
				A[x] = 1
print(A)