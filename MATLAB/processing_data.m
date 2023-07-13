% This file is to try and visualise the data in some decent format
% load("dist_large_narrow_big_mid_hallway.mat")
% data_folder = "D:\Courses\UUJ\Research Project\masters_project\Data Collection\RawDataCollection\Mat files";
data_folder = pwd;
file_list = dir("*.csv");

% data = distancegrid1doorclosed1;
num_of_files = length(file_list);

for i = 1:num_of_files
    
    data = readtable(file_list(i).name, VariableNamingRule="preserve");
    
    data.Properties.VariableNames = ["Ch1 Index", "Ch1 Data", "Ch2 Index", "Ch2 Data"];
    
    ch1_data_dist = data.("Ch1 Data");
    ch2_data_dist = data.("Ch2 Data");
    
    % Moving average filter
    ch1_moving_average = movmean(ch1_data_dist,5);
    ch2_moving_average = movmean(ch2_data_dist,5);

    % Now to work out the distance in cm
    ch1_data_cm = ch1_data_dist * 0.034 / 2;
    ch2_data_cm = ch2_data_dist * 0.034 / 2;


%     figure(1)
%     subplot(3,3,i)
%     plot(ch1_data_dist)
%     hold on 
%     plot(ch2_data_dist)
%     hold off
%     % title("Closed Door, Grid 1, Moving Average")
%     title(file_list(i).name, 'Interpreter', 'none')
%     xlabel("Sample")
%     ylabel("distance")
%     ylim([0 10000])

    figure(1)
    subplot(3,3,i)
    plot(ch1_data_cm)
    hold on 
    plot(ch2_data_cm)
    hold off
    % title("Closed Door, Grid 1, Moving Average")
    title(file_list(i).name, 'Interpreter', 'none')
    xlabel("Sample")
    ylabel("Distance (cm)")
    ylim([0 200])


end

