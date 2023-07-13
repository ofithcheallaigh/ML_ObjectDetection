% In this script, I am trying going to generate a subset where there is
% 5000 samples from grip position

N = 5000; % number of samples per grid I want
data = grid0storageboxclearhallway;

resultsTable = table();

conditions = {'Grid 0';'Grid 1';'Grid 2';'Grid 3';'Grid 4';'Grid 5';'Grid 6';'Grid 7';'Grid 8';'Grid 9'};


idx_0 = find(data.Grid == 0);
idx_1 = find(data.Grid == 1);
idx_2 = find(data.Grid == 2);
idx_3 = find(data.Grid == 3);
idx_4 = find(data.Grid == 4);
idx_5 = find(data.Grid == 5);
idx_6 = find(data.Grid == 6);
idx_7 = find(data.Grid == 7);
idx_8 = find(data.Grid == 8);
idx_9 = find(data.Grid == 9);

% First indexs
start_grid_0 = idx_0(1);
start_grid_1 = idx_1(1);
start_grid_2 = idx_2(1);
start_grid_3 = idx_3(1);
start_grid_4 = idx_4(1);
start_grid_5 = idx_5(1);
start_grid_6 = idx_6(1);
start_grid_7 = idx_7(1);
start_grid_8 = idx_8(1);
start_grid_9 = idx_9(1);

% Get data
sub_grid_0 = data((start_grid_0:start_grid_0+N-1),:);
sub_grid_1 = data((start_grid_1:start_grid_1+N-1),:);
sub_grid_2 = data((start_grid_2:start_grid_2+N-1),:);
sub_grid_3 = data((start_grid_3:start_grid_3+N-1),:);
sub_grid_4 = data((start_grid_4:start_grid_4+N-1),:);
sub_grid_5 = data((start_grid_5:start_grid_5+N-1),:);
sub_grid_6 = data((start_grid_6:start_grid_6+N-1),:);
sub_grid_7 = data((start_grid_7:start_grid_7+N-1),:);
sub_grid_8 = data((start_grid_8:start_grid_8+N-1),:);
sub_grid_9 = data((start_grid_9:start_grid_9+N-1),:);

out_table = vertcat(sub_grid_0,sub_grid_1,sub_grid_2,sub_grid_3,sub_grid_4,sub_grid_5,sub_grid_6,sub_grid_7,sub_grid_8,sub_grid_9);

writetable(out_table,'sub_dataset_storagebox_clearhallway.csv');




