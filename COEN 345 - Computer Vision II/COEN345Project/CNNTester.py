# -*- coding: utf-8 -*-
"""
Created on Thu May 31 18:13:00 2018

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

args = {'dataset': '../datasets/menClassTestImages', 'weights': 'weights/cnn_best_weights_day_7.hdf5'}

# grab the list of images that we'll be describing, then extract
# the class label names from the image paths
print("[INFO] loading images...")
imagePaths = list(paths.list_images(args["dataset"]))
#classNames = [pt.split(os.path.sep)[-2] for pt in imagePaths]
#classNames = [str(x) for x in np.unique(classNames)]

# initialize the image preprocessors
aap = AspectAwarePreprocessor(128, 128)
iap = ImageToArrayPreprocessor()

# load the dataset from disk then scale the raw pixel intensities
# to the range [0, 1]
sdl = SimpleDatasetLoader(preprocessors=[aap, iap])
(data, labels) = sdl.load(imagePaths, verbose=500)
data = data.astype("float") / 255.0

print("[INFO] loading pre-trained network...")
model = load_model(args["weights"])


# evaluate the network
print("[INFO] evaluating network...")
predictions = model.predict(data, batch_size=32)
print(np.round(predictions, 1))