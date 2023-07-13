% Standard Opening
clear;
clc;
close all;

% closed = closeddoorfinaldataset;
% open = midhallwayclearfinaldataset;
% 
% inputTable = vertcat(closed,open); % Brings arrays together

% Setting up colours for plotting
colourArray = ["#F73309", "#27F10E", "#EBF10E", "#EB0EF1", "#0E14F1", "#A4A5BC", "#ADF5CA", "#8B0E31", "#43F9FD"];

data_folder = "D:\Courses\UUJ\Research Project\masters_project\MATLAB\Data";
run_folder = pwd;

cd(data_folder);
% [file,path] = uigetfile('*.csv','Select One or More Files','MultiSelect','on');
% input_table = readtable(strcat(path,file));

closedDoor = readtable("grid0_closeddoor_clearhallway.csv");
displayStand = readtable("grid0_displaystand_clearhallway.csv");
largeBin = readtable("grid0_largebin_clearhallway.csv");
storageBox = readtable("grid0_storagebox_clearhallway.csv");

inputTable = vertcat(closedDoor, displayStand,largeBin,storageBox);

% writetable(inputTable,'myData.csv','Delimiter',' ')  

% inputTable = input_table;

% % Scatter plotting
% for i = 1:9
%     plotTable = inputTable(inputTable.Grid == i, :);
%     scatter(plotTable.Channel1, plotTable.Channel2,'color',colourArray{i},'marker','o')
%     hold on
% end

% Change the Pclass from number to char (categorical variable) for
% convience 
% inputTable.Pclass= num2str(inputTable.Pclass);

% ~~Predictors and Response~~
% This code processes the data into the correct shape for training the
% model
predictorNames = {'Channel1','Channel2'};
toNormalise = inputTable(:,predictorNames);
% N = normalize(toNormalise,'range');
% bpredictors = N;
predictors = inputTable(:,predictorNames);  % Could also be predictorNames = inputTable(:,[3,5,12]);
response = inputTable.Grid;
% response = inputTable.LabelObject;

% ~~Train the classifier~~
% This code specifies all the classifier options and trains the classifier option and trains the classifier
% trainedDecisionTreeModel = fitctree(predictors,response,'OptimizeHyperparameters','auto');
trainedDecisionTreeModel = fitctree(predictors,response);
validationAccuracy = 1 - loss(trainedDecisionTreeModel,predictors,response);

% ~~Graphic respresentation of the tree~~
view(trainedDecisionTreeModel,'mode','graph')

predicatedY = resubPredict(trainedDecisionTreeModel); 

% ~~Use Train/Test to evaluate the model preformance~~
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

% Build a new tree on the training datasets only
predictors = trainingData(:, predictorNames);
response = trainingData.Grid;
% response = trainingData.LabelObject;
trainedDecisionModdel1 = fitctree(predictors,response);

% Compute the accuracy on the training data
validationAccuracy1 = 1 - loss(trainedDecisionModdel1,predictors,response);

% Preformance evaluation on the test data
% Predict the labels of the test data
predictedY = predict(trainedDecisionModdel1,testData(:,predictorNames));

% Create a confusion matrix chart from the true labels and the predicted
% labelspredictedY
cm = confusionchart(testData.Grid,predictedY);
% cm = confusionchart(testData.LabelObject,predictedY);



% results = zeros(1,50);
% for n = 1:50
%     Mdl_n = fitctree(predictors,response,'MaxNumSplits',n,'CrossVal','on');
%     % view(Mdl_n.Trained{1}, 'mode', 'graph')
%     validationAccuracy1 = 1 - loss(Mdl_n.Trained{1},predictors,response);
%     results(n) = results(n) + validationAccuracy1;
% end
% % results = results * 100;