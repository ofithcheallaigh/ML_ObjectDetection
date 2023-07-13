# https://www.datacamp.com/tutorial/convolutional-neural-networks-python

import numpy as np
from keras.utils import to_categorical
import matplotlib.pyplot as plt

import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import cm
import seaborn as sns
import numpy as np
from statistics import mean 

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler

from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import OneHotEncoder

from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.naive_bayes import GaussianNB
from sklearn.svm import SVC
from sklearn import neighbors

from my_fns import modify_to_grid_zero_fn, get_knn_n_plot

import warnings
warnings.simplefilter(action='ignore', category=FutureWarning)

# Read in the data
dataset1 = pd.read_csv("MATLAB\Data\grid0_closeddoor_clearhallway.csv")
# dataset1 = modify_to_grid_zero_fn(dataset1) 
dataset2 = pd.read_csv("MATLAB\Data\grid0_displaystand_clearhallway.csv")
# dataset1=dataset2 # Used to really test the model
dataset3 = pd.read_csv("MATLAB\Data\grid0_largebin_clearhallway.csv")
dataset4 = pd.read_csv("MATLAB\Data\grid0_storagebox_clearhallway.csv")

data = np.vstack((dataset2,dataset3,dataset4))
# data = data.drop("Var1",axis=1)
data = pd.DataFrame(data) # Convert to DataFrame
data.columns=["Channel1","Channel2","LabelObject","Grid"] # Assign column names
# data.to_csv('grid0_storagebox_clearhallway.csv') # This was here to output a text file to show Ian

# For new_data
new_data = ((dataset1))
new_data = pd.DataFrame(new_data) # Convert to DataFrame
new_data.columns=["Channel1","Channel2","LabelObject","Grid"] # Assign column names

# pick out rows depending on grid num
# This was added in to just pick out grid pos 1
# grid1_data = data.loc[data['Grid']==1]
# data = grid1_data

feature_names = ['Channel1','Channel2'] # Features we are interested in
# response = data['Grid'] # Response we are interested in
# response = data['LabelObject'] # Response we are interested in

# Replaces Yes/No with 1/0. Required because some algo will not accept categorical data
data.LabelObject.replace(('Yes', 'No'), (1, 0), inplace=True) 
new_data.LabelObject.replace(('Yes', 'No'), (1, 0), inplace=True)

# X and y are what will be passed through the algorithms to train the model
X = data[feature_names]
y = data['LabelObject']
# y = data['Grid']

X_new_data = new_data[feature_names]
y_new_data = new_data['LabelObject']
# y_new_data = new_data['Grid']

# Creating Training and Test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0) # train_test_split is the best way to slipt up the data
scaler=MinMaxScaler() # Using a scaler because there can be a lot of variability in the data values
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# This will be where I will gather my train data that the system has not been tested on
X_train_new_data, X_test_new_data, y_train_new_data, y_test_new_data = train_test_split(X_new_data, y_new_data, random_state=0) # train_test_split is the best way to slipt up the data
scaler=MinMaxScaler() # Using a scaler because there can be a lot of variability in the data values
X_train_new_data = scaler.fit_transform(X_train_new_data)
X_test_new_data = scaler.transform(X_test_new_data)

""" y_train=y_train.astype('int')
y_test=y_test.astype('int')

y_train_new_data=y_train_new_data.astype('int')
y_test_new_data=y_test_new_data.astype('int')
 """

import keras
from keras.models import Sequential,Input,Model
from keras.layers import Dense, Dropout, Flatten
from keras.layers import Conv2D, MaxPooling2D
from keras.layers.normalization import BatchNormalization
from keras.layers.advanced_activations import LeakyReLU

import tensorflow as tf

