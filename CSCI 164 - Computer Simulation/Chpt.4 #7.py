from random import random
from math import ceil
trials = 10000
total = 0
for i in range(0,trials):
    dice = [0,0,0,0,0,0,0,0,0,0,0]
    unhit = 11
    count = 0
    while(unhit > 0):
        u = ceil(6*random()) + ceil(6*random())     #u = sum of a pair of dice rolls
        if(dice[u-2] == 0):
            dice[u-2] = 1
            unhit -= 1
        count += 1
    total += count
print("The expected value of x is approximately",total/trials,"under",trials,"trials")

