#TEST Complejidades
import os
import random
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import math
fi = open("../../output/arbitraje/test1-bellman-ford.csv",'w+')
fi.write("N,ARBITRAJE,CICLO,TIEMPO\n")
fi.close()
fi = open("../../output/arbitraje/test1-floyd.csv",'w+')
fi.write("N,ARBITRAJE,CICLO,TIEMPO\n")
fi.close()
for n in range(2,1000):
    inputArbitraje = pd.read_csv('../../input/arbitraje/input.csv')
    f = open("input.txt", "w")
    f.write(str(n))
    f.write('\n')
    for x in range(0,n):
        for y in range(0,n):
            if(x!=y):
                valorRandom = random.uniform(0.1,100)
                f.write(str(valorRandom))
                f.write(' ')
            else:
                f.write(str(1))
                f.write(' ')
            
        f.write('\n')
    f.close()
    os.system("../.././arbitraje-bellman-ford ../../output/arbitraje/test1-bellman-ford.csv < input.txt")
    os.system("../.././arbitraje-floyd ../../output/arbitraje/test1-floyd.csv < input.txt")