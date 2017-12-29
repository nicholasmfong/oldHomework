from random import random   #random()
from math import log        #ln
probability = 0.05          #probability of an insurance claim
expectedCost = 800          #expected cost of an insurance claim
over = 0
trials = 10000
for i in range(0,trials):
    total = 0
    claims = 0
    for j in range(0,1000):     #get number of insurance claims
        if(random() < probability):
            claims += 1
    for k in range(0,claims):   #use exponential dist. for each claim
        cost = -expectedCost*log(random())       #X = -800ln(U)
        total += cost
    if(total > 50000):
        over += 1

answer = over/trials
print("The probability that the sum of these claims exceeds 50k is",answer, "based on",trials,"trials")
