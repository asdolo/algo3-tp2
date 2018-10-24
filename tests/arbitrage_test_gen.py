from __future__ import print_function
import numpy as np
import sys

n = int(sys.argv[1])
#puede ser completo, ciclo, sin.
arbitrage = "ciclo"

print(n)
spread = 0.1
coins = np.random.uniform(low=0.5, high=10.0, size=(n,))
for i in xrange(0,n):
	if arbitrage == "completo":
		for j in xrange(0,n):
			if not i == j:
				print(coins[j]/coins[i]+spread, end=' ')
			else:
				print(1)
		print('')
	if arbitrage == "sin":
		for j in xrange(0,n):
			if not i == j:
				print(coins[j]/coins[i]-spread, end=' ')
			else:
				print(1)
		print('')
	if arbitrage == "ciclo":
		for j in xrange(0,n):
			if not i == (j+1)%n:
				print(1/n, end=' ')
			else:
				print(1.1)
		print('')
		


