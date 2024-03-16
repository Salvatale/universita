close all
clear all
clc

x = -55:10:65;
y = [-3.25 -3.37 -3.35 -3.2 -3.12 -3.02 -3.02 -3.07 -3.17 -3.32 -3.3 -3.22 -3.1];

n = 12;

plot(x,y,'*');

hold on
intervallo = linspace(-55,65);

%interpolazione lagrangiana semplice
coeff = polyfit(x,y,n);
plot(intervallo,polyval(coeff,intervallo));

%interpolazione composita
val1 = interp1(x,y,intervallo);
plot(intervallo,val1);

%interpolazione spline
val2 = spline(x,y,intervallo);
plot(intervallo,val2);

legend("punti interpolazione","semplice","composita","spline");


