close all
clc
clear
format long e
n = 1000;
A = tril(rand(n));
x_esatto = rand(n,1);
b = A*x_esatto;
x = metodo_in_avanti(A,b)';

errore = abs(x_esatto-x)
norma = norm(A*x-b)
condizionamento = cond(A)
