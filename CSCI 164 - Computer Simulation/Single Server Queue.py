# FIFO single server queue

from random import random
from math import log
from math import exp

#This is for the arrival distribution
def generateExponential(L):     #L = lambda
    return -log(random())/L

#This is for the departure distribution
def generateUniform(low,high):      #low = lower bound, high = upper bound for uniform dist.
    return low+random()*(high-low)  #assume that high >= low

def generateWeibell(alpha,beta):
    return beta * exp(((1/alpha)*log(-log(random()))))

#Initializations of variables
lambdaArrivals = 20             #lambda occurences per hour
lambdaDepartures = 25
alpha = 2.7
beta = 0.056
lowerBound = 1/60       #To leave the queue takes at least 1 minute
upperBound = 1/12       #To leave the queue takes at most 5 minutes. Set so that the expected value of departures and arrivals is the same
infinity = 100000       #Treat 100000 as infinity. Make as large as needed to be treated as infinity
time = 0                #t
arrivals = [0]          #array of when each arrival happened
departures = [0]        #array of when each departure happened
numArrivals = 0         #Na
numDepartures = 0       #Nd
timeNextArrival = generateExponential(lambdaArrivals)   #Ta
timeNextDeparture = infinity                    #Td.
closingTime = 1000         #T (hours)
lineLength = 0          #State variable n
maxLineLength = 0
longLine = 15
numTimesLongLine = 0
totalTimeLongLine = 0
startOfLongLine = 0
averageExtremeEvent = 0
expectedValueDepartures = 0
for i in range(10000):
    expectedValueDepartures += generateWeibell(alpha,beta)
expectedValueDepartures /= 10000

while(time <= closingTime):     #While the queue is open
    if(timeNextArrival <= timeNextDeparture and timeNextArrival < closingTime):
        if(lineLength == 9):
            numTimesLongLine += 1
            startOfLongLine = timeNextArrival
        if(lineLength >= 10):
            averageExtremeEvent += (timeNextArrival - time)*lineLength
        time = timeNextArrival
        numArrivals += 1        
        lineLength += 1         
        arrivals += [time]      #A(Na) = t
        timeNextArrival = time + generateExponential(lambdaArrivals)
        if(lineLength > maxLineLength):
            maxLineLength = lineLength
        if(lineLength == 1):
            timeNextDeparture = time + generateWeibell(alpha,beta)

    else:       #timeNextDeparture < timeNextArrival or it is past closing time
        if(lineLength >= 10):
            averageExtremeEvent += (timeNextDeparture - time)*lineLength
        time = timeNextDeparture
        if(lineLength == 10):
            totalTimeLongLine += (time - startOfLongLine)
        lineLength -= 1
        numDepartures += 1
        departures += [time]
        if(lineLength == 0):
            timeNextDeparture = infinity
        else:
            timeNextDeparture = time + generateWeibell(alpha,beta)

while(lineLength > 0):          #When the queue is closed
    if(lineLength >= 10):
        averageExtremeEvent += (timeNextDeparture - time)*lineLength
    time = timeNextDeparture
    if(lineLength == 10):
        totalTimeLongLine += (time - startOfLongLine)
    lineLength -= 1
    numDepartures += 1
    departures += [time]
    timeNextDeparture = time + generateWeibell(alpha,beta)

timeNextDeparture = infinity        #reset the value, although we could remove this without any affect on functionality
averageExtremeEvent /= totalTimeLongLine
print("With a time length of",closingTime,", we had a max line length of",maxLineLength)
print("We had an expected value for arrivals as",1/lambdaArrivals,", and an expected value for departures as",expectedValueDepartures)
print("With a long line defined as",longLine,", we had a long line",numTimesLongLine,"times, and we had a long line for time length",totalTimeLongLine,"and had an average extreme event as a line length of",averageExtremeEvent)
##for i in range(len(arrivals)):
##    print("Customer",i,"arrived at",arrivals[i],"and departed at",departures[i])
