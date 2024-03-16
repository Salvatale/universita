close all
clear
clc
format long e

n = 1000;
A = diag(ones(n)*1:n);
b = rand(n,1);
x = matr_diag_sol(A,b);




%controllo
norma = norm((A*x)-b)