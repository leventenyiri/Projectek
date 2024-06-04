function Accelerometer(filename)
    choice = input(['Choose plot type (1 for subplots, 2 for overlay(acceleration vs velocity),' ...
        '\n 3 for overlay(displacement vs velocity), 4 for ovelay(acceleration vs displacement): ']);
    data = readmatrix(filename);
    time = data(:,4);
    displacement = data(:,3);
    velocity = data(:,2);
    acceleration = data(:,1);

    if choice == 1
        % Create figure and subplots
        figure;
        subplot(1,3,1);
        plot(time, acceleration);
        xlabel('Time [s]');
        ylabel('Acceleration');
        title('Acceleration vs time');
        grid on;

        subplot(1,3,2);
        plot(time, velocity);
        xlabel('Time [s]');
        ylabel('Velocity');
        title('Velocity vs time');
        grid on;

        subplot(1,3,3);
        plot(time, displacement);
        xlabel('Time [s]');
        ylabel('Displacement');
        title('Displacement vs time');
        grid on;
    elseif choice == 2
        plotOverlay(filename);

    elseif choice == 3
        plotOverlay1(filename);

    elseif choice == 4
        plotOverlay2(filename);
    end
end

function plotOverlay(filename)
    data = readmatrix(filename);
    time = data(:,4);
    velocity = data(:,2);
    acceleration = data(:,1);

    % Create figure and plot data
    figure;
    plot(time, acceleration, 'blue');
    hold on;
    plot(time, velocity, 'red');
    xlabel('Time [s]');
    ylabel('Data');
    title('Acceleration and Velocity vs Time');
    legend('Acceleration', 'Velocity');
    grid on;
    hold off;
end

function plotOverlay1(filename)
    data = readmatrix(filename);
    time = data(:,4);
    velocity = data(:,2);
    displacement = data(:,3);

    % Create figure and plot data
    figure;
    plot(time, displacement, 'blue');
    hold on;
    plot(time, velocity, 'red');
    xlabel('Time [s]');
    ylabel('Data');
    title('Displacement and Velocity vs Time');
    legend('Displacement', 'Velocity');
    grid on;
    hold off;
end

function plotOverlay2(filename)
    data = readmatrix(filename);
    time = data(:,4);
    acceleration = data(:,1);
    displacement = data(:,3);

    % Create figure and plot data
    figure;
    plot(time, acceleration, 'blue');
    hold on;
    plot(time, displacement, 'red');
    xlabel('Time [s]');
    ylabel('Data');
    title('Acceleration and Displacement vs Time');
    legend('Acceleration', 'Displacement');
    grid on;
    hold off;
end