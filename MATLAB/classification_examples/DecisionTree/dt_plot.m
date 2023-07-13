closed = closeddoorfinaldataset;
open = midhallwayclearfinaldataset;
% 
inputTable = vertcat(closed,open); % Brings arrays together

% inputTable = out;

% Change the Pclass from number to char (categorical variable) for
% convience 
% inputTable.Pclass= num2str(inputTable.Pclass);

% ~~Predictors and Response~~
% This code processes the data into the correct shape for training the
% model
predictorNames = {'Channel1','Channel2'};
toNormalise = inputTable(:,predictorNames);
N = normalize(toNormalise,'range');
predictors = N;
% predictors = inputTable(:,predictorNames);  % Could also be predictorNames = inputTable(:,[3,5,12]);
response = inputTable.Grid;

% ~~Train the classifier~~
% This code specifies all the classifier options and trains the classifier
% option and trains the classifier
trainedDecisionTreeModel = fitctree(predictors,response,'OptimizeHyperparameters','auto');

% ~~Graphic respresentation of the tree~~
view(trainedDecisionTreeModel,'mode','graph')