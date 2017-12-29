# FIFO single server queue exponential departure time distribution

from random import random
from math import log
from math import exp

def generateExponential(L):     #L = lambda
    return -log(random())/L

#Initializations of variables
lambdaArrivals = 20             #lambda occurences per hour
lambdaDepartures = 25
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
longLine = 10
numTimesLongLine = 0
totalTimeLongLine = 0
startOfLongLine = 0
averageExtremeEvent = 0

while(time <= closingTime):     
    if(timeNextArrival <= timeNextDeparture and timeNextArrival < closingTime):
        if(lineLength == (longLine-1)):
            numTimesLongLine += 1
            startOfLongLine = timeNextArrival
        if(lineLength >= longLine):
            averageExtremeEvent += (timeNextArrival - time)*lineLength
        time = timeNextArrival
        numArrivals += 1        
        lineLength += 1         
        arrivals += [time]      #A(Na) = t
        timeNextArrival = time + generateExponential(lambdaArrivals)
        if(lineLength > maxLineLength):
            maxLineLength = lineLength
        if(lineLength == 1):
            timeNextDeparture = time + generateExponential(lambdaDepartures)
        
    else:       #timeNextDeparture < timeNextArrival or it is past closing time
        if(lineLength >= longLine):
            averageExtremeEvent += (timeNextDeparture - time)*lineLength
        time = timeNextDeparture
        if(lineLength == longLine):
            totalTimeLongLine += (time - startOfLongLine)
        lineLength -= 1
        numDepartures += 1
        departures += [time]
        if(lineLength == 0):
            timeNextDeparture = infinity
        else:
            timeNextDeparture = time + generateExponential(lambdaDepartures)

while(lineLength > 0):          #When the queue is closed
    if(lineLength >= longLine):
        averageExtremeEvent += (timeNextDeparture - time)*lineLength
    time = timeNextDeparture
    if(lineLength == longLine):
        totalTimeLongLine += (time - startOfLongLine)
    lineLength -= 1
    numDepartures += 1
    departures += [time]
    timeNextDeparture = time + generateExponential(lambdaDepartures)

averageExtremeEvent /= totalTimeLongLine
print("Using an exponential departure time:")
print("With a time length of",closingTime,", we had a max line length of",maxLineLength)
print("We had an expected value for arrivals as",1/lambdaArrivals,", and an expected value for departures as",1/lambdaDepartures)
print("With a long line defined as",longLine,", we had a long line",numTimesLongLine,"times, and we had a long line for time length",totalTimeLongLine,"and had an average extreme event as a line length of",averageExtremeEvent)
