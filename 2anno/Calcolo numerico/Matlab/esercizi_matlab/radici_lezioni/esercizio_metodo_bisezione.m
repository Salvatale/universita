%metodo bisezione calcolo della radice
% a = 0.5149 della fun = cos(2x)^2 -x^2

close all
clear
clc

a = 0;
b = 1.5;
errore = abs(b-a);
tolleranza = 10^-10;

fun = @(x) cos(2*x)^2-x^2;

i = 1;

while errore > tolleranza
    x = (a+b)/2;
    if(fun(x)*fun(a))< 0
        b = x;
    elseif fun(x) == 0
        return;
    else
        a = x;
    end
    errore = abs(b-a);
    grafico_errore(i) = errore;
    i = i+1;
end

plot(grafico_errore);
title('errore');
x


