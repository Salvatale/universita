close all
clc
clear

n = 10;
A = triu(rand(n));
x_esatto = rand(n,1);
b = A*x_esatto;
x = metodo_indietro(A,b)';


%controllo

norma = norm(A*x -b)
errore = abs(x_esatto-x)