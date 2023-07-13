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



"""len_dataset1 = len(dataset1)
len_dataset2 = len(dataset2)

grid_dataset1_lengths = []
grid_dataset2_lengths = []
# for y in range(len_dataset1):
for x in range(1,10):
    grid_length1 = len(dataset1[dataset1['Grid']==x])
    grid_dataset1_lengths.append(grid_length1)
    grid_length2 = len(dataset2[dataset2['Grid']==x])
    grid_dataset2_lengths.append(grid_length2)

## Balancing dataset
# Now I have the lengths for the data in each grid, I need to start building a new dataset for the grid 0 data
data_points = sum(grid_dataset2_lengths) / len(grid_dataset2_lengths)
data_points = data_points / len(grid_dataset2_lengths) # I will need to take this value from each grid data
data_points = int(data_points)

# Now to try and build the dataset
# new_dataset = pd.DataFrame(columns=["Channel1", "Channel2", "LabelObject", "Grid"])
new_dataset = pd.DataFrame()
for x in range(1,10):
    temp_data = dataset2[dataset2['Grid']==x]
    temp_data = temp_data.iloc[:data_points,:]
    new_dataset = new_dataset.append(temp_data)

dataset2 = modify_to_grid_zero_fn(new_dataset) 

data = np.vstack((dataset1,dataset2)) # Create a variable with one dataset stacked on the other """

# data = np.vstack((dataset1,dataset2,dataset3,dataset4))
data = np.vstack((dataset1))
# data = data.drop("Var1",axis=1)
# data = pd.DataFrame(data) # Convert to DataFrame
data.columns=["Channel1","Channel2","LabelObject","Grid"] # Assign column names
# data.to_csv('grid0_storagebox_clearhallway.csv') # This was here to output a text file to show Ian

# For new_data
# new_data = ((dataset1))
# new_data = pd.DataFrame(new_data) # Convert to DataFrame
# new_data.columns=["Channel1","Channel2","LabelObject","Grid"] # Assign column names

# pick out rows depending on grid num
# This was added in to just pick out grid pos 1
# grid1_data = data.loc[data['Grid']==1]
# data = grid1_data

feature_names = ['Channel1','Channel2'] # Features we are interested in
# feature_names = ['Channel1'] # Features we are interested in
# response = data['Grid'] # Response we are interested in
response = data['LabelObject'] # Response we are interested in

# Replaces Yes/No with 1/0. Required because some algo will not accept categorical data
data.LabelObject.replace(('Yes', 'No'), (1, 0), inplace=True) 
# new_data.LabelObject.replace(('Yes', 'No'), (1, 0), inplace=True)

# dataset2 = modify_to_grid_zero_fn(dataset2) 

# X and y are what will be passed through the algorithms to train the model
X = data[feature_names]
# y = data['LabelObject']
y = data['Grid']

# X_new_data = new_data[feature_names]
# y_new_data = new_data['LabelObject']
# y_new_data = new_data['Grid']


# cmap = cm.get_cmap('gnuplot')
# scatter = pd.plotting.scatter_matrix(X, c=response, marker='o', s=40, hist_kwds={'bins':15}, figsize=(9,9), cmap=cmap)
# pd.plotting.scatter_matrix(for_scatter)
# plt.suptitle('Scatter-matrix for each input variable')
# plt.show()
# plt.savefig('object_scatter_matrix. Object: Display Stand')


# Creating Training and Test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0) # train_test_split is the best way to slipt up the data
scaler=MinMaxScaler() # Using a scaler because there can be a lot of variability in the data values
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# This will be where I will gather my train data that the system has not been tested on
# X_train_new_data, X_test_new_data, y_train_new_data, y_test_new_data = train_test_split(X_new_data, y_new_data, random_state=0) # train_test_split is the best way to slipt up the data
# scaler=MinMaxScaler() # Using a scaler because there can be a lot of variability in the data values
# X_train_new_data = scaler.fit_transform(X_train_new_data)
# X_test_new_data = scaler.transform(X_test_new_data)

y_train=y_train.astype('int')
y_test=y_test.astype('int')

# y_train_new_data=y_train_new_data.astype('int')
# y_test_new_data=y_test_new_data.astype('int')


# This is called when wanting to look at the plot to help determine the number of 
# neigbours that get's the best result
# allResults = get_knn_n_plot(X_train, X_test, y_train, y_test)


# The sections below generate the model accuracy scores
# Model: Logistic regression
logReg = LogisticRegression()
logReg.fit(X_train, y_train)
print('Accuracy of Logistic regression classifier on training set: {:.2f}'.format(logReg.score(X_train, y_train))) 
print('Accuracy of Logistic regression classifier on test set: {:.2f}'.format(logReg.score(X_test, y_test))) 

# Below is used for the unseen data
# print('Accuracy of Logistic regression classifier on test set: {:.2f}'.format(logReg.score(X_test_new_data, y_test_new_data))) 

# Model: Decision tree
clf = DecisionTreeClassifier().fit(X_train, y_train)
print('Accuracy of Decision Tree classifier on training set: {:.2f}'.format(clf.score(X_train, y_train))) 
print('Accuracy of Decision Tree classifier on test set: {:.2f}'.format(clf.score(X_test, y_test))) 

# Below is used for the unseen data
# print('Accuracy of Decision Tree classifier on test set: {:.2f}'.format(clf.score(X_test_new_data, y_test_new_data))) 

# Model: KNN
knn = KNeighborsClassifier()
knn.fit(X_train,y_train)
print('Accuracy of K-NN classifier on training set: {:.2f}'.format(knn.score(X_train, y_train))) 
print('Accuracy of K-NN classifier on test set: {:.2f}'.format(knn.score(X_test, y_test))) 

# Below is used for the unseen data
# print('Accuracy of K-NN classifier on test set: {:.2f}'.format(knn.score(X_test_new_data, y_test_new_data))) 

# Model: Linear Discriminant Analysis
lda = LinearDiscriminantAnalysis()
lda.fit(X_train, y_train)
print('Accuracy of LDA classifier on training set: {:.2f}'.format(lda.score(X_train, y_train))) 
print('Accuracy of LDA classifier on test set: {:.2f}'.format(lda.score(X_test, y_test))) 

# Below is used for the unseen data
# print('Accuracy of LDA classifier on test set: {:.2f}'.format(lda.score(X_test_new_data, y_test_new_data))) 

# Model: Gaussian Naive Bayes
gnb = GaussianNB()
gnb.fit(X_train, y_train)
print('Accuracy of GNB classifier on training set: {:.2f}'.format(gnb.score(X_train, y_train)))
print('Accuracy of GNB classifier on test set: {:.2f}'.format(gnb.score(X_test, y_test))) 

# Below is used for the unseen data
# print('Accuracy of GNB classifier on test set: {:.2f}'.format(gnb.score(X_test_new_data, y_test_new_data))) 

""" # Model: SVM
svm = SVC()
svm.fit(X_train, y_train)
print('Accuracy of SVM classifier on training set: {:.2f}'.format(svm.score(X_train, y_train)))
print('Accuracy of SVM classifier on test set: {:.2f}'.format(svm.score(X_test, y_test))) """
