# -*- coding: utf-8 -*-
"""
Created on Mon May 28 21:17:38 2018

@author: Nicholas Fong
"""

# import the necessary packages
from keras.models import Sequential
from keras.layers.normalization import BatchNormalization
from keras.layers.convolutional import Conv2D
from keras.layers.convolutional import MaxPooling2D
from keras.layers.core import Activation
from keras.layers.core import Flatten
from keras.layers.core import Dropout
from keras.layers.core import Dense
from keras import backend as K

# Based on MiniVGGNet code from Adrian at PyImageSearch
class FongNet:
	@staticmethod
	def build(width, height, depth):
		# initialize the model along with the input shape to be
		# "channels last" and the channels dimension itself
		model = Sequential()
		inputShape = (height, width, depth)
		chanDim = -1

		# if we are using "channels first", update the input shape
		# and channels dimension
		if K.image_data_format() == "channels_first":
			inputShape = (depth, height, width)
			chanDim = 1

		# first CONV => ELU => BN => POOL => DO layer set
		model.add(Conv2D(128, (3, 3), padding="same",
			input_shape=inputShape))
		model.add(Activation("elu"))
		model.add(BatchNormalization(axis=chanDim))
		model.add(MaxPooling2D(pool_size=(2, 2)))
		model.add(Dropout(0.25))

		# second CONV => ELU => BN => POOL => DO layer set
		model.add(Conv2D(128, (3, 3), padding="same",
			input_shape=inputShape))
		model.add(Activation("elu"))
		model.add(BatchNormalization(axis=chanDim))
		model.add(MaxPooling2D(pool_size=(2, 2)))
		model.add(Dropout(0.25))

		# third CONV => ELU => BN => POOL => DO layer set
		model.add(Conv2D(128, (3, 3), padding="same",
			input_shape=inputShape))
		model.add(Activation("elu"))
		model.add(BatchNormalization(axis=chanDim))
		model.add(MaxPooling2D(pool_size=(2, 2)))
		model.add(Dropout(0.25))

		# first set of fully connected nodes
		model.add(Flatten())
		model.add(Dense(512))
		model.add(Dropout(0.5))

		# Final fully connected output
		model.add(Dense(1))

		# return the constructed network architecture
		return model