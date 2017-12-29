# FIFO single server queue

from random import random
from math import log
from math import floor

#This is for the arrival distribution
def generateExponential(L):     #L = lambda
    return -log(random())/L

#This is for the departure distribution
def generateUniform(low,high):      #low = lower bound, high = upper bound for uniform dist.
    return low+random()*(high-low)  #assume that high >= low

#Initializations of variables
Lambda = 20             #lambda occurences per hour
lowerBound = 1/60       #To leave the queue takes at least 1 minute
upperBound = 1/12       #To leave the queue takes at most 5 minutes. Set so that the expected value of departures and arrivals is the same
infinity = 100000       #Treat 100000 as infinity. Make as large as needed to be treated as infinity
trials = 50
lowerLambda = 15
upperLambda = 30
delta = 1
step = lowerLambda
maxLengths = [0]
avgLengths = [0]
avgClosed = [0]
maxClosed = [0]
flow = [0]
j = floor((upperLambda - lowerLambda) / delta)
for i in range(j):
    maxLengths += [0]
    avgLengths += [0]
    avgClosed += [0]
    maxClosed += [0]
    

for k in range(j):
    step = lowerLambda + (k * delta)
    averageLineLength = 0
    counter = 0
    maximumLineLength = 0
    averageClosingLineLength = 0
    maximumClosingLineLength = 0
    for i in range(trials):
        time = 0                #t
        arrivals = [0]          #array of when each arrival happened
        departures = [0]        #array of when each departure happened
        numArrivals = 0         #Na
        numDepartures = 0       #Nd
        timeNextArrival = generateExponential(Lambda)   #Ta
        timeNextDeparture = infinity                    #Td.
        closingTime = 8         #T (hours)
        lineLength = 0          #State variable n
        while(time <= closingTime):     #While the queue is open
            if(timeNextArrival <= timeNextDeparture and timeNextArrival < closingTime): #arrivals
                time = timeNextArrival  
                numArrivals += 1        
                lineLength += 1         
                arrivals += [time]      #A(Na) = t
                timeNextArrival = time + generateExponential(Lambda)
                if(lineLength == 1):
                    timeNextDeparture = time + generateExponential(step)
                averageLineLength += lineLength
                counter += 1
                if(lineLength > maximumLineLength):
                    maximumLineLength = lineLength

            else:       #timeNextDeparture < timeNextArrival or it is past closing time
                time = timeNextDeparture
                lineLength -= 1
                numDepartures += 1
                departures += [time]
                if(lineLength == 0):
                    timeNextDeparture = infinity
                else:
                    timeNextDeparture = time + generateExponential(step)
                averageLineLength += lineLength
                counter += 1
        print(lineLength)
        while(lineLength > 0):          #When the queue is closed
            averageClosingLineLength += lineLength
            if(lineLength > maximumClosingLineLength):
                maximumClosingLineLength = lineLength
            time = timeNextDeparture
            lineLength -= 1
            numDepartures += 1
            departures += [time]
            timeNextDeparture = time + generateExponential(step)
            averageLineLength += lineLength
            counter += 1

        timeNextDeparture = infinity        #reset the value
        if(maximumLineLength > maxLengths[k]):
            maxLengths[k] = maximumLineLength
        if(maximumClosingLineLength > maxClosed[k]):
            maxClosed[k] = maximumClosingLineLength
        avgLengths[k] += averageLineLength / counter
    avgClosed[k] += averageClosingLineLength
    print(averageClosingLineLength)
   #flow += [len(arrivals)]
    step += delta

for i in range(j):
    avgLengths[i] /= trials
    avgClosed[i] /= trials
for i in range(len(maxLengths)):
    print("At lambda departure =",lowerLambda + delta * i,"max line length =",maxLengths[i],", avg line length =",avgLengths[i],"max line length at closing time =",maxClosed[i],"avg closing line length =",avgClosed[i])
