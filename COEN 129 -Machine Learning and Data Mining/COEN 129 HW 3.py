#COEN 129 HW 3
#Yi Fang
#Nicholas Fong
#5-9-17
#Coded in Python 3.4.1
#Numpy 1.8.1

import numpy as np  #for matrices
import math #for log

#calculate w using the closed for linear regression formula w = (X.T*X)^-1*X.T*y
def linReg(X, y):
    return np.dot(np.dot(np.linalg.inv(np.dot(X.T, X)), X.T), y)

#calculate w using closed form ridge regression w = (X.T*X-lambda*I)^-1*X.T*y
def ridgeReg(X, y, l):
    return np.dot(np.dot(np.linalg.inv(np.dot(X.T, X)-l*np.eye(len(X[0]))), X.T), y)

#calculate the RMSE given y and yHat. RMSE = sqrt(sum((y-yHat)^2)/n)
def RMSE(y, yHat):
    return math.sqrt(sum((y-yHat)**2)/len(y))

#evaluate if any element in w changes by more than epsilon
def convergence(w, w2, e):
    for i in range(len(w)):
        if(abs(w[i]-w2[i]) > e):
            return False
    return True

#gradient descent for either linear or ridge regression. wt+1 = wt + gradientDescent()
def gradientDescent(X, y, l, a, w):    #l = lambda, a = alpha
    return a*(np.dot(X.T, (y - np.dot(X, w))) - l * w)

#Section 0: Get and parse the data -----------------------------------
#get the data
trainingData = np.genfromtxt('C:\\Nicholas\\CSCI\\COEN 129\\crime-training-data.txt', delimiter='\t')
testData = np.genfromtxt('C:\\Nicholas\\CSCI\\COEN 129\\crime-test-data.txt', delimiter='\t')

#delete the first row because it is just the column names
trainingData = np.delete(trainingData, (0), axis=0)
testData = np.delete(testData, (0), axis=0)

#randomize the data to reduce bias
np.random.shuffle(trainingData)
np.random.shuffle(testData)

#split the X and y values where the first column are the y values
trainingX = trainingData[:,1:]
trainingY = trainingData[:,0]
testX = testData[:,1:]
testY = testData[:,0]
#add a column of 1s to the X matrices for the constant
ones = np.ones((len(trainingX),1))
trainingX = np.append(trainingX, ones, axis=1)
ones = np.ones((len(testX),1))
testX = np.append(testX, ones, axis=1)

#Section 1: Linear Regression using the closed form solution ---------
#do linear regression with the closed form solution
wClosedFormLinReg = linReg(trainingX, trainingY)

#calculate y-hat and the RMSE on training & test data
yHatLinRegTraining = np.dot(trainingX, wClosedFormLinReg)
RMSELinRegTraining = RMSE(trainingY, yHatLinRegTraining)
yHatLinRegTest = np.dot(testX, wClosedFormLinReg)
RMSELinRegTest = RMSE(testY, yHatLinRegTest)
print('Section 1: Linear Regression Closed Form Solution')
print('RMSE training data:', RMSELinRegTraining)
print('RMSE test data:', RMSELinRegTest)

#Section 2: 5-fold CV with closed form ridge regression --------------
#loop over 10 different lambda values and then 5-fold CV for each lambda
print('\nSection 2: Closed form Ridge Regression using 5-fold CV')
lambdaRMSE = np.zeros(10)   #the lowest RMSE is the ideal lambda
for i in range(10):
    Lambda = 400 / pow(2,i)
    kFoldRMSE = np.zeros(5) #RMSE for each fold
    for j in range(5):
        #split the data into validation and training data
        validationX = trainingX[len(trainingX)/5*j:len(trainingX)/5*(j+1),:]
        validationY = trainingY[len(trainingY)/5*j:len(trainingY)/5*(j+1)]
        leftX = trainingX[0:len(trainingX)/5*j,:]
        rightX = trainingX[len(trainingX)/5*(j+1):,:]
        lambdaTrainingX = np.concatenate((leftX, rightX), axis=0)
        leftY = trainingY[0:len(trainingY)/5*j]
        rightY = trainingY[len(trainingY)/5*(j+1):]
        lambdaTrainingY = np.concatenate((leftY, rightY), axis=0)

        #do ridge regression
        w = ridgeReg(lambdaTrainingX, lambdaTrainingY, Lambda)
        yHat = np.dot(validationX, w)
        kFoldRMSE[j] = RMSE(validationY, yHat)  #store the information
    lambdaRMSE[i] = np.mean(kFoldRMSE)
optimalLambda = 400 / pow(2, np.argmin(lambdaRMSE))
print('RMSE is smallest with Lambda =', optimalLambda)

#calculate ridge regression over the whole training set using the ideal lambda
w = ridgeReg(trainingX, trainingY, optimalLambda)
yHat = np.dot(testX, w)
RMSERidgeReg = RMSE(testY, yHat)
print('RMSE for ridge regression at the optimal lambda =', RMSERidgeReg)

#Section 3: Gradient descent using linear regression
wt = np.random.normal(0, 1, 96)  #initial guess of w with random gaussian numbers
iterations = 0
keepGoing = True
while keepGoing:
    iterations += 1
    wt2 = wt + gradientDescent(trainingX, trainingY, 0, pow(10,-5), wt)
    if convergence(wt, wt2, pow(10, -6)):
        keepGoing = False
    wt = wt2

#use results from gradient descent to calculate RMSE and print results
yHat = np.dot(trainingX, wt)
RSMELinGradDescTraining = RMSE(trainingY, yHat)
yHat = np.dot(testX, wt)
RSMELinGradDescTest = RMSE(testY, yHat)
print('\nSection 3: Gradient Descent with linear regression converged after', iterations, 'iterations')
print('RMSE training data:', RSMELinGradDescTraining)
print('RMSE test data:', RSMELinGradDescTest)

#Section 4: Gradient descent using ridge regression
wt = np.random.normal(0, 1, 96)  #initial guess of w with random gaussian numbers
iterations = 0
keepGoing = True
while keepGoing:
    iterations += 1
    wt2 = wt + gradientDescent(trainingX, trainingY, optimalLambda, pow(10,-5), wt)
    if convergence(wt, wt2, pow(10, -5)):
        keepGoing = False
    wt = wt2

#use results from gradient descent to calculate RMSE and print results
yHat = np.dot(trainingX, wt)
RSMERidgeGradDescTraining = RMSE(trainingY, yHat)
yHat = np.dot(testX, wt)
RSMELRidgeGradDescTest = RMSE(testY, yHat)
print('\nSection 4: Gradient Descent with ridge regression converged after', iterations, 'iterations')
print('RMSE training data:', RSMERidgeGradDescTraining)
print('RMSE test data:', RSMELRidgeGradDescTest)
