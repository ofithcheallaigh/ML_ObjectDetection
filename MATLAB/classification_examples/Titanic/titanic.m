%% Example of classification using the Titanic dataset
% Data is imported as a table. Tables store data in column-orientd or
% tabular data. Table variables can have different data types and sizes as
% long as all varibles have the same number of rows. Table variables have 
% names, just as the fields of a structure have names. Use the summary function 
% to get information about a table

%% Standard Opening
clear;
clc;
close all;

%% Read in the data
titanicData = readtable("titanic_data.csv");
% summary(titanicData)

%% Building the decision tree model
inputTable = titanicData;

% Change the Pclass from number to char (categorical variable) for
% convience 
inputTable.Pclass= num2str(inputTable.Pclass);

% ~~Predictors and Response~~
% This code processes the data into the correct shape for training the
% model
predictorNames = {'Pclass','Sex','Embarked'};
predictors = inputTable(:,predictorNames);  % Could also be predictorNames = inputTable(:,[3,5,12]);
response = inputTable.Survived;

% ~~Train the classifier~~
% This code specifies all the classifier options and trains the classifier
% option and trains the classifier
trainedDecisionTreeModel = fitctree(predictors,response);

% ~~Graphic respresentation of the tree~~
view(trainedDecisionTreeModel,'mode','graph')
% text description (rule generated by the tree)
view(trainedDecisionTreeModel) 

% ~~Model preformance and evaluation on the training dataset~~
% Predicted class of the training 
predicatedY = resubPredict(trainedDecisionTreeModel); 

% Compute the accuracy
valaidationAccuracy = 1 - loss(trainedDecisionTreeModel,predictors,response);

%% ~~Use Train/Test to evaluate the model preformance~~
% Split the data randomly into train and test groups, on a 70%/30% split
% First, get the size of the data
[m,n] = size(inputTable);

% Generate a vector containing random permutation of the integers from 1 to
% n without repeating
idx = randperm(m);

% Set the split perfectage
splitPercentage = 0.70;
% m1 is the number of the training data
m1 = round(splitPercentage*m);
% Now split the data
trainingData = inputTable(idx(1:m1),:);
testData = inputTable(idx(m1+1:end),:);

%% Build a new tree on the training datasets only
predictors = trainingData(:, predictorNames);
response = trainingData.Survived;
trainedDecisionModdel1 = fitctree(predictors,response);

% Compute the accuracy on the training data
validationAccuracy1 = 1 - loss(trainedDecisionModdel1,predictors,response);

%% Preformance evaluation on the test data
% Predict the labels of the test data
predictedY = predict(trainedDecisionModdel1,testData(:,predictorNames));

% Create a confusion matrix chart from the true labels and the predicted
% labelspredictedY
cm = confusionchart(testData.Survived,predictedY);