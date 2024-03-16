close all
clear all
clc
a=0;
b=1;
tolleranza = 10^-5;
f = @(x) 7*exp(-5*x)-3*exp(-2*x)-5;
err = 1;

i =0;
while err > tolleranza
    x = (a+b)/2;
    i = i+1;
    if (f(x)*f(a)) < 0
        b = x;
    elseif (f(x)*f(a)) == 0
        alfa = x
        disp("la radice dell'equazione è uguale" + ...
            "a "+ alfa);
        break;
    else
        a = x;
    end
    err = abs(b-a);
    e(i) = err;
end
err < tolleranza

%grafico dell'errore
ascisse = linspace(0,1,i);
plot(ascisse,e)
