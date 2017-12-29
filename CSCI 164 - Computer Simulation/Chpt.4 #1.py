from random import random
trials = [100,1000,10000]
p1 = 1/3
for j in range(len(trials)):
    totalp1 = 0
    totalp2 = 0
    for i in range(0,trials[j]):
        u = random()
        if(u < p1):
            totalp1+=1
        else:
            totalp2+=1
    print("The proportion of p1 is approximately",totalp1/trials[j], "and p2 is approximately",totalp2/trials[j],"with",trials[j],"trials")
