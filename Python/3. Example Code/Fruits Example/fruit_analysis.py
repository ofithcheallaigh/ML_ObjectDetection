# Source: https://towardsdatascience.com/solving-a-simple-classification-problem-with-python-fruits-lovers-edition-d20ab6b071d2 

import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import pylab as pl
from pandas.plotting import scatter_matrix
from matplotlib import cm
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler

from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.naive_bayes import GaussianNB
from sklearn.svm import SVC

from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix

fruits = pd.read_table('3. Example Code\Fruits Example\\fruit_data_with_colors.txt')

# print(fruits.head())
# print(fruits.shape) # 59, 7
# print(fruits['fruit_name'].unique()) # ['apple' 'mandarin' 'orange' 'lemon']
# print(fruits.groupby('fruit_name').size()) # apple       19
                                           # lemon       16
                                           # mandarin     5
                                           # orange      19

fruits.drop('fruit_label', axis=1).plot(kind='box', subplots=True, layout=(2,2), sharex=False, sharey=False, figsize=(9,9), 
                                        title='Box Plot for each input variable')
# plt.savefig('fruits_box')
# plt.show()
# Plot shows that colour seems to have a pretty good Gaussian distribution.

fruits.drop('fruit_label', axis=1).hist(bins=30,figsize=(9,9))
plt.suptitle("Histogram for each numeric input variable")
# plt.savefig('fruits_hist')
# plt.show()
# Some pairs of attributes are correlated (such as mass and width). This suggest a high correlation and a predictable relationship.

feature_names = ['mass','width','height','color_score']
X = fruits[feature_names]
y = fruits['fruit_label']

print(X)
print(y)

cmap = cm.get_cmap('gnuplot')
scatter = pd.plotting.scatter_matrix(X, c=y, marker='o', s=40, hist_kwds={'bins':15}, figsize=(9,9), cmap=cmap)
plt.suptitle('Scatter-matrix for each input variable')
plt.show()
# plt.savefig('fruits_scatter_matrix')

# Creating Training and Test sets
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)
scaler=MinMaxScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# Model: Logistic regression
logReg = LogisticRegression()
logReg.fit(X_train, y_train)
print('Accuracy of Logistic regression classifier on training set: {:.2f}'.format(logReg.score(X_train, y_train))) # 0.75
print('Accuracy of Logistic regression classifier on test set: {:.2f}'.format(logReg.score(X_test, y_test))) # 0.47

# Model: Decision tree
clf = DecisionTreeClassifier().fit(X_train, y_train)
print('Accuracy of Decision Tree classifier on training set: {:.2f}'.format(clf.score(X_train, y_train))) # 1.00
print('Accuracy of Decision Tree classifier on test set: {:.2f}'.format(clf.score(X_test, y_test))) # 0.87

# Model: KNN
knn = KNeighborsClassifier()
knn.fit(X_train,y_train)
print('Accuracy of K-NN classifier on training set: {:.2f}'.format(knn.score(X_train, y_train))) # 0.95
print('Accuracy of K-NN classifier on test set: {:.2f}'.format(knn.score(X_test, y_test))) # 1.00

# Model: Linear Discriminant Analysis
lda = LinearDiscriminantAnalysis()
lda.fit(X_train, y_train)
print('Accuracy of LDA classifier on training set: {:.2f}'.format(lda.score(X_train, y_train))) #0.86
print('Accuracy of LDA classifier on test set: {:.2f}'.format(lda.score(X_test, y_test))) # 0.67

# Model: Gaussian Naive Bayes
gnb = GaussianNB()
gnb.fit(X_train, y_train)
print('Accuracy of GNB classifier on training set: {:.2f}'.format(gnb.score(X_train, y_train))) # 0.86
print('Accuracy of GNB classifier on test set: {:.2f}'.format(gnb.score(X_test, y_test))) # 0.67

# Model: SVM
svm = SVC()
svm.fit(X_train, y_train)
print('Accuracy of SVM classifier on training set: {:.2f}'.format(svm.score(X_train, y_train))) # 0.91
print('Accuracy of SVM classifier on test set: {:.2f}'.format(svm.score(X_test, y_test))) # 0.80

# KNN was the most accurate
pred = knn.predict(X_test)
print(confusion_matrix(y_test, pred))
print(classification_report(y_test, pred))