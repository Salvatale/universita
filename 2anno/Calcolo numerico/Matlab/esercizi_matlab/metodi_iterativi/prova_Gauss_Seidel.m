close all
clc
clear

format long e
A = [4,1,1;2,-9,0;0,-8,-6];
x_esatto = [6;1;2];
b = A*x_esatto;
max_iter = 100;
tolleranza = 10^-2;

[x,k] = Gauss_Seidel_Matrix(A,b,tolleranza,max_iter)
x_esatto
x
err = norm(x_esatto-x)
k