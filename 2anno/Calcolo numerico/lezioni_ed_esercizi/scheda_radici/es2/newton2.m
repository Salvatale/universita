close all
clear
clc

tolleranza = 10^-5;
f = @(x) x^4-7*x^3+15*x^2-13*x-6;
df = @(x) 4*x^3-21*x^2+30*x-13;
x = -12;
criterio_arresto = abs(f(x));
num_iter = 0;


while criterio_arresto > tolleranza
    x = x - f(x)/df(x);
    criterio_arresto = abs(f(x));
    num_iter = num_iter+1;
end
x
num_iter