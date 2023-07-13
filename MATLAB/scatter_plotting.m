% Setting up colours for plotting
colourArray = ["#e6194B", "#3cb44b", "#ffe119", "#4363d8", "#f58231", "#911eb4", "#42d4f4", "#f032e6", "#bfef45"];

data_folder = "D:\Courses\UUJ\Research Project\masters_project\MATLAB\Data";
% run_folder = pwd;

cd(data_folder);
[file,path] = uigetfile('*.csv','Select One or More Files','MultiSelect','on');
% filename_split = split(file,'_');

input_table = readtable(strcat(path,file));
% input_table = [a; b; c; d]; % Only used when manually entering data

inputTable = input_table;

fname = string(strcat(filename_split(2), '.txt'));
fileID = fopen(fname,'w');

% Scatter plotting
for i = 1:9

    plotTable = inputTable(inputTable.Grid == i, :);
%     uniqueValuesCh1 = unique(plotTable.Channel1);
%     uniqueValuesCh2 = unique(plotTable.Channel2);
% 
%     fprintf(fileID,"The length of Grid %i data is: %i\n", i, height(plotTable));
%     fprintf(fileID,"The maxmimum value in the Grid %i, Channel 1 data set is %i\n", i, max(plotTable.Channel1));
%     fprintf(fileID,"The mimimum value in the Grid %i, Channel 1 data set is %i\n", i, min(plotTable.Channel1));
%     diff1 = max(plotTable.Channel1) - min(plotTable.Channel1);
%     fprintf(fileID,"The unique number of values in the Grid %i, Channel 1 data set is %i\n", i, length(uniqueValuesCh1));
%     fprintf(fileID,"The max-min difference is %i",diff1);
% 
%     fprintf(fileID,"\n");
% 
%     fprintf(fileID,"The maxmimum value in the Grid %i, Channel 2 data set is %i\n", i, max(plotTable.Channel2));
%     fprintf(fileID,"The mimimum value in the Grid %i, Channel 2 data set is %i\n", i, min(plotTable.Channel2));
%     fprintf(fileID,"The unique number of values in the Grid %i, Channel 2 data set is %i\n", i, length(uniqueValuesCh2));
%     diff2 = max(plotTable.Channel2) - min(plotTable.Channel2);
%     fprintf(fileID,"The max-min difference is %i",diff2);
% 
%     fprintf(fileID, "\n");
%     fprintf(fileID,"===========================================================================================\n");
%     fprintf(fileID, "\n");

    % fprintf("The maxmimum value in the Grid %i data set is %i", i, max(plotTable))
    scatter(plotTable.Channel1, plotTable.Channel2,'color',colourArray{i},'marker','+')
    % title('meh')
    hold on
    title('grid0_storagebox_clearhallway','Interpreter', 'none');
    xlabel("Channel1")
    ylabel("Channel2")
    
end
% fclose(fileID);
legend({'Grid 1';'Grid 2';'Grid 3';'Grid 4';'Grid 5';'Grid 6';'Grid 7'; 'Grid 8';'Grid 9'})

