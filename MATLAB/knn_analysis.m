data_folder = "D:\Courses\UUJ\Research Project\masters_project\MATLAB\Data";
run_folder = pwd;

cd(data_folder);
% [file,path] = uigetfile('*.csv','Select One or More Files','MultiSelect','on');
% input_table = readtable(strcat(path,file));

closedDoor = readtable("grid0_closeddoor_clearhallway.csv");
displayStand = readtable("grid0_displaystand_clearhallway.csv");
largeBin = readtable("grid0_largebin_clearhallway.csv");
storageBox = readtable("grid0_storagebox_clearhallway.csv");

% distrinution


inputTable = vertcat(closedDoor,displayStand,largeBin,storageBox);

predictorNames = {'Channel1','Channel2'};
% toNormalise = inputTable(:,predictorNames);
% N = normalize(toNormalise,'range');
% predictors = N;
predictors = inputTable(:,predictorNames);

response = inputTable.Grid;
% response = inputTable.LabelObject;

mdl = fitcknn(predictors,response,'NumNeighbors',10);

% Now we will carry out cross validation of the model using crossval, 
% using 5-fold cross validation
cvmdl1= crossval(mdl,'KFold',15);

% We can use Holdout to keep 30% of the data for evaluation
cvmdl2 = crossval(mdl,'Holdout',0.3);

% Output the loss and accuracy of the classifier for both the 5-fold 
% cross validation and Handout validation
cvm1loss = kfoldLoss(cvmdl1, 'LossFun', 'ClassifError');
Accuracy1 = 1 - kfoldLoss(cvmdl1, 'LossFun', 'ClassifError');

cvm2loss=kfoldLoss(cvmdl2, 'LossFun', 'ClassifError');
Accuracy2 = 1 - kfoldLoss(cvmdl2, 'LossFun', 'ClassifError');



