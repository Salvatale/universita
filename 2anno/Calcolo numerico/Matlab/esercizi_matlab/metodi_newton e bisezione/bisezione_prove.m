close all
clear
clc



a = 0;
b = 1.5;
f = @(x) cos(2*x)^2-x^2;
tolleranza = 10^-10;

[x,e,num_iter] = metodo_bisezione(tolleranza,a,b,f);
x
num_iter
plot(e);
title('grafico errore');
max_iter = (log(b-a) - log(tolleranza))/log(2);
max_iter

