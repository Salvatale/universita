close all
clear all
clc

a = 0.6;
b = 1;
tolleranza = 10^-10;
f = @(x) x/8*(63*x^4-70*x^2+15);
max_iter = (log(b-a)-log(tolleranza))/log(2)

iter = 1;
err = abs(b-a);

while err > tolleranza
    x = (a+b)/2;
    if(f(x)*f(a)) < 0
        b = x;
    elseif (f(x)*f(a)) == 0
        return;
    else
        a = x;
    end
    err = abs(b-a);
    e(iter) = err;
    iter = iter+1;
end
radice_alfa = x
iter
plot(e);
title("grafico errore relativo");




