close all
clear
clc
format long e
A = [4,1,1;2,-9,0;0,-8,-6];
x_esatto = [6;1;2];
b = A*x_esatto;
max_iter = 1000;
tolleranza = 10^-8;

[x,k] = Jacobi_matrix(A,b,tolleranza,max_iter);
x
x_esatto
err = abs(x_esatto-x)
k

pause
