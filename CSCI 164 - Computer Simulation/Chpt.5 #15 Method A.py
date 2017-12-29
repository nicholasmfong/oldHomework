from random import random
from math import exp
from math import floor
from time import time
init_time = time()
trials = 10000
answers = [0]
for j in range(0,74):           #Generate buckets of width 0.2 to count our results up to 15
    answers += [0]
for i in range(0,trials):
    u = random()
    low = 0
    high = 15                   #F(15) = 1 with 5 decimals of accuracy
    mid = 7.5
    F = 1-exp(-mid)*(1+mid)
    while(abs(u-F)>0.00001):     #use binary search to find the inverse transform value
        if(u<F):
            high = mid
            mid = (mid + low)/2
        else:
            low = mid
            mid = (mid + high)/2
        F = 1-exp(-mid)*(1+mid)
    answers[floor(mid*5)] += 1
print("Time taken =",time()-init_time,"seconds for",trials,"trials")
for k in range(len(answers)):
    print("Count between",k/5,"-",(k+1)/5,"=",answers[k]," Expected amount =",
          (exp(-(k/5))*(1+(k/5))-exp(-(k+1)/5)*(1+(k+1)/5))*trials)

