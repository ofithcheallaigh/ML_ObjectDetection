# Classification
## Introduction

These set of notes aim to set the goundwork for classification within the world of machine learning.

Generally speaking, there are three different types of machine leaning:
1. Supervised leaning
    - Labelled data
    - Direct feedback
    - Predict the outcome
2. Unsupervised learning
    - No labels/targets
    - No feedback
    - Finds the hidden structure in data
3. Reinforement learning
    - Decision process
    - Reward system
    - Learn series of action

Classification is a subcategory of supervised learning. In classification, the aim is to preicat the class labels for new instances or data, based on past observations. 

## Lovely Spam, Wonderful Spam
The standard example used to try and explain classification is the email span detection system. This is an example of a binary classifier, since there are only two possible outcomes: spam and not spam. 

Typically, binary classification tasks involve one class that is said to be a "normal state". It follows the other class is the "not normal" state, or to be more precise, the "abnormal state". In the email example, "not spam" is the normal state, and "spam" is the abnormal state. In another common example, "not cancer" is the normal state, and "caner" is the abnormal state. Again, typially, the normal state is denoted by class label 0, and the abnormal state is denited by the class label 1. 

There are a number of popular classification algorithms that can be used for binary classification:
1. Logistic Regression
2. k-Nearest Neigbour
3. Decision Trees
4. Support Vector Machines
5. Naive Bayes

Some of the above can be used for multi-classification systems, which others (logistic regression, SVM) are specifically aimed at binary classification.    

Classification algotithms, such as logistic regression, generate probability scores that assign some probability of the input belonging to a category. This probability is then mapped to a binary mapping (if the classification is binary). If we use the email spam example, a model might read an email and generate a probability score of 95%. This high score means that there is a very high chance the that the email is spam. In the same way, a model may read an email and assign a probability score of 3% that the email is spam. This means that in all likihood, the email is _not_ spam.

When we are dealing with these sorts of scores, the binary assignment is pretty obvious. Things get a bit more tricky when dealing with scores of say, 52%. Should a score of 52% be assigned to spam? Should a score of 41% be assigned to not-spam?

This is where the idea of a classification threshold comes into play.

## Classification Thresholds
One potential threshold which could be used would be 0.5, where all inputs greather than or equal this threshold are mapped to one class, and all other inputs are mapped to the different class. To put it another way:

```math 
\textrm{Class} \space 0 = \textrm{Prediction} \ge 0.5 
```
```math
\textrm{Class} \space 1 = \textrm{Prediction} < 0.5 
```


Which this threshold may be a starting point, thresholds are problem specific, and as such, they need to be tuned. 

The best threshold for the classifier may be derived from a set of circumstances, such as looking at Precision-Recall Curves or ROC Curves

## The Algorithms
### Logistic Regression
Logistic regression is a ML algorithm used for classification tasks. As described above, classification tasks are concerned with predicting the probability that an input belongs in a certain class or not. 

Logistics regression gets it's name from the function used in the method - the logistic function

# Sources
1. [Towards Data Science - Classification Models and Thresholds in Machine Leanring](https://towardsdatascience.com/classification-models-and-thresholds-97821aa5760f#:~:text=Classification%20models%20are%20a%20subset,spam%20or%20not%20%E2%80%94%20binary%20classification.)
2. [Machine Learning Mastery - A Gentle Introduction to Threshold-Moving for Imbalanced Classification](https://machinelearningmastery.com/threshold-moving-for-imbalanced-classification/)
3. [Deep Checks - Classification Thresholds](https://deepchecks.com/glossary/classification-threshold/#:~:text=In%20a%20binary%20classification%20issue,are%20allocated%20to%20class%200.)
4. [Equation Support 1](https://docs.mathjax.org/en/latest/input/tex/macros/index.html)
5. [Equation Support 2](https://docs.github.com/en/get-started/writing-on-github/working-with-advanced-formatting/writing-mathematical-expressions)
6. [KD Nugets - How Does Logistic Regression Work](https://www.kdnuggets.com/2022/07/logistic-regression-work.html)
7. [Machine Leaning Mastery - Logistic Regression for Machine Learning](https://machinelearningmastery.com/logistic-regression-for-machine-learning/)


