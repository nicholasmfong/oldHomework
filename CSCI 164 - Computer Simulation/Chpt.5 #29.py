from random import random
from math import floor
from math import log
N = 0   #N = number of buses
t = 0   #t = time
l = 5   #l = lambda
fans = 0
end_time = 1
while(t < end_time):
    t += -log(random())/l
    N += 1
N -= 1  #account for the extra 1 added at the end
for i in range(N):
    fans += (20 + floor(21*random()))

print("The number of fans that arrived by t=1 is",fans)
