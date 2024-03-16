close all
clear
clc

f = @(x) x^3-6*x^2+11*x-6;
a = 2.7;
b = 3;
tolleranza = 10^-5;
errore = abs(b-a);
num_iter = 0;

while errore > tolleranza
    x = (a+b)/2;
    if (f(x)*f(a)) < 0
        b = x;
    elseif (f(x)*f(a)) == 0
        return
    else
        a = x;
    end
    num_iter = num_iter+1;
    errore = abs(b-a);
end

x
num_iter