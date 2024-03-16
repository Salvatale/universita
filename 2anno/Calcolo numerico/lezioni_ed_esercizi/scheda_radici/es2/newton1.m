close all
clear
clc

tolleranza = 10^-5;
f = @(x) x^3-6*x^2+11*x-6;
df = @(x) 3*x^2-12*x+11;
x = 2.4;
criterio_arresto = abs(f(x));
num_iter = 0;


while criterio_arresto > tolleranza
    x = x - f(x)/df(x);
    criterio_arresto = abs(f(x));
    num_iter = num_iter+1;
end
x
num_iter