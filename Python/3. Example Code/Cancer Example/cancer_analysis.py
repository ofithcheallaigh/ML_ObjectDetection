from sklearn import neighbors
from sklearn.tree import DecisionTreeClassifier
from sklearn.naive_bayes import GaussianNB
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeRegressor
import seaborn as sns 
import matplotlib.pyplot as plt 
from sklearn import model_selection 
import pandas as pd
import numpy as np

# Load dataset into a NumPy array
cancerTrain = np.genfromtxt("Cancer Example\cancerTrain.csv", delimiter=',')
cancerTest = np.genfromtxt("Cancer Example\cancerTest.csv", delimiter=',')

train_features = cancerTrain[:,:-1]
train_labels = cancerTrain[:,-1]

test_features = cancerTest[:,:-1]
test_labels = cancerTest[:,-1]

print(train_features.shape)
print(test_features.shape)

# Evaluate the preformance of a kNN
# We will explore and plot results for combinations of hyper-parameters (k and distance metric)
allResults = []
for kValue in range(1,100):
    knn = neighbors.KNeighborsClassifier(n_neighbors=kValue, metric="minkowski",p=1)
    knn = knn.fit(train_features,train_labels)
    accuracy = knn.score(test_features, test_labels)
    allResults.append(accuracy)
plt.plot(allResults)
plt.show()