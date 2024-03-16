close all
clear
clc

x = -55:10:65;
n = length(x);
y = [-3.25 -3.37 -3.35 -3.2 -3.12 -3.02 -3.02 -3.07 -3.17 -3.32 -3.3 -3.22 -3.1];
x1 = linspace(-55,65);

%interpolazione semplice
p = polyfit(x,y,n-1);
plot(x,y,'*');
hold on
plot(x1,polyval(p,x1));

%interpolazione composita
pc = interp1(x,y,x1);
plot(x1,pc);

%interpolazione spline
ps = spline(x,y,x1);
plot(x1,ps);


legend("nodi","polinomio i.semplice", ...
    "interpolazione composita","spline");
