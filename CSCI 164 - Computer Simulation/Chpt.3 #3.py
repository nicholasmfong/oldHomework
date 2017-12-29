from random import random
from math import exp
total = 0
trials = 100000
for i in range(0,trials):
    total += exp(exp(random()))

answer = total/trials
print("integral of e^e^x from 0-1 is approximately",answer, "based on",trials,"trials")
