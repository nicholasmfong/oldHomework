from random import random
from math import exp
total = 0
trials = 1000000
for i in range(0,trials):
    x = random()
    y = random()
    total += exp(pow((x+y),2))  #e^(x+y)^2

answer = total/trials
print("integral of e^(x+y)^2 from 0-1 for both x and y is approximately",answer, "based on",trials,"trials")
