from random import random
trials = 100000
p = [0.3,0.5,0.85,1]
total = 0
x_values = [0,0,0,0]    #spot i refers to x = i+1
for i in range(0,trials):
    u = random()
    for j in range(len(p)):
        if(u < p[j]):
            x = j+1
            total += x
            x_values[j] += 1
            break

print("The expected value of x is approximately",total/trials,"under",trials,"trials")
print("The number of times RV x hit certain values are:")
for i in range(len(x_values)):
    print("x =",i+1,":",x_values[i])
    
