
close all
clear
clc

f = @(x) cos(2*x)^2-x^2;
df = @(x) -4*cos(2*x)*sin(2*x)-2*x;
tolleranza = 10^-10;
x0 = 0.5;
max_iter = 100;

[num_iter, x] = metodo_newton(f,df,tolleranza,x0,max_iter);
x
num_iter

radice = fzero(f,x0)
err = abs(radice - x)

