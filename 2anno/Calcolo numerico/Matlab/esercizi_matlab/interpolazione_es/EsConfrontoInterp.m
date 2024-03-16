clear
clc
close all

x = [-55:10:65];
y = [-3.25, -3.37, -3.35, -3.2, -3.12, -3.02, -3.02, -3.07, -3.17, -3.32, -3.3, -3.22, -3.1];
n = 12;
plot(x, y, "*");
hold on;


interv = linspace(-55, 65);

%% Interp. semplice
coeff = polyfit(x, y, n);
f = polyval(coeff, interv);

plot(interv, f);
hold on;

%% Interp. composita lineare
val = interp1(x, y, interv);

plot(interv, val);
hold on;

%% Interp. spline
val2 = spline(x, y, interv);

plot(interv, val2);
hold on;

legend('punti interpolazione','interpolazione semplice',...
    'interpolazione composita lineare','interpolazione spline')