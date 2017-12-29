from random import random
from math import exp
from math import floor
from math import log
from time import time
init_time = time()
trials = 10000
answers = [0]
for j in range(0,74):           #Generate buckets of width 0.2 to count our results up to 15
    answers += [0]
for i in range(0,trials):
    x = -log(random()*random())
    answers[floor(x*5)] += 1
print("Time taken =",time()-init_time,"seconds for",trials,"trials")
for k in range(len(answers)):
    print("Count between",k/5,"-",(k+1)/5,"=",answers[k]," Expected amount =",
          (exp(-(k/5))*(1+(k/5))-exp(-(k+1)/5)*(1+(k+1)/5))*trials)

