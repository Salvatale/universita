close all
clear
clc

x = [0.49 0.64 0.81];
y = [0.7 0.8 0.9];
n = 2;
p = polyfit(x,y,n);
val = polyval(p,0.6);
err = abs(sqrt(0.6)-val)

%approssimazione con 4 punti
x = [0.49 0.64 0.81 0.36];
y = [0.7 0.8 0.9 0.6];
n = 2;
p = polyfit(x,y,n);
val = polyval(p,0.6);
err = abs(sqrt(0.6)-val)
