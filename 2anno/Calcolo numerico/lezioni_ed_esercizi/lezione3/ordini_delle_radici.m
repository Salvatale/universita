close all
clear all
clc

p = @(x) x.^2-2*x+2;
coeff = [1 -2 1];
radici = roots(coeff);
x = linspace(0,2);
plot(x,p(x));

%controllo se f_m(a) diverso da 0;

dsecf = @(x) 2;
dsecf(radici);

%verifico derivata prima sia uguale a 0
d_primf = @(x) 2*x-2;
d_primf(radici)

