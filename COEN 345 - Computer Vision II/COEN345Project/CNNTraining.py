# -*- coding: utf-8 -*-
"""
Created on Mon May 28 21:17:38 2018

@author: Nicholas Fong
"""

# import the necessary packages
from sklearn.model_selection import train_test_split
from pyimagesearch.nn.conv import FongNet
from pyimagesearch.preprocessing import ImageToArrayPreprocessor
from pyimagesearch.preprocessing import AspectAwarePreprocessor
from pyimagesearch.datasets import SimpleDatasetLoader
from keras.preprocessing.image import ImageDataGenerator
from keras.callbacks import ModelCheckpoint
from keras.optimizers import SGD
from keras.optimizers import Adadelta
from keras.models import load_model
from imutils import paths
import keras.backend as K
import matplotlib.pyplot as plt
import numpy as np
import argparse
import os


## construct the argument parse and parse the arguments
#ap = argparse.ArgumentParser()
#ap.add_argument("-w", "--weights", required=True,
#	help="path to best model weights file")
#args = vars(ap.parse_args())

args = {'dataset': '../datasets/men', 'weights': 'weights/cnn_best_weights.hdf5'}

# grab the list of images that we'll be describing, then extract
# the class label names from the image paths
print("[INFO] loading images...")
imagePaths = list(paths.list_images(args["dataset"]))
classNames = [pt.split(os.path.sep)[-2] for pt in imagePaths]
classNames = [str(x) for x in np.unique(classNames)]

# initialize the image preprocessors
aap = AspectAwarePreprocessor(128, 128)
iap = ImageToArrayPreprocessor()

# load the dataset from disk then scale the raw pixel intensities
# to the range [0, 1]
sdl = SimpleDatasetLoader(preprocessors=[aap, iap])
(data, labels) = sdl.load(imagePaths, verbose=500)
data = data.astype("float") / 255.0
labels = labels.astype("float")

# partition the data into training and testing splits using 75% of
# the data for training and the remaining 25% for testing
(trainX, testX, trainY, testY) = train_test_split(data, labels,
	test_size=0.25)

# construct the image generator for data augmentation
aug = ImageDataGenerator(rotation_range=15, width_shift_range=0.1,
	height_shift_range=0.1, shear_range=0.1, zoom_range=0.1,
	horizontal_flip=True, vertical_flip=False, fill_mode="nearest")

"""# initialize the optimizer and model
def mean_squared_err(y_true, y_pred):
	return pow(K.mean(y_pred), 2)"""

"""print("[INFO] compiling model...")
#opt = SGD(lr=learning_rate, momentum=0.8, decay=learning_rate/num_epoch, nesterov=False)
opt = Adadelta()
model = FongNet.build(width=128, height=128, depth=3)
model.compile(loss="mean_squared_error", optimizer=opt,
	metrics=["mae"])"""

print("[INFO] loading pre-trained network...")
model = load_model(args["weights"])

# construct the callback to save only the *best* model to disk
# based on the validation loss
checkpoint = ModelCheckpoint(args["weights"], monitor="val_loss",
	save_best_only=True, verbose=1)
callbacks = [checkpoint]

# train the network
print("[INFO] training network...")
learning_rate = 0.001 # 0.05
num_epoch = 1
H = model.fit_generator(aug.flow(trainX, trainY, batch_size=32),
	validation_data=(testX, testY), steps_per_epoch=len(trainX) // 32,
	epochs=num_epoch, callbacks=callbacks, verbose=1)

## evaluate the network
#print("[INFO] evaluating network...")
#predictions = model.predict(testX, batch_size=32)
#print(classification_report(testY.argmax(axis=1),
#	predictions.argmax(axis=1), target_names=classNames))

# plot the training loss and accuracy
plt.style.use("ggplot")
plt.figure()
plt.plot(np.arange(0, num_epoch), H.history["loss"], label="train_loss")
plt.plot(np.arange(0, num_epoch), H.history["val_loss"], label="val_loss")
#plt.plot(np.arange(0, num_epoch), H.history["mean_absolute_error"], label="train_mae")
#plt.plot(np.arange(0, num_epoch), H.history["val_mean_absolute_error"], label="val_mae")
plt.title("Training Loss and MAE")
plt.xlabel("Epoch #")
plt.ylabel("Loss/MAE")
plt.legend()
plt.show()